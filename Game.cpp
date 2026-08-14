#include "Game.hpp"
#include "utils.hpp"
#include "BoardFactory.hpp"
#include "effectType.hpp"
#include <iostream>

Game::Game(): _board(nullptr), _players(), _currentPlayerIndex(0), _timesJailed(0), _turnsSpentInJail(0) {}

Game::Game(const Game &other)
    : _board(other._board ? std::make_unique<Board>(*other._board) : nullptr),
    _players(other._players), 
    _currentPlayerIndex(other._currentPlayerIndex), 
    _timesJailed(other._timesJailed), 
    _turnsSpentInJail(other._turnsSpentInJail) {}

Game &Game::operator=(const Game &other) {
    if (this != &other) {
        _board = other._board ? std::make_unique<Board>(*other._board) : nullptr;
        _players = other._players;
        _currentPlayerIndex = other._currentPlayerIndex;
        _timesJailed = other._timesJailed;
        _turnsSpentInJail = other._turnsSpentInJail;
    }
    return *this;
}

Game &Game::clear() {
    clearBoard();
    clearPlayers();
    _timesJailed = 0;
    _turnsSpentInJail = 0;
    return *this;
}

Game &Game::addPlayer(const Player &player) {
    _players.push_back(player);
    return *this;
}

Game &Game::addPlayer(const std::string &name) {
    _players.emplace_back(name, 0);
    return *this;
}

Game &Game::clearPlayers() {
    _players.clear();
    _currentPlayerIndex = 0;
    return *this;
}

Game &Game::setBoard(std::unique_ptr<Board> board) {
    _board = std::move(board);
    return *this;
}

Game &Game::setDefaultBoard() {
    _board = BoardFactory::createDefaultBoard();
    return *this;
}

Game &Game::clearBoard() {
    _board = nullptr;
    return *this;
}

void Game::_sendPlayerToJail(Player &player) {
    player.setCurrentSquare(_board->getJailSquareIndex());
    player.startTurnsLeftInJailCountdown();
    player.resetDoublesRolled();
    ++_timesJailed;
    std::cout << "Player " << player.getName() << " is sent to Jail!" << std::endl;
}

EffectResult Game::_movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll) {
    player.setCurrentSquare((player.getCurrentSquare() + diceRoll.total) % _board->getBoardSize());
    BaseSquare *currentSquare = _board->getSquare(player.getCurrentSquare());

    std::cout << "Player " << player.getName() << " landed on square " << player.getCurrentSquare() << " (" << currentSquare->getName() << ")." << std::endl;

    EffectResult effect = currentSquare->landOn(player);
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
        std::cout << "Player " << player.getName() << " is in Jail and rolled doubles to get out!" << std::endl;
        player.resetTurnsLeftInJail();
    } else {
        player.incrementDoublesRolled();
    }

    if (player.getDoublesRolledInARow() >= 3) {
        std::cout << "Player " << player.getName() << " rolled doubles three times in a row and is sent to Jail!" << std::endl;
        _sendPlayerToJail(player);
    } else {
        EffectResult appliedEffect = _movePlayerDiceRoll(player, diceRoll);

        if (!wasInJail && appliedEffect.type != EffectType::GoToJail) {
            std::cout << "Player " << player.getName() << " rolled doubles and gets another turn!" << std::endl;
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
        std::cout << "Player " << player.getName() << " is in Jail and did not roll doubles." << std::endl;
    } else {
        appliedEffect = _movePlayerDiceRoll(player, diceRoll);
    }
    if (appliedEffect.type != EffectType::GoToJail) {
        player.decrementTurnsLeftInJail();
    }
}

void Game::_playPlayerTurn(Player &player) {
    if (player.isInJail()) {
        ++_turnsSpentInJail;
    }

    std::cout << "Player " << player.getName() << "'s turn." << std::endl;

    MonopolyDiceRollResult diceRoll = rollMonopolyDice();
    std::cout << "Player " << player.getName() << " rolled a " << diceRoll.total << " (" << diceRoll.die1 << " + " << diceRoll.die2 << ") || " << (diceRoll.doubles ? "DOUBLES!" : "No Doubles") << std::endl;

    if (diceRoll.doubles) {
        _playPlayerTurnDoubles(player, diceRoll);
    } else {
        _playPlayerTurnNoDoubles(player, diceRoll);
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

    for (unsigned int turn = 0; turn < numTurns; ++turn) {
        if (turn > 0) {
            std::cout << std::endl;
        }
        std::cout << "========== Turn " << (turn + 1) << " ==========" << std::endl;
        Player &currentPlayer = _players[_currentPlayerIndex];
        _playPlayerTurn(currentPlayer);

        _currentPlayerIndex = (_currentPlayerIndex + 1) % _players.size();
    }
    _showSquareLandingInfo();
}

void Game::_showSquareLandingInfo() const {
    if (_board == nullptr) {
        std::cerr << "No board to show square landing info." << std::endl;
        return;
    }

    unsigned int totalLandings = 0;

    std::cout << "\n==========Square Landing Info===========\n" << std::endl;
    for (unsigned int i = 0; i < _board->getBoardSize(); ++i) {
        BaseSquare *square = _board->getSquare(i);
        std::cout << "Square " << i << " (" << square->getName() << ") was landed on " << square->getTimesLandedOn() << " times." << std::endl;
        totalLandings += square->getTimesLandedOn();
    }

    std::cout << "\n==========Jail Info===========\n" << std::endl;
    std::cout << "Total landings: " << totalLandings << std::endl;
    std::cout << "Times jailed: " << _timesJailed << std::endl;
    std::cout << "Turns spent in jail: " << _turnsSpentInJail << std::endl;
    if (_timesJailed > 0) {
        std::cout << "Average turns per jailing: "
                  << static_cast<double>(_turnsSpentInJail) / _timesJailed << std::endl;
    }
}