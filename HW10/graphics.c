#include "graphics.h"
#include "gba.h"
// Example for the provided garbage image:
#include "images/field.h"
#include "images/halfback.h"
#include "images/linebacker.h"
#include "images/fly.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Draws player
static void drawPlayer(Player toDraw) {
    drawImageDMA(toDraw.x, toDraw.y, HALFBACK_WIDTH, HALFBACK_HEIGHT, halfback);
}

//Draws all Linebackers
static void drawLinebackers(Linebacker *linebackers, int numLinebackers) {
    for (int i = 0; i < numLinebackers; i++) {
        Linebacker toDraw = linebackers[i];
        drawImageDMA(toDraw.x, toDraw.y, LINEBACKER_WIDTH, LINEBACKER_HEIGHT, linebacker);
    }
}

//Draws all Flies
static void drawFlies(Fly *flies, int numFlies) {
    for (int i = 0; i < numFlies; i++) {
        Fly toDraw = flies[i];
        drawImageDMA(toDraw.x, toDraw.y, FLY_WIDTH, FLY_WIDTH, fly);
    }
}

// This function will be used to draw everything about the app
// including the background and whatnot.
void fullDrawAppState(AppState *state) {

    drawFullScreenImageDMA(field);
    
    //Buffer is used to get the level into a String format
    char buffer[20];
    sprintf(buffer, "Level: %d", state -> level);
    drawString(180, 5, buffer, 0x0000);
    
    //Draws all moving characters
    drawPlayer(state -> player);
    drawLinebackers(state -> linebackers, state -> numLinebackers);
    drawFlies(state -> flies, state -> numFlies);
    
    
}

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state) {
    //Redraw the part of the background the player was in in the last state
    drawPartialBackground(state -> player.x, state -> player.y, HALFBACK_WIDTH, HALFBACK_HEIGHT, field);
    
    //Uncomment these lines to prevent the intentional tearing of the enemies
//    for (int i = 0; i < state -> numLinebackers; i++) {
//        drawPartialBackground(state -> linebackers[i].x, state -> linebackers[i].y, LINEBACKER_WIDTH, LINEBACKER_HEIGHT, field);
//    }
    
//    for (int i = 0; i < state -> numFlies; i++) {
//        Fly toUndraw = state -> flies[i];
//        drawPartialBackground(toUndraw.x, toUndraw.y, FLY_WIDTH, FLY_HEIGHT, field);
//    }

}

// Draws linebackers and the player and the flies
void drawAppState(AppState *state) {
    drawPlayer(state -> player);
    drawLinebackers(state -> linebackers, state -> numLinebackers);
    drawFlies(state -> flies, state -> numFlies);
}
