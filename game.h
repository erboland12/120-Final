//
// Created by Sarah McLaughlin on 4/10/18.
//


#ifndef WARRIORSANDWIZARDS_GAME_H
#define WARRIORSANDWIZARDS_GAME_H

#include "string"
#include "vector"
#include "map.h"
#include "players.h"
#include "iostream"
#include "fstream"
#include "istream"

using namespace std;

enum movement {move_up, move_down, move_left, move_right};

class Game {
private:
    int progress;
    string loadFile;


public:
    Player * player;
    Map myMap;

    /**
     * Default Constructor
     * Requires: Nothing
     * Modifies: int progress, vector<Map> Maps
     * Effects: Sets the fields to default values
     */
    Game(string name, int classType);

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Writes to an external text file with information that can be used to load the game at a later time
     */
    void save(string fileName) const;

    /**
     * Requires: string fileName | The name of the file to be loaded
     * Modifies: int progress, vector<Map> Maps
     * Effects: Loads the game from a provided text file
     */
    bool load(string fileName);

    /**
     * Requires: Nothing
     * Modifies: int progress, vector<Map> Maps
     * Effects: Resets the game to a fresh state
     */
    void newGame();

    /**
     * Requires: Square enemySquare | The square that contains the enemy
     * Modifies: The player or monster health and status of fight
     * Effects: Directs a fight by calling the monster & player attack and defends methods while also updating the user
     * the status of the fight
     */
    void fight(Square enemySquare);

    /**
     * Requires: movement direction | The direction that the player is moving
     * Modifies: Player coordinates
     * Effects: Sets the player's coordinates and calls an interact method if they interact with an object
     */
    void move(movement direction);

    void redrawMap();

    /**
     * Getters
     */
    int getProgress() const;
    Player &getPlayer() const;
    const Map &getMap() const;
    string getLoadFile() const;

    /**
     * Setters
     */
    void setPlayer(string name, int classType);
    void setProgress(int progress);
    void setMap(Map myMap);
    void setLoadFile(string loadIn);
    void print();


};


#endif //WARRIORSANDWIZARDS_GAME_H
