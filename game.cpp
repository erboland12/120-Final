//
// Created by Sarah McLaughlin on 4/10/18.
//

#include "game.h"
bool fight;
Game::Game(string name, int classType) {
    newGame();
}


void Game::save(string fileName) const {
    ofstream saveFile;
    saveFile.open(fileName + ".txt");

    vector<string> squareTypes = myMap.save();

    for(int i = 0; i < squareTypes.size(); i++) {
        saveFile << squareTypes[i] << endl;
    }

    saveFile.close();

    cout << "The game has been successfully saved.";
}

void Game::print() {
    cout << player->print();
    cout << "\n";
    cout << progress;

}

bool Game::load(string fileName) {
    player = new Warrior();

    string message;
    int playerPos;

    vector<string> squareTypes;
    string currentLine;
    int counter = 1;


    ifstream loadFile;
    loadFile.open(fileName);

    if (loadFile.is_open()) {
        while (loadFile.is_open()) {
            if (counter <= 81) {
                getline(loadFile, currentLine);

                if (currentLine == "playerSpace") {
                    playerPos = counter;
                }

                squareTypes.push_back(currentLine);
                counter++;
            } else if (counter == 82) {
                loadFile.close();
            }
        }
    } else {
        return false;
    }

    myMap.squareSpaces = squareTypes;

    int playerPosY = playerPos % 8;
    int playerPosX = playerPos / 8;

    player->setXPos(playerPosX);
    player->setYPos(playerPosY);

    myMap.draw(playerPosX, playerPosX);


    return true;


}

void Game::newGame() {

    // Reset map
    myMap.draw(4, 4);

}

void Game::fight(Square enemySquare) {
    int i = 2;

    // Get the enemy in the square
    Monster monster;

    cout << "You have started a fight with " << monster.getName() << "! Good luck." << endl;

    while (monster.getHealth() > 0 && player->getCurrHealth() > 0) {
        // Fight can continue
        if (i % 2 == 0) {
            cout << "Current player health: " << player->getCurrHealth() << endl;
            // Even numbers
            // TODO: Implement attack/defend
            // Player attacks
            int playerHit = player->attack();

            cout << "Player hit: " << playerHit << endl;

            // Monster defends attack

            int monsterDefend = monster.defend();

            cout << "Monster Defend: " << monsterDefend << endl;

            if (playerHit >> monsterDefend) {
                cout << "Player hits monster" << endl;
                monster.changeHealth(-(playerHit - monsterDefend));
                cout << "New monster health: " << monster.getHealth() << endl;

            } else if (playerHit << monsterDefend) {
                cout << "Monster defends from player" << endl;
            } else {
                cout << "Player hit equals monster defend" << endl;
            }

        } else {
            cout << "Current monster health: " << monster.getHealth() << endl;

            // Monster attacks
            int monsterHit = monster.attack();

            cout << "Monster hit: " << monsterHit << endl;

            // Player defends attack
            int playerDefend = player->defend();

            cout << "Player defend: " << playerDefend << endl;

            if (monsterHit > playerDefend) {
                cout << "Monster hits player" << endl;
                player->changeHealth(-(monsterHit - playerDefend));
                cout << "New player health: " << player->getCurrHealth() << endl;
            } else if (playerDefend > monsterHit) {
                cout << "Player defends from monster" << endl;
            } else {
                cout << "Monster hit equals player defend" << endl;
            }
        }
        i++;

        // TODO: Figure out what to do with player and monster if win/lose
    }
}

void Game::move(movement direction) {
    int playerPosX = 0;
    int playerPosY = 0;
    int newPos = 0;
    SquareType squareToMoveToType;

    vector<vector<Square>> map = myMap.getMap();

    for (int x = 0; x < map.size(); x++) {
        for (int y = 0; y < map[x].size(); y++) {
            if (map[x][y].getSquare() == playerSpace) {
                playerPosX = x;
                playerPosY = y;
            }
        }
    }

    // Check to see if there is something in the square that the user wants to move to
    switch (direction) {
        case move_right:
            newPos = playerPosX + 1;
            squareToMoveToType = map.at(newPos).at(playerPosY).square;
            break;
        case move_left:
            newPos = playerPosX - 1;
            squareToMoveToType = map.at(newPos).at(playerPosY).square;
            break;
        case move_up:
            newPos = playerPosY - 1;
            squareToMoveToType = map.at(playerPosX).at(newPos).square;
            break;
        case move_down:
            newPos = playerPosY + 1;
            squareToMoveToType = map.at(playerPosX).at(newPos).square;
            break;
    }

    Square s;
    s.setSquare(monsterSpace);
    switch(squareToMoveToType) {
        case empty:
            // Move the player
            switch (direction) {
                case move_right:
                    iter_swap(map.at(playerPosX).begin() + playerPosY, map.at(newPos).begin() + playerPosY);
                    this->player->setXPos(newPos);
                    break;
                case move_left:
                    iter_swap(map.at(playerPosX).begin() + playerPosY, map.at(newPos).begin() + playerPosY);
                    this->player->setXPos(newPos);
                    break;
                case move_up:
                    iter_swap(map.at(playerPosX).begin() + playerPosY, map.at(playerPosX).begin() + playerPosX);
                    this->player->setYPos(newPos-1);
                    break;
                case move_down:
                    iter_swap(map.at(playerPosX).begin() + playerPosY, map.at(newPos).begin() + playerPosY);
                    this->player->setYPos(newPos-1);
                    break;
            }
            break;
        case wall:
        default:
            break;
    }

    myMap.replaceMap(map);

}

void Game::redrawMap() {
    myMap.draw(player->getXPos(), player->getYPos());
}

int Game::getProgress() const {
    return progress;
}

void Game::setPlayer(string name, int classType) {
    if (classType == 0) {
        this->player = new Warrior(name);
    } else {
        this->player = new Wizard(name);
    }
}


void Game::setProgress(int progress) {
    Game::progress = progress;
}

const Map &Game::getMap() const {
    return myMap;
}

void Game::setMap(Map myMap) {
    Game::myMap = myMap;
}

Player &Game::getPlayer() const {
    return *player;
}
