#include "GameStatistics.hpp"

GameStatistics::GameStatistics()
    : _turnsSpentInJailPerPlayer(0),
      _timesJailedPerPlayer(0),
      _totalTurnsPerPlayer(0),
      _totalDoublesRolledPerPlayer(0),
      _totalDiceRollsPerPlayer(0),
      _totalLandingsPerSquare(0) {}

void GameStatistics::setPlayerCount(unsigned int numPlayers) {
    _turnsSpentInJailPerPlayer.resize(numPlayers, 0);
    _timesJailedPerPlayer.resize(numPlayers, 0);
    _totalTurnsPerPlayer.resize(numPlayers, 0);
    _totalDoublesRolledPerPlayer.resize(numPlayers, 0);
    _totalDiceRollsPerPlayer.resize(numPlayers, 0);
}

void GameStatistics::setSquareCount(unsigned int numSquares) {
    _totalLandingsPerSquare.resize(numSquares, 0);
}

void GameStatistics::recordTurnInJailPlayer(unsigned int playerIndex) {
    ++_turnsSpentInJailPerPlayer[playerIndex];
}

unsigned int GameStatistics::getTurnsSpentInJailPlayer(unsigned int playerIndex) const {
    return _turnsSpentInJailPerPlayer[playerIndex];
}

void GameStatistics::recordTimesJailedPlayer(unsigned int playerIndex) {
  ++_timesJailedPerPlayer[playerIndex];
}

unsigned int GameStatistics::getTimesJailedPlayer(unsigned int playerIndex) const {
    return _timesJailedPerPlayer[playerIndex];
}

void GameStatistics::recordTurnPlayer(unsigned int playerIndex) {
    ++_totalTurnsPerPlayer[playerIndex];
}

unsigned int GameStatistics::getTotalTurnsPlayer(unsigned int playerIndex) const {
    return _totalTurnsPerPlayer[playerIndex];
}

void GameStatistics::recordDiceRollPlayer(unsigned int playerIndex, MonopolyDiceRollResult diceRoll) {
    ++_totalDiceRollsPerPlayer[playerIndex];
    if (diceRoll.doubles) {
        ++_totalDoublesRolledPerPlayer[playerIndex];
    }
}

unsigned int GameStatistics::getTotalDiceRollsPlayer(unsigned int playerIndex) const {
    return _totalDiceRollsPerPlayer[playerIndex];
}

unsigned int GameStatistics::getTotalDoublesRolledPlayer(unsigned int playerIndex) const {
    return _totalDoublesRolledPerPlayer[playerIndex];
}

void GameStatistics::recordLandingSquare(unsigned int squareIndex) {
    ++_totalLandingsPerSquare[squareIndex];
}

unsigned int GameStatistics::getTotalLandingsSquare(unsigned int squareIndex) const {
    return _totalLandingsPerSquare[squareIndex];
}