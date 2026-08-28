#include "Game.hpp"
#include "utils.hpp"
#include "BoardFactory.hpp"
#include "effects.hpp"
#include "rules.hpp"
#include <fstream>
#include "Logger.hpp"

Game::Game(): _board(nullptr), _players(), _currentPlayerIndex(0), _gameStatistics() {}

Game &Game::clear() {
    clearBoard();
    clearPlayers();
    return *this;
}

Game &Game::addPlayer(const std::string &name) {
    _players.emplace_back(_players.size(), name, 0, rules::STARTING_MONEY);
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
    Logger::debug("[DEBUG] Player ", player.getDescription(), "'s times jailed count is now ", _gameStatistics.getTimesJailedPlayer(player.getId()));

    Logger::info("Player ", player.getDescription(), " is sent to Jail!");
}

SquareEffectResult Game::_movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll) {
    player.setCurrentSquare((player.getCurrentSquare() + diceRoll.total) % _board->getBoardSize());
    const BaseSquare &currentSquare = _board->getSquare(player.getCurrentSquare());

    this->_gameStatistics.recordLandingSquare(player.getCurrentSquare());

    Logger::info("Player ", player.getDescription(), " landed on square ", player.getCurrentSquare(), " (", currentSquare.getName(), ").");

    SquareEffectResult effect = currentSquare.getSquareEffect(player);
    switch (effect.type) {
        case SquareEffectType::GoToJail:
            _sendPlayerToJail(player);
            break;
        case SquareEffectType::None:
            // No special effect
            break;
        case SquareEffectType::Move:
            // Handle move effect if needed
            break;
    }
    return effect;
}

void Game::_playPlayerTurnDoubles(Player &player, MonopolyDiceRollResult diceRoll) {
    bool wasInJail = player.isInJail();

    if (player.isInJail()) {
        Logger::info("Player ", player.getDescription(), " is in Jail and rolled doubles to get out!");
        player.resetTurnsLeftInJail();
    } else {
        player.incrementDoublesRolled();
    }

    if (player.getDoublesRolledInARow() >= rules::DOUBLES_TO_JAIL) {
        Logger::info("Player ", player.getDescription(), " rolled doubles three times in a row and is sent to Jail!");
        _sendPlayerToJail(player);
    } else {
        SquareEffectResult appliedEffect = _movePlayerDiceRoll(player, diceRoll);

        if (!wasInJail && appliedEffect.type != SquareEffectType::GoToJail) {
            Logger::info("Player ", player.getDescription(), " rolled doubles and gets another turn!");
            _playPlayerTurn(player);
        }
    }
}

void Game::_playPlayerTurnNoDoubles(Player &player, MonopolyDiceRollResult diceRoll) {
    player.resetDoublesRolled();
    SquareEffectResult appliedEffect;
    appliedEffect.type = SquareEffectType::None;
    appliedEffect.value = 0;

    if (player.isInJail()) {
        Logger::info("Player ", player.getDescription(), " is in Jail and did not roll doubles.");
    } else {
        appliedEffect = _movePlayerDiceRoll(player, diceRoll);
    }
    if (appliedEffect.type != SquareEffectType::GoToJail) {
        player.decrementTurnsLeftInJail();
    }
}

void Game::_playPlayerTurn(Player &player) {
    this->_gameStatistics.recordTurnPlayer(player.getId());
    Logger::debug("[DEBUG] Player ", player.getDescription(), "'s turn count is now ", _gameStatistics.getTotalTurnsPlayer(player.getId()));
    Logger::info("Player ", player.getDescription(), "'s turn.");
    
    MonopolyDiceRollResult diceRoll = rollMonopolyDice();
    this->_gameStatistics.recordDiceRollPlayer(player.getId(), diceRoll);

    Logger::info("Player ", player.getDescription(), " rolled a ", diceRoll.total, " (", diceRoll.die1, " + ", diceRoll.die2, ") || ", (diceRoll.doubles ? "DOUBLES!" : "No Doubles"));

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

void Game::printStatistics() const {
    Logger::info("\n========== Game Statistics ==========");
    Logger::info("\nTurns spent in Jail per player:");
    for (unsigned int i = 0; i < _players.size(); ++i) {
        Logger::info("\t", _players[i].getDescription(), ": ", _gameStatistics.getTurnsSpentInJailPlayer(_players[i].getId()));
    }

    Logger::info("\nTimes jailed per player:");
    for (unsigned int i = 0; i < _players.size(); ++i) {
        Logger::info("\t", _players[i].getDescription(), ": ", _gameStatistics.getTimesJailedPlayer(_players[i].getId()));
    }

    Logger::info("\nTotal turns per player:");
    for (unsigned int i = 0; i < _players.size(); ++i) {
        Logger::info("\t", _players[i].getDescription(), ": ", _gameStatistics.getTotalTurnsPlayer(_players[i].getId()));
    }
    
    Logger::info("\nTotal dice rolls per player:");
    for (unsigned int i = 0; i < _players.size(); ++i) {
        Logger::info("\t", _players[i].getDescription(), ": ", _gameStatistics.getTotalDiceRollsPlayer(_players[i].getId()));
    }

    Logger::info("\nTotal doubles rolled per player:");
    for (unsigned int i = 0; i < _players.size(); ++i) {
        Logger::info("\t", _players[i].getDescription(), ": ", _gameStatistics.getTotalDoublesRolledPlayer(_players[i].getId()));
    }

    Logger::info("\nTotal landings per square:");
    for (unsigned int i = 0; i < _board->getBoardSize(); ++i) {
        const BaseSquare &square = _board->getSquare(i);
        Logger::info("\t", square.getName(), " : ", _gameStatistics.getTotalLandingsSquare(i));
    }

}

void Game::exportSquaresStatisticsToCSV(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        Logger::error("Failed to open squares file for writing: ", filename);
        return;
    }

    file << "square_name,total_landings\n";
    for (unsigned int i = 0; i < _board->getBoardSize(); ++i) {
        const BaseSquare &square = _board->getSquare(i);
        file << square.getName() << ","
             << _gameStatistics.getTotalLandingsSquare(i) << "\n";
    }
    file.close();
}

void Game::exportPlayersStatisticsToCSV(const std::string &filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        Logger::error("Failed to open players file for writing: ", filename);
        return;
    }

    file << "player_id,player_name,total_turns,turns_spent_in_jail,times_jailed,total_dice_rolls,total_doubles_rolled\n";
    for (const auto &player : _players) {
        unsigned int playerId = player.getId();
        file << playerId << ","
             << player.getName() << ","
             << _gameStatistics.getTotalTurnsPlayer(playerId) << ","
             << _gameStatistics.getTurnsSpentInJailPlayer(playerId) << ","
             << _gameStatistics.getTimesJailedPlayer(playerId) << ","
             << _gameStatistics.getTotalDiceRollsPlayer(playerId) << ","
             << _gameStatistics.getTotalDoublesRolledPlayer(playerId) << "\n";
    }
    file.close();


}

void Game::runSimulation(unsigned int numTurns) {
    if (_players.empty() || _board == nullptr) {
        if (_players.empty()) {
            Logger::error("No players to simulate.");
        }
        if (_board == nullptr) {
            Logger::error("No board to simulate.");
        }
        return ;
    }
    _setupGameStatistics();

    Logger::info("Starting simulation with ", numTurns, " turns.");

    for (unsigned int turn = 0; turn < numTurns; ++turn) {
        if (turn > 0) {
            Logger::info("");
        }
        Logger::info("========== Turn ", (turn + 1), " ==========");
        Logger::progress(turn, numTurns);
        Player &currentPlayer = _players[_currentPlayerIndex];
        _playPlayerTurn(currentPlayer);

        _currentPlayerIndex = (_currentPlayerIndex + 1) % _players.size();
    }
}
