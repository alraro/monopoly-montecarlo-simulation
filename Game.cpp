#include "Game.hpp"
#include "utils.hpp"
#include "BoardFactory.hpp"
#include "effectType.hpp"
#include <iostream>

Game::Game(): _board(NULL), _players(), _currentPlayerIndex(0) {}

Game::Game(const Game &other): _board(NULL), _players(), _currentPlayerIndex(other._currentPlayerIndex) {
    if (other._board != NULL) {
        this->_board = new Board(*other._board);
    }
    for (std::vector<Player *>::const_iterator it = other._players.begin(); it != other._players.end(); ++it) {
        this->_players.push_back(new Player(**it));
    }
}

Game &Game::operator=(const Game &other) {
    if (this != &other) {
        delete _board;
        _board = NULL;
        for (std::vector<Player *>::iterator it = _players.begin(); it != _players.end(); ++it) {
            delete *it;
        }
        _players.clear();
        _currentPlayerIndex = other._currentPlayerIndex;

        if (other._board != NULL) {
            this->_board = new Board(*other._board);
        }
        for (std::vector<Player *>::const_iterator it = other._players.begin(); it != other._players.end(); ++it) {
            this->_players.push_back(new Player(**it));
        }
    }
    return *this;
}

Game::~Game() {
    delete _board;
    for (std::vector<Player *>::iterator it = _players.begin(); it != _players.end(); ++it) {
        delete *it;
    }
}

Game &Game::clear() {
    delete _board;
    _board = NULL;
    for (std::vector<Player *>::iterator it = _players.begin(); it != _players.end(); ++it) {
        delete *it;
    }
    _players.clear();
    _currentPlayerIndex = 0;
    return *this;
}

Game &Game::addPlayer(const Player &player) {
    _players.push_back(new Player(player));
    return *this;
}

Game &Game::addPlayer(const std::string &name) {
    return Game::addPlayer(Player(name, 0));
}

Game &Game::clearPlayers() {
    for (std::vector<Player *>::iterator it = _players.begin(); it != _players.end(); ++it) {
        delete *it;
    }
    _players.clear();
    _currentPlayerIndex = 0;
    return *this;
}

Game &Game::setBoard(const Board &board) {
    delete _board;
    _board = new Board(board);
    return *this;
}

Game &Game::setDefaultBoard() {
    delete _board;
    _board = new Board(BoardFactory::createDefaultBoard());
    return *this;
}

Game &Game::clearBoard() {
    delete _board;
    _board = NULL;
    return *this;
}

void Game::_sendPlayerToJail(Player &player) {
    player.setCurrentSquare(_board->getJailSquareIndex());
    _board->getSquare(_board->getJailSquareIndex())->landOn(player);
    player.getJailed();
    std::cout << "Player " << player.getName() << " is sent to Jail!" << std::endl;
}

EffectResult Game::_movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll) {
    player.setCurrentSquare((player.getCurrentSquare() + diceRoll.total) % _board->getBoardSize());
    BaseSquare *currentSquare = _board->getSquare(player.getCurrentSquare());

    std::cout << "Player " << player.getName() << " landed on square " << player.getCurrentSquare() << " (" << currentSquare->getName() << ")." << std::endl;

    EffectResult effect = currentSquare->landOn(player);
    switch (effect.type) {
        case GO_TO_JAIL:
            _sendPlayerToJail(player);
            break;
        case NONE:
            // No special effect
            break;
        default:
            std::cerr << "Unknown effect type encountered." << std::endl;
            break;
    }
    return effect;
}

void Game::_playPlayerTurnDoubles(Player &player, MonopolyDiceRollResult diceRoll) {
    bool wasInJail = player.isInJail();

    if (player.isInJail()) {
        std::cout << "Player " << player.getName() << " is in Jail and rolled doubles to get out!" << std::endl;
        player.setTurnsLeftInJail(0);
    }

    player.incrementDoublesRolled();

    if (player.getDoublesRolledInARow() >= 3) {
        std::cout << "Player " << player.getName() << " rolled doubles three times in a row and is sent to Jail!" << std::endl;
        _sendPlayerToJail(player);
        player.resetDoublesRolled();
    } else {
        EffectResult appliedEffect = _movePlayerDiceRoll(player, diceRoll);

        if (!wasInJail && appliedEffect.type != GO_TO_JAIL) {
            std::cout << "Player " << player.getName() << " rolled doubles and gets another turn!" << std::endl;
            _playPlayerTurn(player);
        }
    }
}

void Game::_playPlayerTurnNoDoubles(Player &player, MonopolyDiceRollResult diceRoll) {
    player.resetDoublesRolled();
    EffectResult appliedEffect = NONE;

    if (player.isInJail()) {
        std::cout << "Player " << player.getName() << " is in Jail and did not roll doubles." << std::endl;
    } else {
        appliedEffect = _movePlayerDiceRoll(player, diceRoll);
    }
    if (appliedEffect.type != GO_TO_JAIL) {
        player.decrementTurnsLeftInJail();
    }
}

void Game::_playPlayerTurn(Player &player) {
    std::cout << "Turn " << (turnsPlayed + 1) << ": Player " << player.getName() << "'s turn." << std::endl;

    MonopolyDiceRollResult diceRoll = rollMonopolyDice();
    std::cout << "Player " << player.getName() << " rolled a " << diceRoll.total << " (" << diceRoll.die1 << " + " << diceRoll.die2 << ") || " << (diceRoll.doubles ? "DOUBLES!" : "No Doubles") << std::endl;

    if (diceRoll.doubles) {
        _playPlayerTurnDoubles(player, diceRoll);
    } else {
        _playPlayerTurnNoDoubles(player, diceRoll);
    }
}

void Game::runSimulation(unsigned int numTurns) {
    if (_players.empty() || _board == NULL) {
        if (_players.empty()) {
            std::cerr << "No players to simulate." << std::endl;
        }
        if (_board == NULL) {
            std::cerr << "No board to simulate." << std::endl;
        }
    }

    unsigned int turnsPlayed = 0;
    while (turnsPlayed < numTurns) {
        Player *currentPlayer = _players[_currentPlayerIndex];
        _playPlayerTurn(currentPlayer);

        _currentPlayerIndex = (_currentPlayerIndex + 1) % _players.size();
        ++turnsPlayed;
    }
    _showSquareLandingInfo();
}

void Game::_showSquareLandingInfo() {
    if (_board == NULL) {
        std::cerr << "No board to show square landing info." << std::endl;
        return;
    }

    std::cout << "\n==========Square Landing Info===========\n" << std::endl;
    for (unsigned int i = 0; i < _board->getBoardSize(); ++i) {
        BaseSquare *square = _board->getSquare(i);
        std::cout << "Square " << i << " (" << square->getName() << ") was landed on " << square->getTimesLandedOn() << " times." << std::endl;
    }
}