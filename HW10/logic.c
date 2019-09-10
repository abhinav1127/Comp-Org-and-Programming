#include "logic.h"
#include "gba.h"
#include <stdio.h>
#include <stdlib.h>

void initializeAppState(AppState* appState) {
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    appState -> gameOver = 0;
    appState -> won = 0;
    
    //Sets player's initial position and assigns to appState's player
    Player newPlayer;
    newPlayer.x = 130;
    newPlayer.y = 110;
    
    appState -> player = newPlayer;
    
    appState -> numLinebackers = 1;
    //allocate memory for up to 5 linebackers
    //Intentionally not handling malloc error, asked TA and he said to just leave it
    appState -> linebackers = (Linebacker*) malloc(sizeof(Linebacker) * 5);
    
    Linebacker newLinebacker;
    newLinebacker.x = 90;
    newLinebacker.y = 110;
    newLinebacker.speed = 3;
    
    appState -> linebackers[0] = newLinebacker;
    
    appState -> numFlies = 0;
    //allocate memory for up to 5 Flies
    //Intentionally not handling malloc error, asked TA and he said to just leave it
    appState -> flies = (Fly*) malloc(sizeof(Fly) * 5);
    
    //Game starts at level 1
    appState -> level = 1;
}

//Called when we are increasing the level
//Specifies exactly how many of each type of enemy will exist at each level and the enemies' speed
void reinitializeAppState(AppState* appState) {
    
    //These lines make sure that the whole state is restarted
    appState -> gameOver = 0;
    appState -> won = 0;
    
    //Initializes the player to the same thing every time
    appState -> player.x = 130;
    appState -> player.y = 110;
    
    //Initializes the first Linebacker
    appState -> linebackers[0].x = 90;
    appState -> linebackers[0].y = 60;
    
    //Initializes the second Linebacker
    appState -> linebackers[1].x = 90;
    appState -> linebackers[1].y = 140;
    
    appState -> level += 1;
    
    //These statements help increase the difficulty as the levels increase
    //By increasing speed and amount of enemies
    if (appState -> level >= 2) {
        appState -> numLinebackers = 2;
        appState -> linebackers[0].speed = 3;
        appState -> numFlies = 0;

    }
    if (appState -> level >= 3) {
        appState -> numFlies = 1;
        
        appState -> flies[0].x = 50;
        appState -> flies[0].y = 110;
        appState -> flies[0].speed = 3;
        appState -> flies[0].destinationX = randint(0, 140);
        appState -> flies[0].destinationY = randint(0, 220);

        
    }
    if (appState -> level >= 4) {
        appState -> flies[0].speed = 2;
    }
    
    if (appState -> level >= 5) {
        appState -> numFlies = 2;

        appState -> flies[1].x = 50;
        appState -> flies[1].y = 65;
        appState -> flies[1].speed = 3;
        appState -> flies[1].destinationX = randint(0, 140);
        appState -> flies[1].destinationY = randint(0, 220);
    }
    
    if (appState -> level >= 6) {
        appState -> linebackers[0].speed = 2;
    }
    
    if (appState -> level >= 7) {
        appState -> numLinebackers = 3;
        
        appState -> linebackers[2].x = 70;
        appState -> linebackers[2].y = 110;
    }
    
    if (appState -> level >= 8) {
        appState -> numFlies = 3;
        
        appState -> flies[2].x = 90;
        appState -> flies[2].y = 120;
        appState -> flies[2].speed = 3;
        appState -> flies[2].destinationX = randint(0, 140);
        appState -> flies[2].destinationY = randint(0, 220);
    }
    
    if (appState -> level >= 9) {
        appState -> numLinebackers = 4;
        
        appState -> linebackers[3].x = 70;
        appState -> linebackers[3].y = 40;
    }
    
    if (appState -> level >= 10) {
        appState -> flies[0].speed = 1;
    }
    
    if (appState -> level >= 11) {
        appState -> linebackers[0].speed = 1;
    }
    
    if (appState -> level >= 12) {
        appState -> numFlies = 4;
        
        appState -> flies[3].x = 30;
        appState -> flies[3].y = 130;
        appState -> flies[3].speed = 3;
        appState -> flies[3].destinationX = randint(0, 140);
        appState -> flies[3].destinationY = randint(0, 220);
    }
    
    if (appState -> level >= 13) {
        appState -> numLinebackers = 5;
        
        appState -> linebackers[3].x = 30;
        appState -> linebackers[3].y = 20;
    }
    
    if (appState -> level >= 14) {
        appState -> numFlies = 5;
        
        appState -> flies[3].x = 100;
        appState -> flies[3].y = 20;
        appState -> flies[3].speed = 3;
        appState -> flies[3].destinationX = randint(0, 140);
        appState -> flies[3].destinationY = randint(0, 220);
    }
    
    if (appState -> level == 15) {
        appState -> gameOver = 1;
    }
    
}


//Moves the player according to their button input and makes sure they do not go off screen
static void movePlayer(AppState *currentAppState, u32 keysPressedNow, AppState *nextAppState) {
    
    if (KEY_DOWN(BUTTON_RIGHT, keysPressedNow)) {
        if (currentAppState -> player.y < 220) {
            nextAppState -> player.y += 1;
        }
    }
    if (KEY_DOWN(BUTTON_LEFT, keysPressedNow)) {
        if (currentAppState -> player.y > 0) {
            nextAppState->player.y -= 1;
        }
    }
    if (KEY_DOWN(BUTTON_UP, keysPressedNow)) {
        nextAppState->player.x -= 1;
        
    }
    if (KEY_DOWN(BUTTON_DOWN, keysPressedNow)) {
        if (currentAppState -> player.x < 140) {
            nextAppState->player.x += 1;
        }
    }
}

//Moves linebacker given the position of the player
//Will always move toward the player, but can only move laterally
static void moveLinebacker(AppState *currentAppState, AppState *nextAppState) {
    
    //Moves each Linebacker
    for (int i = 0; i < currentAppState -> numLinebackers; i++) {
        //Gets distance between player and this Linebacker
        int xDist = currentAppState -> player.x - currentAppState -> linebackers[i].x;
        int yDist = currentAppState -> player.y - currentAppState -> linebackers[i].y;
        
        if (xDist < 0) {
            nextAppState -> linebackers[i].x -= 1;
        } else if (yDist < 0) {
            nextAppState -> linebackers[i].y -= 1;
        } else if (yDist > 0) {
            nextAppState -> linebackers[i].y += 1;
        } else {
            nextAppState -> linebackers[i].x += 1;
        }
    }

}

//Moves the fly towards its destination
//Its destination is chosen randomly in the screen
static void moveFlies(AppState *currentAppState, AppState *nextAppState) {
    
    //Moves each Fly
    for (int i = 0; i < currentAppState -> numFlies; i++) {

        //If the Fly is at its destination, choose a new destination
        if (currentAppState -> flies[i].x == currentAppState -> flies[i].destinationX  &&
            currentAppState -> flies[i].y == currentAppState -> flies[i].destinationY) {
            nextAppState -> flies[i].destinationX = randint(27, 140);
            nextAppState -> flies[i].destinationY = randint(0, 220);
        }
        
        //Move towards its destination
        if (currentAppState -> flies[i].destinationX > currentAppState -> flies[i].x) {
            nextAppState -> flies[i].x += 1;
        }
        if (currentAppState -> flies[i].destinationX < currentAppState -> flies[i].x) {
            nextAppState -> flies[i].x -= 1;
        }
        if (currentAppState -> flies[i].destinationY < currentAppState -> flies[i].y) {
            nextAppState -> flies[i].y -= 1;
        }
        if (currentAppState -> flies[i].destinationY > currentAppState -> flies[i].y) {
            nextAppState -> flies[i].y += 1;
        }
    }
    
}

//Checks if the player has crossed into the endzone, will go to level if true
static void checkWin(AppState *currentAppState, AppState *nextAppState) {
    if (currentAppState -> player.x < 27 || nextAppState -> player.x < 10) {
        nextAppState -> won = 1;
    }

}

//Checks for collisions with enemies, will end game if true
static void checkTackle(AppState *currentAppState, AppState *nextAppState) {
    int x = currentAppState -> player.x;
    int y = currentAppState -> player.y;
    
    //Checks if any Linebackers have collided with the player
    for (int i = 0; i < currentAppState -> numLinebackers; i++) {
        int xL = currentAppState -> linebackers[i].x;
        int yL = currentAppState -> linebackers[i].y;
        
        //Since both the player and enemy are 20x20, we can simply check if the absolute
        //value of the difference of their positions in both the x and y directions is less than 20
        //to check if there was a collision.
        if ((abs(x - xL) < 20 && abs(y - yL) < 20) || nextAppState -> player.x < 10) {
            nextAppState -> gameOver = 1;
            break;
        }
    }
    
    //Checks if any Flies have collided with the player
    //Will not execute if a Linebacker has collided with a player
    if (nextAppState -> gameOver == 0) {
        for (int i = 0; i < currentAppState -> numFlies; i++) {
            int xL = currentAppState -> flies[i].x;
            int yL = currentAppState -> flies[i].y;
            
            if ((abs(x - xL) < 20 && abs(y - yL) < 20) || nextAppState -> player.x < 10) {
                nextAppState -> gameOver = 1;
                break;
            }
        }
    }
    

}


// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {

    AppState nextAppState = *currentAppState;
    
    movePlayer(currentAppState, keysPressedNow, &nextAppState);
    
    //Moves the Linebackers according to their speeds (will move every 1/speed frames)
    if (vBlankCounter % currentAppState -> linebackers[0].speed == 0) {
        moveLinebacker(currentAppState, &nextAppState);
    }
    
    //Moves the Flies according to their speeds (will move every 1/speed frames)
    if (vBlankCounter % currentAppState -> flies[0].speed == 0) {
        moveFlies(currentAppState, &nextAppState);
    }
    
    checkTackle(currentAppState, &nextAppState);
    checkWin(currentAppState, &nextAppState);
    
    keysPressedBefore += 1;
    

    return nextAppState;
}
