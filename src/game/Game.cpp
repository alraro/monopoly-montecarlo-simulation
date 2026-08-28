#include "Game.hpp"
#include "utils.hpp"
#include "Squares.hpp"
#include "effects.hpp"
#include "rules.hpp"
#include <fstream>
#include "Logger.hpp"

Game::Game(const SimulationRules &rules): 
            _rules(rules),
            _board(getBoardFromRules(rules)),
            _players(getPlayersFromRules(rules)),
            _currentPlayerIndex(0),
            _gameStatistics(getGameStatisticsFromRules(rules)) {}

void Game::_sendPlayerToJail(Player &player) {
    player.currentSquare = _board.jailSquareIndex;
    player.turnsLeftInJail = rules::TURNS_IN_JAIL;
    player.doublesRolledInARow = 0;

    this->_gameStatistics.recordTimesJailedPlayer(player.id);
    Logger::debug("[DEBUG] Player ", _rules.players[player.id].name, "'s times jailed count is now ", _gameStatistics.getTimesJailedPlayer(player.id));

    Logger::info("Player ", _rules.players[player.id].name, " is sent to Jail!");
}

SquareEffectResult Game::_movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll) {
    player.currentSquare = ((player.currentSquare + diceRoll.total) % _board.squares.size());
    const Square &currentSquare = _board.squares[player.currentSquare];

    this->_gameStatistics.recordLandingSquare(player.currentSquare);

    Logger::info("Player ", _rules.players[player.id].name, " landed on square ", player.currentSquare, " (", _rules.squares[player.currentSquare].name, ").");

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
    bool wasInJail = player.turnsLeftInJail > 0;

    if (player.turnsLeftInJail > 0) {
        Logger::info("Player ", _rules.players[player.id].name, " is in Jail and rolled doubles to get out!");
        player.turnsLeftInJail = 0;
    } else {
        player.doublesRolledInARow++;
    }

    if (player.doublesRolledInARow >= rules::DOUBLES_TO_JAIL) {
        Logger::info("Player ", _rules.players[player.id].name, " rolled doubles three times in a row and is sent to Jail!");
        _sendPlayerToJail(player);
    } else {
        SquareEffectResult appliedEffect = _movePlayerDiceRoll(player, diceRoll);

        if (!wasInJail && appliedEffect.type != SquareEffectType::GoToJail) {
            Logger::info("Player ", _rules.players[player.id].name, " rolled doubles and gets another turn!");
            _playPlayerTurn(player);
        }
    }
}

void Game::_playPlayerTurnNoDoubles(Player &player, MonopolyDiceRollResult diceRoll) {
    player.doublesRolledInARow = 0;
    SquareEffectResult appliedEffect;
    appliedEffect.type = SquareEffectType::None;
    appliedEffect.value = 0;

    if (player.turnsLeftInJail > 0) {
        Logger::info("Player ", _rules.players[player.id].name, " is in Jail and did not roll doubles.");
    } else {
        appliedEffect = _movePlayerDiceRoll(player, diceRoll);
    }
    if (appliedEffect.type != SquareEffectType::GoToJail) {
        player.turnsLeftInJail = std::max(0, player.turnsLeftInJail - 1);
    }
}

void Game::_playPlayerTurn(Player &player) {
    this->_gameStatistics.recordTurnPlayer(player.id);
    Logger::debug("[DEBUG] Player ", _rules.players[player.id].name, "'s turn count is now ", _gameStatistics.getTotalTurnsPlayer(player.id));
    Logger::info("Player ", _rules.players[player.id].name, "'s turn.");
    
    MonopolyDiceRollResult diceRoll = rollMonopolyDice();
    this->_gameStatistics.recordDiceRollPlayer(player.id, diceRoll);

    Logger::info("Player ", _rules.players[player.id].name, " rolled a ", diceRoll.total, " (", diceRoll.die1, " + ", diceRoll.die2, ") || ", (diceRoll.doubles ? "DOUBLES!" : "No Doubles"));

    if (diceRoll.doubles) {
        _playPlayerTurnDoubles(player, diceRoll);
    } else {
        _playPlayerTurnNoDoubles(player, diceRoll);
    }

    if (player.turnsLeftInJail > 0) {
        this->_gameStatistics.recordTurnInJailPlayer(player.id);
    }
}

void Game::_setupGameStatistics() {
    _gameStatistics.setPlayerCount(_players.size());
    _gameStatistics.setSquareCount(_board.squares.size());
}

void Game::printStatistics() const {
    Logger::info("\n========== Game Statistics ==========");
    Logger::info("\nTurns spent in Jail per player:");
    for (unsigned int i = 0; i < _players.size(); ++i) {
        Logger::info("\t", _rules.players[_players[i].id].name, ": ", _gameStatistics.getTurnsSpentInJailPlayer(_players[i].id));
    }

    Logger::info("\nTimes jailed per player:");
    for (unsigned int i = 0; i < _players.size(); ++i) {
        Logger::info("\t", _rules.players[_players[i].id].name, ": ", _gameStatistics.getTimesJailedPlayer(_players[i].id));
    }

    Logger::info("\nTotal turns per player:");
    for (unsigned int i = 0; i < _players.size(); ++i) {
        Logger::info("\t", _rules.players[_players[i].id].name, ": ", _gameStatistics.getTotalTurnsPlayer(_players[i].id));
    }
    
    Logger::info("\nTotal dice rolls per player:");
    for (unsigned int i = 0; i < _players.size(); ++i) {
        Logger::info("\t", _rules.players[_players[i].id].name, ": ", _gameStatistics.getTotalDiceRollsPlayer(_players[i].id));
    }

    Logger::info("\nTotal doubles rolled per player:");
    for (unsigned int i = 0; i < _players.size(); ++i) {
        Logger::info("\t", _rules.players[_players[i].id].name, ": ", _gameStatistics.getTotalDoublesRolledPlayer(_players[i].id));
    }

    Logger::info("\nTotal landings per square:");
    for (unsigned int i = 0; i < _board.squares.size(); ++i) {
        const Square &square = _board.squares[i];
        Logger::info("\t", _rules.squares[i].name, " : ", _gameStatistics.getTotalLandingsSquare(i));
    }

}

void Game::exportSquaresStatisticsToCSV(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        Logger::error("Failed to open squares file for writing: ", filename);
        return;
    }

    file << "square_name,total_landings\n";
    for (unsigned int i = 0; i < _board.squares.size(); ++i) {
        const Square &square = _board.squares[i];
        file << _rules.squares[i].name << ","
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
        unsigned int playerId = player.id;
        file << playerId << ","
             << _rules.players[playerId].name << ","
             << _gameStatistics.getTotalTurnsPlayer(playerId) << ","
             << _gameStatistics.getTurnsSpentInJailPlayer(playerId) << ","
             << _gameStatistics.getTimesJailedPlayer(playerId) << ","
             << _gameStatistics.getTotalDiceRollsPlayer(playerId) << ","
             << _gameStatistics.getTotalDoublesRolledPlayer(playerId) << "\n";
    }
    file.close();


}

void Game::play(unsigned int numTurns) {
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
