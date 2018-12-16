//
// Created by Sarah McLaughlin on 4/10/18.
//

#ifndef WARRIORSANDWIZARDS_MAP_H
#define WARRIORSANDWIZARDS_MAP_H

#include <iostream>
#include <vector>

class Square;
using namespace std;

enum SquareType{empty, wall, checkpoint, playerSpace, monsterSpace};

class Square;

class Map {
private:
    vector<vector<Square>> map;
    int x;
    int y;
    int mapSize;

public:
    vector<string> squareSpaces;

    /**Default constructor.
     * Requires: nothing
     * Modifies: map, x, y
     * Effects: sets map to be empty, sets x and y to be 0.
     */
    Map();
    /**Non-Default constructor.
     * Requires: nothing
     * Modifies: x,y
     * Effects: sets map to be mapIn, sets x to be xIn, sets y to be yIn
     */
    Map(vector<vector<Square>>, int xIn, int yIn);

    /**Getters
    * Requires: nothing
    * Modifies: nothing
    * Effects: returns the value stored in the field for a constructor
    */
    vector<vector<Square>> getMap() const;

    int getX() const;

    void resetMap(vector<vector<Square>> newMap);

    int getMapSize();

    void clear();

    int getY() const;

    /**Setters
     * Requires: nothing
     * Modifies: map, x, y
     * Effects: sets the field to the value that is input into the setter.
     */
    void setMap(int num, SquareType st);

    void replaceMap(vector<vector<Square>> mapIn);

    void setX(int xIn);

    void setY(int yIn);

    /**Draw Method
     * Requires: nothing
     * Modifies: nothing
     * Effects: fills squares in map with different square types.
     */
    void draw(int playerPosX, int playerPosY);

    /**
     * Printing for debugging purposes only
     */
    void print() const;

    /**
     * Save method
     * Requires: nothing
     * Modifies: nothing
     * Effects: Saves the current map to a file for next load.
    */
    vector<string> save() const;




};

class Square {
public:
    SquareType square;
    int x;
    int y;
public:
    /**Default constructor.
     * Requires: nothing
     * Modifies: square
     * Effects: sets square to be empty.
     */
    Square();

    /**Non-Default constructor.
     * Requires: nothing
     * Modifies: square
     * Effects: sets square to be squareIn.
     */
    Square(SquareType squareIn, int xIn, int yIn);

    /**Getters
    * Requires: nothing
    * Modifies: nothing
    * Effects: returns the value stored in the field for a constructor
    */
    SquareType getSquare() const;

    int getX() const;
    int getY() const;

    /**Setters
     * Requires: nothing
     * Modifies: square
     * Effects: sets the field to the value that is input into the setter.
     */
    void setSquare(SquareType squareIn);

    void setX(int xIn);
    void setY(int yIn);

    /**Draw method
     * Requires: nothing
     * Modifies: nothing
     * Effects: draws based on square type given.
     */
    void draw();

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Switches on the SquareType and returns the value in a stirng
    */
    string printSquareType() const;



};


#endif //WARRIORSANDWIZARDS_MAP_H
