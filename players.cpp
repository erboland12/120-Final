//
// Created by Sarah McLaughlin on 4/10/18.
//

#include "players.h"

Player::Player() : maxHealth(10), currHealth(10), name(""), xPos(4), yPos(4){
    setExperience(0);
}

Player::Player(string n) : maxHealth(10), currHealth(10), name(n), xPos(4), yPos(4) {
    setExperience(0);
}

int Player::getCurrHealth() const {
    return currHealth;
}

int Player::getMaxHealth() const {
    return maxHealth;
}

string Player::getName() const {
    return name;
}

int Player::getLevel() const {
    return level;
}

int Player::getExperience() const {
    return experience;
}

int Player::getXPos() const {
    return xPos;
}

int Player::getYPos() const {
    return yPos;
}

void Player::setName(string n){
    name = n;
}

void Player::setLevel(int level) {
    this->level = level;
}

void Player::setExperience(int e) {
    //TODO: generate a logistic equation to determine level based on experience
    if(e >= 0) {
        experience = e;
        level = experience/300 + 1;
        maxHealth = 10*(level+1);
        currHealth = maxHealth;
    }
    else experience = 0;
}

void Player::setXPos(const int &x){
    if(x < 0) xPos = -1;
    xPos = x;
}

void Player::setYPos(const int &y){
    if(y < 0) yPos = -1;
    yPos = y;
}

void Player::changeHealth(const int &h) {
    currHealth += h;
    if(currHealth < 0) currHealth = 0;
    else if(currHealth > maxHealth) currHealth = maxHealth;
}

void Player::addExp(const int &e){
    if(e > 0) experience += e;
    int currLevel = level;
    level = experience/(300*currLevel) + 1;
    if(currLevel != level){
        maxHealth = 10*(level+1);
        currHealth = maxHealth;
    }
}

void Player::resetHealth() {
    currHealth = maxHealth;
}

Warrior::Warrior() : Player() {}

Warrior::Warrior(string n) : Player(n) {}

int Warrior::attack() const {
    return rand() % 10 + level/2;
}

int Warrior::defend() const {
    return rand() % 8 + level/3;
}

string Warrior::print() const{
    return name + "\n" + "level " + to_string(level) + " warrior\n" + to_string(currHealth) + "/" + to_string(maxHealth) + " health";
}

Wizard::Wizard() : Player() {}

Wizard::Wizard(string n) : Player(n) {}

int Wizard::attack() const {
    return rand() % 8 + level/3;
}

int Wizard::defend() const {
    return rand() % 10 + level/2;
}

string Wizard::print() const{
    return to_string(level);
}

Monster::Monster() : health(20), name(""), isHidden(false), level(1) {}

Monster::Monster(string n, bool i, int l) : name(n), isHidden(i) {
    if(l <= 1) level = 1;
    level = l;
    health = 20*level;
}

int Monster::getHealth() const{
    return health;
}

string Monster::getName() const{
    return name;
}

bool Monster::getIsHidden() const{
    return isHidden;
}

int Monster::getLevel() const{
    return level;
}

void Monster::setName(const string &n){
    name = n;
}

void Monster::setIsHidden(const bool &h){
    isHidden = h;
}

void Monster::changeHealth(const int &h){
    health += h;
    if(health < 0) health = 0;
}

void Monster::changeHiddenStatus() {
    isHidden = !isHidden;
}

int Monster::attack() const{
    return rand() % health + level;
}

int Monster::defend() const{
    return rand() & (health/2) + 2*level;
}