#ifndef LOGIC_SEEN
#define LOGIC_SEEN

#include "gba.h"

//Will be controlled by player
typedef struct {
    int x;
    int y;
} Player;

//Enemy that will seek the player automatically, can tackle player
typedef struct {
    int x;
    int y;
    //Will decrease speed with levels because speed determines how many frames the Linebacker is moving.
    //For example, if speed is 3, Linebacker will move every 3 frames
    int speed;
} Linebacker;

//Enemy that will randomly move around the map, can tackle player
typedef struct {
    int x;
    int y;
    //Will decrease speed with levels because speed determines how many frames the Fly is moving.
    //For example, if speed is 3, Fly will move every 3 frames
    int speed;
    //Random location is stored in the destination
    int destinationX;
    int destinationY;
} Fly;

//Controls everything that the app logic needs
typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;
    //The state in which we are transitioning levels
    int won;
    
    Player player;
    
    int numLinebackers;
    Linebacker *linebackers;
    
    int numFlies;
    Fly *flies;
    
    //Represents how many enemies there will be and their speed
    int level;

} AppState;

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

//This function reinitializes the app state after the level increases
void reinitializeAppState(AppState* appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

#endif
