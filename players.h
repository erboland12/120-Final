
//
// Created by Sarah McLaughlin on 4/10/18.
//

#ifndef WARRIORSANDWIZARDS_PLAYERS_H
#define WARRIORSANDWIZARDS_PLAYERS_H

#include <ctime>
#include <string>
#include <ostream>
#include <iostream>

using namespace std;

class Player{
protected:
    int currHealth;
    int maxHealth;
    string name;
    int level;
    int experience;
    int xPos;
    int yPos;

public:
    /**
     * Default constructor
     * Requires: nothing
     * Modifies: fields
     * Effects: sets current and max health to 10, xPos and yPos to -1, and name to empty string.
     *          Calls setExperience with 0
     */
    Player();

    /**
     * Non-Default constructor
     * Requires: nothing
     * Modifies: fields
     * Effects: sets name to n, xPos and yPos to -1, and current and max health to h.
     *          Calls setExperience and with inputs
     */
    Player(string n);

    /**
     * Getters
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the field
     */
    int getCurrHealth() const;
    int getMaxHealth() const;
    string getName() const;
    int getLevel() const;
    int getExperience() const;
    int getXPos() const;
    int getYPos() const;

    /**
     * Setters
     * Requires: nothing
     * Modifies: field
     * Effects: sets field to the input
     */
    void setName(string n);
    void setExperience(int experience);
    void setXPos(const int &x);
    void setYPos(const int &y);
    void setLevel(int level);

    /**
     * Requires: nothing
     * Modifies: health
     * Effects: changes the health of the player by the input. if the players'
     *          health would drop below 0, it sets the health to 0 instead
     */
    void changeHealth(const int &h);

    /**
     * Requires: nothing
     * Modifies: experience
     * Effects: adds the input to experience. If the input is less than 0, it
     *          does not add anything to experience
     */
    void addExp(const int &e);

    /**
     * Requires: nothing
     * Modifies: currHealth
     * Effects: sets currHealth to maxHealth
     */
    void resetHealth();

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the strength of the player's attack
     */
    virtual int attack() const = 0;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the ability of the player's defense
     */
    virtual int defend() const = 0;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prints out the Player information
     */
    virtual string print() const = 0;
};

class Warrior : public Player{
public:
    /**
     * Default Constructor
     * Requires: nothing
     * Modifies: fields
     * Effects: calls the default player constructor
     */
    Warrior();

    /**
     * Non-default Constructor
     * Requires: nothing
     * Modifies: fields
     * Effects: calls the non-default player constructor
     */
    Warrior(string n);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the attack strength of a warrior
     */
    int attack() const override;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the defense ability of a warrior
     */
    int defend() const override;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prints out the Warrior information
     */
    string print() const override;
};

class Wizard : public Player{
public:
    /**
     * Default Constructor
     * Requires: nothing
     * Modifies: fields
     * Effects: calls the default player constructor
     */
    Wizard();

    /**
     * Non-default Constructor
     * Requires: nothing
     * Modifies: fields
     * Effects: calls the non-default player constructor
     */
    Wizard(string n);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the attack strength of a wizard
     */
    int attack() const override;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the defense ability of a wizard
     */
    int defend() const override;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prints out the Wizard information
     */
    string print() const override;
};

class Monster{
private:
    int health;
    string name;
    bool isHidden;
    int level;

public:
    /**
     * Default Constructor
     * Requires: nothing
     * Modifies: fields
     * Effects: sets health to 20, name to the empty string, isHidden to false, and level to 1
     */
    Monster();

    /**
     * Non-default Constructor
     * Requires: nothing
     * Modifies: fields
     * Effects: name, isHidden, and level to the inputs, sets health to 20*level
     */
    Monster(string n, bool i, int l);

    /**
     * Getters
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the fields
     */
    int getHealth() const;
    string getName() const;
    bool getIsHidden() const;
    int getLevel() const;

    /**
     * Setters
     * Requires: nothing
     * Modifies: fields
     * Effects: sets field to input
     */
    void setName(const string &n);
    void setIsHidden(const bool &h);

    /**
     * Requires: nothing
     * Modifies: health
     * Effects: changes the health of the monster by the input. if the monster'
     *          health would drop below 0, it sets the health to 0 instead
     */
    void changeHealth(const int &h);

    /**
     * Requires: nothing
     * Modifies: isHidden
     * Effects: swaps the status of isHidden
     */
    void changeHiddenStatus();

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns a random number, based on the level that the monster attacks for
     */
    int attack() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns the monster's defense ability
     */
    int defend() const;
};


#endif //WARRIORSANDWIZARDS_PLAYERS_H
