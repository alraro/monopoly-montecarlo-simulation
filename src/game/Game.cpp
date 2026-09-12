#include <cassert>
#include <fstream>
#include <string>
#include "Game.hpp"
#include "Squares.hpp"
#include "effects.hpp"
#include "rules.hpp"
#include "Logger.hpp"
#include <filesystem>
#include <string_view>
#include <system_error>
#include <format>

Game::Game(const SimulationConfig &config, GameId gameId, std::atomic<bool> &shouldStop) : 
            _shouldStop(shouldStop),
            _config(config),
            _gameId(gameId),
            _board(getBoardFromRules(config)),
            _players(getPlayersFromRules(config)),
            _currentPlayerIndex(0),
            _gameStatistics(getGameStatisticsFromRules(config)),
            _dice()
{
    assert(!_players.empty() && "Precondition failed: There must be at least one player in the game.");
    assert(!_board.squares.empty() && "Precondition failed: There must be at least one square on the board.");
}

void Game::_sendPlayerToJail(Player &player) {
    player.sendToJail(_board.jailSquareIndex);

    this->_gameStatistics.recordTimesJailedPlayer(player.id);
    Logger::debug("[DEBUG] Player ", _config.players[player.id].name, "'s times jailed count is now ", _gameStatistics.getPlayerStats(player.id).timesJailed);

    Logger::info("Player ", _config.players[player.id].name, " is sent to Jail!");
}

SquareEffectResult Game::_movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll) {
    player.moveToSquare(static_cast<SquareId>((player.currentSquare + diceRoll.total()) % _board.squares.size()));
    const Square &currentSquare = _board.squares[player.currentSquare];

    this->_gameStatistics.recordLandingSquare(player.currentSquare);

    Logger::info("Player ", _config.players[player.id].name, " landed on square ", player.currentSquare, " (", _config.squares[player.currentSquare].name, ").");

    SquareEffectResult effect = getSquareEffect(currentSquare, player, _config);
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
        Logger::info("Player ", _config.players[player.id].name, " is in Jail and rolled doubles to get out!");
        player.turnsLeftInJail = 0;
    } else {
        player.doublesRolledInARow++;
    }

    if (player.doublesRolledInARow >= rules::DOUBLES_TO_JAIL) {
        Logger::info("Player ", _config.players[player.id].name, " rolled doubles three times in a row and is sent to Jail!");
        _sendPlayerToJail(player);
    } else {
        SquareEffectResult appliedEffect = _movePlayerDiceRoll(player, diceRoll);

        if (!wasInJail && appliedEffect.type != SquareEffectType::GoToJail) {
            Logger::info("Player ", _config.players[player.id].name, " rolled doubles and gets another turn!");
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
        Logger::info("Player ", _config.players[player.id].name, " is in Jail and did not roll doubles.");
    } else {
        appliedEffect = _movePlayerDiceRoll(player, diceRoll);
    }
    if (appliedEffect.type != SquareEffectType::GoToJail) {
        player.turnsLeftInJail = static_cast<int8_t>(std::max(0, player.turnsLeftInJail - 1));
    }
}

void Game::_playPlayerTurn(Player &player) {
    this->_gameStatistics.recordTurnPlayer(player.id);
    Logger::debug("[DEBUG] Player ", _config.players[player.id].name, "'s turn count is now ", _gameStatistics.getPlayerStats(player.id).totalTurns);
    Logger::info("Player ", _config.players[player.id].name, "'s turn.");
    
    MonopolyDiceRollResult diceRoll = this->_dice.rollMonopolyDice();
    this->_gameStatistics.recordDiceRollPlayer(player.id, diceRoll);

    Logger::info("Player ", _config.players[player.id].name, " rolled a ", diceRoll.total(), " (", diceRoll.die1, " + ", diceRoll.die2, ") || ", (diceRoll.areDoubles() ? "DOUBLES!" : "No Doubles"));

    if (diceRoll.areDoubles()) {
        _playPlayerTurnDoubles(player, diceRoll);
    } else {
        _playPlayerTurnNoDoubles(player, diceRoll);
    }

    if (player.turnsLeftInJail > 0) {
        this->_gameStatistics.recordTurnInJailPlayer(player.id);
    }
}

void Game::_printStatistics() const {
    Logger::info("\n========== Game Statistics ==========");
    
    Logger::info("\n--- Player Statistics ---");
    for (const auto &player : _players) {
        const PlayerStats &stats = _gameStatistics.getPlayerStats(player.id);
        Logger::info("Player ", _config.players[player.id].name, " (ID: ", player.id, "):");
        Logger::info("  Total Turns: ", stats.totalTurns);
        Logger::info("  Turns Spent in Jail: ", stats.turnsSpentInJail);
        Logger::info("  Times Jailed: ", stats.timesJailed);
        Logger::info("  Total Dice Rolls: ", stats.totalDiceRolls);
        Logger::info("  Total Doubles Rolled: ", stats.totalDoublesRolled);
    }

}

std::ofstream Game::_createStatsFile(std::string_view fileName) const {
    std::error_code ec;

    std::filesystem::path dirPath = std::filesystem::path(_config.baseDir) / _config.simulationName / std::format("game_{:04d}", _gameId); 
    std::filesystem::create_directories(dirPath, ec);

    if (ec) {
        Logger::error("Failed to create game directory: ", _config.baseDir + "/" + _config.simulationName + "/game_" + std::to_string(_gameId), ". Error: ", ec.message());
        return std::ofstream();
    }

    std::ofstream file(dirPath / fileName);
    if (!file.is_open()) {
        Logger::error("Failed to open file for writing: ", dirPath / fileName);
        return std::ofstream();
    }

    return file;
}

void Game::_exportSquaresStatisticsToCSV(std::string_view fileName) const {
    std::ofstream file = _createStatsFile(fileName);
    if (!file.is_open()) {
        return;
    }

    file << "square_name,total_landings\n";
    for (unsigned int i = 0; i < _board.squares.size(); ++i) {
        file << _config.squares[i].name << ","
             << _gameStatistics.getSquareLandings(i) << "\n";
    }
    file.close();
}

void Game::_exportPlayersStatisticsToCSV(std::string_view fileName) const {
    std::ofstream file = _createStatsFile(fileName);
    if (!file.is_open()) {
        return;
    }

    file << "player_id,player_name,total_turns,turns_spent_in_jail,times_jailed,total_dice_rolls,total_doubles_rolled\n";
    for (const auto &player : _players) {
        PlayerStats stats = _gameStatistics.getPlayerStats(player.id);
        file << player.id << ","
             << _config.players[player.id].name << ","
             << stats.totalTurns << ","
             << stats.turnsSpentInJail << ","
             << stats.timesJailed << ","
             << stats.totalDiceRolls << ","
             << stats.totalDoublesRolled << "\n";
    }
    file.close();
}

void Game::play() {
    Logger::info("Starting simulation with ", _config.turnLimit, " turns.");

    for (size_t turn = 0; turn < _config.turnLimit; ++turn) {
        if (turn > 0) {
            Logger::info("");
        }
        if (this->_shouldStop.load(std::memory_order_relaxed)) {
            return ;
        }
        Logger::info("========== Turn ", (turn + 1), " ==========");
        Logger::progress(turn, _config.turnLimit);
        Player &currentPlayer = _players[_currentPlayerIndex];
        _playPlayerTurn(currentPlayer);

        _currentPlayerIndex = static_cast<PlayerId>((_currentPlayerIndex + 1) % _players.size());
    }

    Logger::info("Simulation completed.");
    if (!_config.exportStatistics)
        return ;

    Logger::info("Storing statistics to CSV files.");
    this->_exportPlayersStatisticsToCSV();
    this->_exportSquaresStatisticsToCSV();
}

Board getBoardFromRules(const SimulationConfig &config) {
    Board board;
    board.squares.reserve(config.squares.size());
    for (const auto &squareInfo : config.squares) {
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
                board.jailSquareIndex = static_cast<SquareId>(board.squares.size());
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

GameStatistics getGameStatisticsFromRules(const SimulationConfig &config) {
    return GameStatistics(config.players.size(), config.squares.size());
}

std::vector<Player> getPlayersFromRules(const SimulationConfig &config) {
    std::vector<Player> players;
    players.reserve(config.players.size());
    for (const auto &playerInfo : config.players) {
        Player player;
        player.id = playerInfo.id;
        players.push_back(player);
    }
    return players;
}
