#include "graphics.h"
#include "shapes.h"
#include "map.h"
#include "game.h"

enum mode {start, game, load, howTo, fight, playerInfo, gameOver, save};

void displayFight();

mode screen;
GLdouble width, height;
int wd;
string file;
vector<Circle> attack;
vector<Circle> circles1;
vector<Circle> circles2;
vector<Circle> circles3;
Tangle newGame;
Tangle loadGame;
Tangle instructions;
Tangle back;
Tangle background;
Tangle target;
Tangle player;
Tangle warrior;
Tangle wizard;
Tangle pHealthMax;
Tangle pHealthCurr;
Tangle mHealthMax;
Tangle mHealthCurr;
string fileName;
string fileName2;
Game gameInstance("Player", 1);
bool loaded = false;
bool playerTurn = true;
int attackTurn;
string playerName = "";
int timeLeft;
int timeNewMonster;

Monster tempMon;

Map m = gameInstance.getMap();

int mouseX;
int mouseY;

void init() {
    timeNewMonster = rand() % 20 + 5;
    width = 1200;
    height = 700;

    mouseX = mouseY = 0;

    screen = start;

    //start screen shapes
    newGame.setDimensions(100, 500);
    newGame.setCenter(width/2.0, height/2.0);
    newGame.setFillColor(1.0,1.0,1.0);
    newGame.setBorderColor(0.0,0.0,0.0);
    loadGame.setDimensions(100, 500);
    loadGame.setCenter(width/2.0, height/2.0+110);
    loadGame.setFillColor(1.0,1.0,1.0);
    loadGame.setBorderColor(0.0,0.0,0.0);
    instructions.setDimensions(100, 500);
    instructions.setCenter(width/2.0, height/2.0+220);
    instructions.setFillColor(1.0,1.0,1.0);
    instructions.setBorderColor(0.0,0.0,0.0);

    // player info screen shapes
    warrior.setDimensions(100, 500);
    warrior.setCenter(width/2.0, height/2.0);
    warrior.setFillColor(1.0,1.0,1.0);
    warrior.setBorderColor(0.0,0.0,0.0);
    wizard.setDimensions(100, 500);
    wizard.setCenter(width/2.0, height/2.0+110);
    wizard.setFillColor(1.0,1.0,1.0);
    wizard.setBorderColor(0.0,0.0,0.0);

    //instruction screen shapes
    back.setDimensions(50, 200);
    back.setCenter(width/2.0, height-100);
    back.setFillColor(1.0,1.0,1.0);
    back.setBorderColor(0.0,0.0,0.0);

    //fight screen shapes
    background.setDimensions(height, width);
    background.setCenter(width/2.0, height/2.0);
    target.setDimensions(100, 50);
    target.setCenter(width/2.0, height/2.0);
    target.setFillColor({0.0,0.0,0.0});
    target.setBorderColor({0.0,0.8,0.0});
    player.setDimensions(120, 30);
    player.setCenter(15, height/2.0);
    player.setFillColor({0.8,0.8,0.0});
    player.setBorderColor({0.0,0.0,0.0});
    pHealthMax.setDimensions(20, 200);
    pHealthMax.setCenter(120, height-20);
    pHealthMax.setBorderColor({0.1,1.0,0.1});
    pHealthCurr.setDimensions(20, 200);
    pHealthCurr.setCenter(120, height-20);
    pHealthCurr.setFillColor({0.1,1.0,0.1});
    mHealthMax.setDimensions(20, 200);
    mHealthMax.setCenter(width-120, height-20);
    mHealthMax.setBorderColor({1.0,0.1,0.1});
    mHealthCurr.setDimensions(20, 200);
    mHealthCurr.setCenter(width-120, height-20);
    mHealthCurr.setFillColor({1.0,0.1,0.1});

    //initialize attack 1 circles
    for (int i = 0; i < 100; ++i) {
        circles1.push_back(Circle(rand() % 10 + 5, //random radius
                                 {1.0,1.0,1.0}, //white border
                                 {1.0,1.0,1.0}, //white border
                                 {0, 0},
                                 {width/2.0, height/2.0}) //middle of the screen
        );
    }

    //initialize attack 2 circles
    for (int i = 0; i < 40; ++i) {
        int side = rand() % 4;
        if(side == 0) {//LEFT
            circles2.push_back(Circle(rand() % 10 + 5, //random radius
                                     {1.0, 1.0, 1.0}, //white border
                                     {1.0, 1.0, 1.0}, //white border
                                     {0, 0}, //direction
                                     {0, rand() % (int) height})
            );
        } else if(side == 1){//RIGHT
            circles2.push_back(Circle(rand() % 10 + 5, //random radius
                                     {1.0, 1.0, 1.0}, //white border
                                     {1.0, 1.0, 1.0}, //white border
                                     {0, 0}, //direction
                                     {width, (rand() % (int) height)/1.0})
            );

        } else if(side == 2){//TOP
            circles2.push_back(Circle(rand() % 10 + 5, //random radius
                                     {1.0, 1.0, 1.0}, //white border
                                     {1.0, 1.0, 1.0}, //white border
                                     {0, 0}, //direction
                                     {rand() % (int) width, 0})
            );
        } else {//BOTTOM
            circles2.push_back(Circle(rand() % 10 + 5, //random radius
                                     {1.0, 1.0, 1.0}, //white border
                                     {1.0, 1.0, 1.0}, //white border
                                     {0, 0}, //direction
                                     {(rand() % (int) height)/1.0, height})
            );
        }
    }
    //initialize attack 3 circles
    for (int i = 0; i < 75; ++i) {
        circles3.push_back(Circle(rand() % 10 + 5, //random radius
                                 {1.0,1.0,1.0}, //white border
                                 {1.0,1.0,1.0}, //white border
                                 {0, 0},
                                 {rand() % (int)height, rand() % (int)height}) //left of the screen
        );
    }

}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black and opaque


}

void displayPlayerInfo() {
    string message = "What is your name, mighty player?";

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/2.75, 50);
    for (char c : message) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/2., 90);
    for (char c : playerName) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    warrior.draw();
    string warrior = "Warrior";

    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(width/2.0-50, height/2.0+10);
    for (char c : warrior) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    wizard.draw();
    string wizardString = "Wizard";

    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(width/2.0-50, height/2.0+120);
    for (char c : wizardString) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

void displayLoad() {
    string message = "Please enter the name of your file and press enter to load it";

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/4.0, 50);
    for (char c : message) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/2.5, 100);
    for (char c : fileName) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    if (loaded) {
        screen = game;
    }
}

void displayStart(){
    string warrior = "Warriors &";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/2.0-80, 140);
    for (char c : warrior) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
    string wizard = "Wizards";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/2.0, 165);
    for (char c : wizard) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
    newGame.draw();
    loadGame.draw();
    instructions.draw();
    string newGame = "New Game";
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(width/2.0-35, height/2.0+10);
    for (char c : newGame) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    string loadGame = "Load Game";
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(width/2.0-40, height/2.0+120);
    for (char c : loadGame) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    string instructions = "How to Play";
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(width/2.0-50, height/2.0+230);
    for (char c : instructions) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
}

void displayHowTo() {
    string title = "Instructions";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/2.0-60, 150);
    for (char c : title) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    string generalTitle = "General";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(90, 250);
    for (char c : generalTitle) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    string general1 = "Use the arrow keys to move around the map";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(90, 280);
    for (char c : general1) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string general2 = "Be wary of monsters!";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(90, 310);
    for (char c : general2) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string general3 = "If you get too close, you'll start a fight";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(90, 340);
    for (char c : general3) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string general4 = "The more monsters you defeat, the stronger you get";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(90, 370);
    for (char c : general4) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string general5 = "Don't forget to save every once in a while";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(90, 400);
    for (char c : general5) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string fightTitle = "Fighting";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width-540, 250);
    for (char c : fightTitle) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    string fight1 = "When attacking, press enter to stop the yellow box";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width-540, 280);
    for (char c : fight1) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string fight2 = "Try to get it inside the green target box";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width-540, 310);
    for (char c : fight2) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string fight3 = "When being attacked, use your mouse";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width-540, 340);
    for (char c : fight3) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string fight4 = "Avoid the white circles";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width-540, 370);
    for (char c : fight4) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string fight5 = "Don't leave the screen";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width-540, 400);
    for (char c : fight5) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string fight6 = "If you're hit before time is up, you will lose health";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width-540, 430);
    for (char c : fight6) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    string fight7 = "Try to kill the monster before it kills you";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width-540, 460);
    for (char c : fight7) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);

    back.draw();
    string ready = "I'm ready to play!";
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(width/2.0-80, height-96);
    for (char c : ready) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
}

void drawShape(SquareType squareType, int x, int y) {
    Tangle p;
    Tangle m;
    if(squareType == empty){

    }
    else if(squareType == checkpoint){
        Circle checkpoint;
        //checkpoint.setCenter(s.getX(),s.getY());
        checkpoint.setRadius(30);
        checkpoint.setBorderColor(0/255.0,0/255,0/255.0);
        checkpoint.setFillColor(49/255.0,57/255,205/255.0);
        checkpoint.setCenter({x,y});
        checkpoint.draw();

    }
    else if(squareType == wall){
        Tangle wall;

        wall.setDimensions(30,30);
        wall.setBorderColor(1.0, 1.0, 1.0);
        wall.setFillColor(1.0, 1.0, 1.0);
        wall.setCenter(x,y);
        wall.draw();
    }
    else if(squareType == playerSpace){
        Tangle player;
        player.setDimensions(30,30);
        player.setBorderColor(1.0, 1.0, 1.0);
        player.setFillColor(20/255.0, 130/255.0, 55/255.0);
        player.setCenter(x,y);
        player.draw();
    }
    else if(squareType == monsterSpace){
        Tangle monster = p;
        monster.setDimensions(30,30);
        monster.setBorderColor(1.0, 1.0, 1.0);
        monster.setFillColor(255/255.0, 0/255.0, 0/255.0);
        monster.setCenter(x,y);
        monster.draw();
    }
}


void displayGame(){
    Map gameMap = gameInstance.getMap();
    for(int i = 0; i < gameMap.getMap().size(); i++){
        for(int j = 0; j < gameMap.getMap().at(i).size(); j++){
            SquareType squareType = gameMap.getMap().at(i).at(j).getSquare();
            drawShape(squareType, i * 80, j * 80);
            //Checks to see if monster is next to player.  If so, starts fight sequence.
            if (gameMap.getMap().at(i).at(j).getSquare() == playerSpace &&
                    gameMap.getMap().at(i+1).at(j).getSquare() == monsterSpace){
                screen = fight;
            }
            if (gameMap.getMap().at(i).at(j).getSquare() == playerSpace &&
                gameMap.getMap().at(i-1).at(j).getSquare() == monsterSpace){
                screen = fight;
            }
            if (gameMap.getMap().at(i).at(j).getSquare() == playerSpace &&
                gameMap.getMap().at(i).at(j+1).getSquare() == monsterSpace){
                screen = fight;
            }
            if (gameMap.getMap().at(i).at(j).getSquare() == playerSpace &&
                gameMap.getMap().at(i).at(j-1).getSquare() == monsterSpace){
                screen = fight;
            }

            //Checks to see if player is next to checkpoint.  If so, lets user save file.
            if (gameMap.getMap().at(i).at(j).getSquare() == playerSpace &&
                gameMap.getMap().at(i+1).at(j).getSquare() == checkpoint){
                screen = save;
            }
            if (gameMap.getMap().at(i).at(j).getSquare() == playerSpace &&
                gameMap.getMap().at(i-1).at(j).getSquare() == checkpoint){
                screen = save;
            }
            if (gameMap.getMap().at(i).at(j).getSquare() == playerSpace &&
                gameMap.getMap().at(i).at(j+1).getSquare() == checkpoint){
                screen = save;
            }
            if (gameMap.getMap().at(i).at(j).getSquare() == playerSpace &&
                gameMap.getMap().at(i).at(j-1).getSquare() == checkpoint){
                screen = save;
            }
        }
    }

}

void displayFight(){
    player.setFillColor({0.8,0.8,0.0});
    player.setBorderColor({0.0,0.0,0.0});
    pHealthMax.draw();
    pHealthCurr.draw();
    mHealthMax.draw();
    mHealthCurr.draw();
    string pH = "Your Health:";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(20, height-40);
    for (char c : pH) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    string mH = "Monster's Health:";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width-220, height-40);
    for (char c : mH) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    if(playerTurn){
        target.draw();
        player.draw();
        timeLeft = 20;
        attackTurn = rand() % 3;
        if(attackTurn == 0) attack = circles1;
        else if(attackTurn == 1) attack = circles2;
        else attack = circles3;
    } else {
        player.setCenter(player.getWidth(), height/2.0);
        player.setDirection(30, 0);
        string timer = "Time Left: " + to_string(timeLeft);
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2i(width-150, 24);
        for (char c : timer) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
        }

        for (int i = 0; i < attack.size(); i++) attack[i].draw();
        //check for overlapping
        for (int i = 0; i < attack.size(); i++) {
            if (attack[i].isOverlapping({mouseX, mouseY})) {
                attack[i].setFillColor(0.0, 0.0, 1.0);
                attack[i].setBorderColor(0.0, 0.0, 1.0);
                gameInstance.getPlayer().changeHealth(-1);
                pHealthCurr.setDimensions(20,200*(gameInstance.getPlayer().getCurrHealth()/(1.0*gameInstance.getPlayer().getMaxHealth())));
                pHealthCurr.setCenter(pHealthCurr.getWidth()/2+20, height-20);
                if(gameInstance.getPlayer().getCurrHealth() == 0) screen = gameOver;
                playerTurn = !playerTurn;
            } else {
                attack[i].setFillColor(circles1[i].getFillColor());
                attack[i].setBorderColor(circles1[i].getBorderColor());
            }
        }
    }
}

void displayGameOver() {
    string over = "Game Over.";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/2.0-25, height/2.0);
    for (char c : over) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
}

void displayCheckpoint() {
    string message = "What would you like to name your file?";

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/4.0, 50);
    for (char c : message) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/2.5, 100);
    for (char c : fileName2) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*
     * Draw here
     */
    switch(screen){
        case start: displayStart();
            break;
        case game: displayGame();
            break;
        case load: displayLoad();
            break;
        case howTo: displayHowTo();
            break;
        case fight: displayFight();
            break;
        case playerInfo: displayPlayerInfo();
            break;
        case gameOver: displayGameOver();
            break;
        case save: displayCheckpoint();
            break;
    }


    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    if(screen == save){
        if (key == 13){
            gameInstance.save(fileName2);
            fileName2 = "";

            vector<vector<Square>> squareVec;
            squareVec = gameInstance.getMap().getMap();

            for (int i = 0; i < squareVec.size(); i++) {
                for (int j = 0; j < squareVec[i].size(); j++) {
                    if (squareVec[i][j].getSquare() == checkpoint) {
                        squareVec[i][j].setSquare(empty);
                    }
                }
            }


            gameInstance.myMap.replaceMap(squareVec);
            screen = game;
        } else if (key == 127) {
            fileName2.pop_back();
        } else{
            fileName2 += key;
        }
    }
    if (screen == load) {
        if (key == 13) {
            loaded = gameInstance.load(fileName);
            fileName = "";
        } else if (key == 127) {
            fileName.pop_back();
        } else {
            fileName += key;
        }
    } else if (screen == fight && playerTurn) {
        if(key == 13){
            //return or enter
            //stop moving the player, check if overlapping
            player.setDirection({0,0});
            if(player.isOverlappingTangle(target)) {
                player.setFillColor({0.0,1.0,0.0});
                tempMon.changeHealth(-1*(gameInstance.getPlayer().getLevel()));
                mHealthCurr.setDimensions(20,200*(tempMon.getHealth()/(tempMon.getLevel()*20.0)));
                mHealthCurr.setCenter(width-(mHealthCurr.getWidth()/2+20), height-20);
                if(tempMon.getHealth() == 0){
                    vector<vector<Square>> squareVec;
                    squareVec = gameInstance.getMap().getMap();

                    for (int i = 0; i < squareVec.size(); i++) {
                        for (int j = 0; j < squareVec[i].size(); j++) {
                            if (squareVec[i][j].getSquare() == monsterSpace) {
                                squareVec[i][j].setSquare(empty);
                            }
                        }
                    }


                    gameInstance.myMap.replaceMap(squareVec);
                    gameInstance.getPlayer().addExp(300);
                    tempMon.changeHealth(20);
                    mHealthCurr.setDimensions(20,200*(tempMon.getHealth()/(tempMon.getLevel()*20.0)));
                    mHealthCurr.setCenter(width-(mHealthCurr.getWidth()/2+20), height-20);
                    screen = game;
                }
            }
            else player.setFillColor({1.0,0.0,0.0});
            playerTurn = !playerTurn;
        }
    } else if (screen == playerInfo) {
        playerName += key;
    }


    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    glutPostRedisplay();

    return;
}

void kbdS(int key, int x, int y) {
    if (screen == game) {
        switch(key) {
            case GLUT_KEY_DOWN:
                gameInstance.move(move_down);
                break;
            case GLUT_KEY_LEFT:
                gameInstance.move(move_left);
                break;
            case GLUT_KEY_RIGHT:
                gameInstance.move(move_right);
                break;
            case GLUT_KEY_UP:
                gameInstance.move(move_up);
                break;
        }
    }

    gameInstance.redrawMap();
    glutPostRedisplay();

    return;
}

void cursor(int x, int y) {
    //update mouse coordinates
    mouseX = x;
    mouseY = y;

    if(screen == start){
        if(newGame.isOverlapping({x,y})) newGame.setFillColor({0.5,0.5,0.5});
        else newGame.setFillColor({1.0,1.0,1.0});
        if(loadGame.isOverlapping({x,y})) loadGame.setFillColor({0.5,0.5,0.5});
        else loadGame.setFillColor({1.0,1.0,1.0});
        if(instructions.isOverlapping({x,y})) instructions.setFillColor({0.5,0.5,0.5});
        else instructions.setFillColor({1.0,1.0,1.0});
    }

    if (screen == playerInfo) {
        if(warrior.isOverlapping({x,y})) warrior.setFillColor({0.5,0.5,0.5});
        else warrior.setFillColor({1.0,1.0,1.0});
        if(wizard.isOverlapping({x,y})) wizard.setFillColor({0.5,0.5,0.5});
        else wizard.setFillColor({1.0,1.0,1.0});
    }

    if(screen == fight && !playerTurn){
        if(!background.isOverlapping({x,y})){
            gameInstance.getPlayer().changeHealth(-1);
            pHealthCurr.setDimensions(20,200*(gameInstance.getPlayer().getCurrHealth()/(1.0*gameInstance.getPlayer().getMaxHealth())));
            pHealthCurr.setCenter(pHealthCurr.getWidth()/2+20, height-20);
            if(gameInstance.getPlayer().getCurrHealth() == 0) screen = gameOver;
            playerTurn = !playerTurn;
        }
    }

    if(screen == howTo){
        if(back.isOverlapping({x,y})) back.setFillColor({0.5,0.5,0.5});
        else back.setFillColor({1.0,1.0,1.0});
    }

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (screen == start)) {
        if(newGame.isOverlapping({x,y})){
            screen = playerInfo;
        } else if (loadGame.isOverlapping({x, y})) {
            screen = load;
        } else if (instructions.isOverlapping({x, y})) {
            screen = howTo;
        }
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == playerInfo) {
        if (warrior.isOverlapping({x, y})) {
            gameInstance.setPlayer(playerName, 1);
            screen = game;
        } else if (wizard.isOverlapping({x, y})) {
            gameInstance.setPlayer(playerName, 0);
            screen = game;
        }
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == howTo) {
        if (back.isOverlapping({x, y})) {
            screen = start;
        }
    }


    glutPostRedisplay();
}

void timer(int extra) {
    if(screen == fight && playerTurn){
        //move player
        if(player.getCenter().x <= player.getLength()/2){
            player.setDirection({30,0});
        } else if (player.getCenter().x >= width - player.getLength()/2){
            player.setDirection({-30,0});
        }
        player.move(player.getDirection().xChange, player.getDirection().yChange);
    } else if(screen == fight){
        // move circles in pattern 1
        if(attackTurn == 0) {
            for (int i = 0; i < attack.size(); i++) {
                if (attack[i].getCenter().y < 0 || attack[i].getCenter().y > height ||
                    attack[i].getCenter().x < 0 || attack[i].getCenter().x > width) {
                    attack[i].setCenter(width / 2.0, height / 2.0);
                    attack[i].setDirection({rand() % 21 - 10, rand() % 21 - 10});
                    while (attack[i].getDirection().xChange == 0 &&
                            attack[i].getDirection().yChange == 0) {
                        attack[i].setDirection({rand() % 21 - 10, rand() % 21 - 10});
                    }
                }
                attack[i].move(attack[i].getDirection().xChange, attack[i].getDirection().yChange);
            }
        } else if (attackTurn == 1){
            // move circles in pattern 2
            for (int i = 0; i < attack.size(); i++) {
                //generate random speed
                int speed = rand() % 12 + 36;
                if ((attack[i].getDirection().xChange > 0 && attack[i].getCenter().x > width/2.0) ||
                    (attack[i].getDirection().xChange < 0 && attack[i].getCenter().x < width/2.0) ||
                    (attack[i].getDirection().yChange > 0 && attack[i].getCenter().y > height/2.0) ||
                    (attack[i].getDirection().yChange < 0 && attack[i].getCenter().y < height/2.0)) {
                    int side = rand() % 4;
                    if(side == 0) { //LEFT SIDE
                        attack[i].setCenter(0, rand() % (int) height);
                        if (attack[i].getCenter().y >= height/2.0) {
                            attack[i].setDirection(
                                    (int) distance({attack[i].getCenter().x, 0}, {width/2.0, 0.0})/speed,
                                    -(int) distance({0, attack[i].getCenter().y}, {0.0, height/2.0})/speed);
                        } else {
                            attack[i].setDirection(
                                    (int) distance({attack[i].getCenter().x, 0}, {width/2.0, 0.0})/speed,
                                    (int) distance({0, attack[i].getCenter().y}, {0.0, height/2.0})/speed);
                        }
                    } else if (side == 1){ //RIGHT SIDE
                        attack[i].setCenter(width, rand() % (int) height);
                        if (attack[i].getCenter().y >= height/2.0) {
                            attack[i].setDirection(
                                    -(int) distance({attack[i].getCenter().x, 0}, {width/2.0, 0.0})/speed,
                                    -(int) distance({0, attack[i].getCenter().y}, {0.0, height/2.0})/speed);
                        } else {
                            attack[i].setDirection(
                                    -(int) distance({attack[i].getCenter().x, 0}, {width/2.0, 0.0})/speed,
                                    (int) distance({0, attack[i].getCenter().y}, {0.0, height/2.0})/speed);
                        }
                    } else if (side == 2){ //TOP
                        attack[i].setCenter(rand() % (int)width, 0);
                        if (attack[i].getCenter().x <= width/2.0) {
                            attack[i].setDirection(
                                    (int) distance({attack[i].getCenter().x, 0}, {width/2.0, 0.0})/speed,
                                    (int) distance({0, attack[i].getCenter().y}, {0.0, height/2.0})/speed);
                        } else {
                            attack[i].setDirection(
                                    -(int) distance({attack[i].getCenter().x, 0}, {width/2.0, 0.0})/speed,
                                    (int) distance({0, attack[i].getCenter().y}, {0.0, height/2.0})/speed);
                        }
                    } else { //BOTTOM
                        attack[i].setCenter(rand() % (int)width, height);
                        if (attack[i].getCenter().x <= width/2.0) {
                            attack[i].setDirection(
                                    (int) distance({attack[i].getCenter().x, 0}, {width/2.0, 0.0})/speed,
                                    -(int) distance({0, attack[i].getCenter().y}, {0.0, height/2.0})/speed);
                        } else {
                            attack[i].setDirection(
                                    -(int) distance({attack[i].getCenter().x, 0}, {width/2.0, 0.0})/speed,
                                    -(int) distance({0, attack[i].getCenter().y}, {0.0, height/2.0})/speed);
                        }
                    }
                }
                attack[i].move(attack[i].getDirection().xChange, attack[i].getDirection().yChange);
            }
        } else {
            //move in pattern 3
            for (int i = 0; i < attack.size(); i++) {
                if (attack[i].getCenter().y < 0 || attack[i].getCenter().y > height ||
                    attack[i].getCenter().x < 0 || attack[i].getCenter().x > width ) {
                    int random = rand() % 2;
                    if(random == 0){ //LEFT
                        attack[i].setCenter(attack[i].getRadius(), rand() % (int)height);
                        attack[i].setDirection({rand() % 9 + 5, 0});
                    } else { //RIGHT
                        attack[i].setCenter(width-attack[i].getRadius(), rand() % (int)height);
                        attack[i].setDirection({-1*(rand() % 9 + 5), 0});
                    }
                    while(attack[i].getDirection().xChange == 0 &&
                          attack[i].getDirection().yChange == 0){
                        if(random == 0)attack[i].setDirection({rand() % 9 + 5, 0});
                        else attack[i].setDirection({-1*(rand() % 9 + 5), 0});
                    }
                }
                attack[i].move(attack[i].getDirection().xChange, attack[i].getDirection().yChange);
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

void timeKeeper(int extra){
    if(screen == fight && !playerTurn){
        timeLeft--;
        if(timeLeft == -1){
            playerTurn = !playerTurn;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000, timeKeeper, 0);
}

void newMonsterTimer(int extra){
    if(screen == game){
        timeNewMonster--;
        if(timeNewMonster == -1){
            //add new monster to game screen here
            timeNewMonster = rand() % 20 + 5;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000, newMonsterTimer, 0);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(50, 0); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Warriors and Wizards" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timers
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(1000, timeKeeper, 0);
    glutTimerFunc(1000, newMonsterTimer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
