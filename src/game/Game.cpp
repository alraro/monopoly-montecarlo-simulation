#include "Game.hpp"
#include "utils.hpp"
#include "BoardFactory.hpp"
#include "effectType.hpp"
#include <iostream>
#include "rules.hpp"

Game::Game(): _board(nullptr), _players(), _currentPlayerIndex(0), _gameStatistics() {}

Game &Game::clear() {
    clearBoard();
    clearPlayers();
    return *this;
}

Game &Game::addPlayer(const std::string &name) {
    _players.emplace_back(_players.size(), name, 0);
    return *this;
}

Game &Game::clearPlayers() {
    _players.clear();
    _currentPlayerIndex = 0;
    return *this;
}

Game &Game::setBoard(std::shared_ptr<const Board> board) {
    _board = std::move(board);
    return *this;
}

Game &Game::setDefaultBoard() {
    _board = std::make_shared<const Board>(BoardFactory::createDefaultBoard());
    return *this;
}

Game &Game::clearBoard() {
    _board = nullptr;
    return *this;
}

const std::shared_ptr<const Board> &Game::getBoard() const {
    return _board; 
}

void Game::_sendPlayerToJail(Player &player) {
    player.setCurrentSquare(_board->getJailSquareIndex());
    player.startTurnsLeftInJailCountdown();
    player.resetDoublesRolled();

    this->_gameStatistics.recordTimesJailedPlayer(player.getId());
    std::cout << "[DEBUG] Player " << player.getDescription() << "'s times jailed count is now " << _gameStatistics.getTimesJailedPlayer(player.getId()) << std::endl;

    std::cout << "Player " << player.getDescription() << " is sent to Jail!" << std::endl;
}

EffectResult Game::_movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll) {
    player.setCurrentSquare((player.getCurrentSquare() + diceRoll.total) % _board->getBoardSize());
    const BaseSquare &currentSquare = _board->getSquare(player.getCurrentSquare());

    this->_gameStatistics.recordLandingSquare(player.getCurrentSquare());

    std::cout << "Player " << player.getDescription() << " landed on square " << player.getCurrentSquare() << " (" << currentSquare.getName() << ")." << std::endl;

    EffectResult effect = currentSquare.getSquareEffect(player);
    switch (effect.type) {
        case EffectType::GoToJail:
            _sendPlayerToJail(player);
            break;
        case EffectType::None:
            // No special effect
            break;
        case EffectType::Move:
            // Handle move effect if needed
            break;
    }
    return effect;
}

void Game::_playPlayerTurnDoubles(Player &player, MonopolyDiceRollResult diceRoll) {
    bool wasInJail = player.isInJail();

    if (player.isInJail()) {
        std::cout << "Player " << player.getDescription() << " is in Jail and rolled doubles to get out!" << std::endl;
        player.resetTurnsLeftInJail();
    } else {
        player.incrementDoublesRolled();
    }

    if (player.getDoublesRolledInARow() >= rules::DOUBLES_TO_JAIL) {
        std::cout << "Player " << player.getDescription() << " rolled doubles three times in a row and is sent to Jail!" << std::endl;
        _sendPlayerToJail(player);
    } else {
        EffectResult appliedEffect = _movePlayerDiceRoll(player, diceRoll);

        if (!wasInJail && appliedEffect.type != EffectType::GoToJail) {
            std::cout << "Player " << player.getDescription() << " rolled doubles and gets another turn!" << std::endl;
            _playPlayerTurn(player);
        }
    }
}

void Game::_playPlayerTurnNoDoubles(Player &player, MonopolyDiceRollResult diceRoll) {
    player.resetDoublesRolled();
    EffectResult appliedEffect;
    appliedEffect.type = EffectType::None;
    appliedEffect.value = 0;

    if (player.isInJail()) {
        std::cout << "Player " << player.getDescription() << " is in Jail and did not roll doubles." << std::endl;
    } else {
        appliedEffect = _movePlayerDiceRoll(player, diceRoll);
    }
    if (appliedEffect.type != EffectType::GoToJail) {
        player.decrementTurnsLeftInJail();
    }
}

void Game::_playPlayerTurn(Player &player) {
    this->_gameStatistics.recordTurnPlayer(player.getId());
    std::cout << "[DEBUG] Player " << player.getDescription() << "'s turn count is now " << _gameStatistics.getTotalTurnsPlayer(player.getId()) << std::endl;
    std::cout << "Player " << player.getDescription() << "'s turn." << std::endl;
    
    MonopolyDiceRollResult diceRoll = rollMonopolyDice();
    this->_gameStatistics.recordDiceRollPlayer(player.getId(), diceRoll);

    std::cout << "Player " << player.getDescription() << " rolled a " << diceRoll.total << " (" << diceRoll.die1 << " + " << diceRoll.die2 << ") || " << (diceRoll.doubles ? "DOUBLES!" : "No Doubles") << std::endl;

    if (diceRoll.doubles) {
        _playPlayerTurnDoubles(player, diceRoll);
    } else {
        _playPlayerTurnNoDoubles(player, diceRoll);
    }

    if (player.isInJail()) {
        this->_gameStatistics.recordTurnInJailPlayer(player.getId());
    }
}

void Game::_setupGameStatistics() {
    _gameStatistics.setPlayerCount(_players.size());
    _gameStatistics.setSquareCount(_board->getBoardSize());
}

void Game::_printStatistics() const {
    std::cout << std::endl << "========== Game Statistics ==========" << std::endl;
    std::cout << "\nTurns spent in Jail per player:" << std::endl;
    for (unsigned int i = 0; i < _players.size(); ++i) {
        std::cout << "\t" << _players[i].getDescription() << ": " << _gameStatistics.getTurnsSpentInJailPlayer(_players[i].getId()) << std::endl;
    }

    std::cout << "\nTimes jailed per player:" << std::endl;
    for (unsigned int i = 0; i < _players.size(); ++i) {
        std::cout << "\t" << _players[i].getDescription() << ": " << _gameStatistics.getTimesJailedPlayer(_players[i].getId()) << std::endl;
    }

    std::cout << "\nTotal turns per player:" << std::endl;
    for (unsigned int i = 0; i < _players.size(); ++i) {
        std::cout << "\t" << _players[i].getDescription() << ": " << _gameStatistics.getTotalTurnsPlayer(_players[i].getId()) << std::endl;
    }
    
    std::cout << "\nTotal dice rolls per player:" << std::endl;
    for (unsigned int i = 0; i < _players.size(); ++i) {
        std::cout << "\t" << _players[i].getDescription() << ": " << _gameStatistics.getTotalDiceRollsPlayer(_players[i].getId()) << std::endl;
    }

    std::cout << "\nTotal doubles rolled per player:" << std::endl;
    for (unsigned int i = 0; i < _players.size(); ++i) {
        std::cout << "\t" << _players[i].getDescription() << ": " << _gameStatistics.getTotalDoublesRolledPlayer(_players[i].getId()) << std::endl;
    }

    std::cout << "\nTotal landings per square:" << std::endl;
    for (unsigned int i = 0; i < _board->getBoardSize(); ++i) {
        const BaseSquare &square = _board->getSquare(i);
        std::cout << "\t" << square.getName() << " : " << _gameStatistics.getTotalLandingsSquare(i) << std::endl;
    }

}

void Game::runSimulation(unsigned int numTurns) {
    if (_players.empty() || _board == nullptr) {
        if (_players.empty()) {
            std::cerr << "No players to simulate." << std::endl;
        }
        if (_board == nullptr) {
            std::cerr << "No board to simulate." << std::endl;
        }
        return ;
    }
    _setupGameStatistics();

    for (unsigned int turn = 0; turn < numTurns; ++turn) {
        if (turn > 0) {
            std::cout << std::endl;
        }
        std::cout << "========== Turn " << (turn + 1) << " ==========" << std::endl;
        Player &currentPlayer = _players[_currentPlayerIndex];
        _playPlayerTurn(currentPlayer);

        _currentPlayerIndex = (_currentPlayerIndex + 1) % _players.size();
    }
    this->_printStatistics();
}
