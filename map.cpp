//
// Created by Sarah McLaughlin on 4/10/18.
//
#include "graphics.h"
#include "map.h"
#include "shapes.h"
#include <fstream>

int tempX;
int tempY;

/** Map Class **/

//Default Constructor
Map::Map(){
    draw(4, 4);
}
//Non-Default Constructor
Map::Map(vector<vector<Square>> mapIn, int xIn, int yIn) {
    x = xIn;
    y = yIn;
    map = mapIn;
}
//Getters
vector<vector<Square>> Map::getMap() const {
    return map;
}
int Map::getX() const {
    return x;
}
int Map::getY() const {
    return y;
}

void Map::clear() {
    map.clear();
}

int Map::getMapSize() {
    int mapSize = map.size();
    return mapSize;
}

//Setters
void Map::setMap(int num, SquareType st) {
    for (int i = 0; i < map.at(num).size(); i++) {
        map.at(num).at(i).setSquare(st);
    }
}

void Map::replaceMap(vector<vector<Square>> mapIn) {
    map = mapIn;
}

void Map::setX(int xIn){
    x = xIn;
}
void Map::setY(int yIn){
    y = yIn;
}

void Map::resetMap(vector<vector<Square>> newMap) {
    map = newMap;
}


//Draw method
void Map::draw(int playerPosX, int playerPosY) {
    if (squareSpaces.size() == 0) {

        map.clear();
        vector<Square> squareVec;
        for (int i = 0; i < 8; i++) {
            squareVec.push_back(Square(wall, i, 0));
            for (int j = 0; j < 8; j++) {
                if (i == 0 || i == 8) {
                    squareVec.push_back(Square(wall, i, j));
                } else if (i == playerPosX && j == playerPosY) {
                    squareVec.push_back(Square(playerSpace, i, j));
                } else if (i == 5 && j == 3) {
                    squareVec.push_back(Square(monsterSpace, i, j));
                } else if (i == 6 && j == 4) {
                    squareVec.push_back(Square(checkpoint, i, j));
                } else {
                    squareVec.push_back(Square(empty, i, j));
                }
            }
            squareVec[0] = Square(wall, i, 0);
            squareVec[squareVec.size() - 1] = Square(wall, i, squareVec.size() - 1);
            map.push_back(squareVec);
            squareVec.clear();
        }

        for (int i = 8; i >= 0; i--) {
            squareVec.push_back(Square(wall, 8, i));
        }

        map.push_back(squareVec);

    return;

    }
}

vector<string> Map::save() const {
    vector<string> squareTypes;

    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map.at(i).size(); j++){
            squareTypes.push_back(map[i][j].printSquareType());
        }
    }

    return squareTypes;
}


/** Square Class **/

//Default constructor
Square::Square(){
    square = empty;
    x = y = 0;
}
//Non-Default Constructor
Square::Square(SquareType squareIn, int xIn, int yIn) {
    square = squareIn;
    x = xIn;
    y = yIn;
}
//Getters
SquareType Square::getSquare() const {
    return square;
}
int Square::getX() const {
    return x;
}
int Square::getY() const {
    return y;
}
//Setters
void Square::setSquare(SquareType squareIn) {
    square = squareIn;
}
void Square::setX(int xIn) {
    x = xIn;
}
void Square::setY(int yIn) {
    y = yIn;
}


string Square::printSquareType() const {
    switch (square) {
        case empty: return "empty";
        case wall: return "wall";
        case checkpoint: return "checkpoint";
        case playerSpace: return "playerSpace";
        case monsterSpace: return "monsterSpace";
    }
}


