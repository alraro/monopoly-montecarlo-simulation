#include <fstream>
#include "Game.hpp"
#include "Squares.hpp"
#include "effects.hpp"
#include "rules.hpp"
#include "Logger.hpp"

Game::Game(const SimulationRules &rules): 
            _rules(rules),
            _board(getBoardFromRules(rules)),
            _players(getPlayersFromRules(rules)),
            _currentPlayerIndex(0),
            _gameStatistics(getGameStatisticsFromRules(rules)),
            _dice()
{
    if (_players.empty()) {
        throw std::runtime_error("No players provided in the simulation rules.");
    }

    if (_board.squares.empty()) {
        throw std::runtime_error("No squares provided in the simulation rules.");
    }
}

void Game::_sendPlayerToJail(Player &player) {
    player.sendToJail(_board.jailSquareIndex);

    this->_gameStatistics.recordTimesJailedPlayer(player.id);
    Logger::debug("[DEBUG] Player ", _rules.players[player.id].name, "'s times jailed count is now ", _gameStatistics.getPlayerStats(player.id).timesJailed);

    Logger::info("Player ", _rules.players[player.id].name, " is sent to Jail!");
}

SquareEffectResult Game::_movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll) {
    player.moveToSquare((player.currentSquare + diceRoll.total()) % _board.squares.size());
    const Square &currentSquare = _board.squares[player.currentSquare];

    this->_gameStatistics.recordLandingSquare(player.currentSquare);

    Logger::info("Player ", _rules.players[player.id].name, " landed on square ", player.currentSquare, " (", _rules.squares[player.currentSquare].name, ").");

    SquareEffectResult effect = getSquareEffect(currentSquare, player, _rules);
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
        case SquareEffectType::Pay:
            // Handle pay effect if needed
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
    Logger::debug("[DEBUG] Player ", _rules.players[player.id].name, "'s turn count is now ", _gameStatistics.getPlayerStats(player.id).totalTurns);
    Logger::info("Player ", _rules.players[player.id].name, "'s turn.");
    
    MonopolyDiceRollResult diceRoll = this->_dice.rollMonopolyDice();
    this->_gameStatistics.recordDiceRollPlayer(player.id, diceRoll);

    Logger::info("Player ", _rules.players[player.id].name, " rolled a ", diceRoll.total(), " (", diceRoll.die1, " + ", diceRoll.die2, ") || ", (diceRoll.areDoubles() ? "DOUBLES!" : "No Doubles"));

    if (diceRoll.areDoubles()) {
        _playPlayerTurnDoubles(player, diceRoll);
    } else {
        _playPlayerTurnNoDoubles(player, diceRoll);
    }

    if (player.turnsLeftInJail > 0) {
        this->_gameStatistics.recordTurnInJailPlayer(player.id);
    }
}

void Game::printStatistics() const {
    Logger::info("\n========== Game Statistics ==========");
    
    Logger::info("\n--- Player Statistics ---");
    for (const auto &player : _players) {
        const PlayerStats &stats = _gameStatistics.getPlayerStats(player.id);
        Logger::info("Player ", _rules.players[player.id].name, " (ID: ", player.id, "):");
        Logger::info("  Total Turns: ", stats.totalTurns);
        Logger::info("  Turns Spent in Jail: ", stats.turnsSpentInJail);
        Logger::info("  Times Jailed: ", stats.timesJailed);
        Logger::info("  Total Dice Rolls: ", stats.totalDiceRolls);
        Logger::info("  Total Doubles Rolled: ", stats.totalDoublesRolled);
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
        file << _rules.squares[i].name << ","
             << _gameStatistics.getSquareLandings(i) << "\n";
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
        PlayerStats stats = _gameStatistics.getPlayerStats(player.id);
        file << player.id << ","
             << _rules.players[player.id].name << ","
             << stats.totalTurns << ","
             << stats.turnsSpentInJail << ","
             << stats.timesJailed << ","
             << stats.totalDiceRolls << ","
             << stats.totalDoublesRolled << "\n";
    }
    file.close();
}

void Game::play(size_t numTurns) {
    Logger::info("Starting simulation with ", numTurns, " turns.");

    for (size_t turn = 0; turn < numTurns; ++turn) {
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

Board getBoardFromRules(const SimulationRules &rules) {
    Board board;
    board.squares.reserve(rules.squares.size());
    for (const auto &squareInfo : rules.squares) {
        Square square;
        switch (squareInfo.type) {
            case SquareType::Property:
                square = PropertySquare{};
                break;
            case SquareType::Community:
                square = CommunitySquare{};
                break;
            case SquareType::GoToJail:
                square = GoToJailSquare{};
                break;
            case SquareType::Jail:
                square = JailSquare{};
                board.jailSquareIndex = board.squares.size();
                break;
            case SquareType::Luck:
                square = LuckSquare{};
                break;
            case SquareType::Parking:
                square = ParkingSquare{};
                break;
            case SquareType::Start:
                square = StartSquare{};
                break;
        }
        board.squares.push_back(square);
    }
    return board;
}

GameStatistics getGameStatisticsFromRules(const SimulationRules &rules) {
    return GameStatistics(rules.players.size(), rules.squares.size());
}

std::vector<Player> getPlayersFromRules(const SimulationRules &rules) {
    std::vector<Player> players;
    players.reserve(rules.players.size());
    for (const auto &playerInfo : rules.players) {
        Player player;
        player.id = playerInfo.id;
        players.push_back(player);
    }
    return players;
}
