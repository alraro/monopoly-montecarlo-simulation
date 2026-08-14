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
        std::cout << "Turn " << (turnsPlayed + 1) << ": Player " << _players[_currentPlayerIndex]->getName() << "'s turn." << std::endl;
        unsigned int diceRoll = rollDice(2, 6); // Roll two six-sided dice
        std::cout << "Player " << _players[_currentPlayerIndex]->getName() << " rolled a " << diceRoll << std::endl;

        Player *currentPlayer = _players[_currentPlayerIndex];
        currentPlayer->setCurrentSquare((currentPlayer->getCurrentSquare() + diceRoll) % _board->getBoardSize());

        BaseSquare *currentSquare = _board->getSquare(currentPlayer->getCurrentSquare());

        EffectResult effect = currentSquare->landOn(*currentPlayer);
        switch (effect.type) {
            case GO_TO_JAIL:
                currentPlayer->setCurrentSquare(_board->getJailSquareIndex());
                _board->getSquare(_board->getJailSquareIndex())->landOn(*currentPlayer); // Land on Jail square
                std::cout << "Player " << currentPlayer->getName() << " is sent to Jail!" << std::endl;
                break;
            case NONE:
                // No special effect
                break;
            default:
                std::cerr << "Unknown effect type encountered." << std::endl;
                break;
        }
        std::cout << "Player " << currentPlayer->getName() << " landed on " << currentSquare->getName() << std::endl;

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