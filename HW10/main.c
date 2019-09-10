#include "gba.h"
#include "logic.h"
#include "graphics.h"

#include "images/halfback.h"
#include "images/garbage.h"
#include "images/field.h"
#include "images/end.h"


#include <stdio.h>
#include <stdlib.h>

// AppState enum definition
typedef enum {
    START,
    START_NODRAW,
    APP_INIT,
    APP_INCREMENT_LEVEL,
    APP_WAIT,
    APP,
    APP_EXIT,
    APP_EXIT_NODRAW,
} GBAState;

int main(void) {
    // Manipulate REG_DISPCNT to set Mode 3.
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    GBAState state = START;

    // We store the "previous" and "current" states.
    AppState currentAppState, nextAppState;

    // We store the current and previous values of the button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    while(1) {
        // Load the current state of the buttons
        currentButtons = BUTTONS;

        switch(state) {
        case START:
            // Wait for VBlank
            waitForVBlank();

            //Draws the start state
            drawFullScreenImageDMA(field);
            //Draws all the title and the instructions
            char *title = "TOUCHDOWN";
            u16 color = 0x3800;
            drawCenteredString(68, 0, 100, 30, title, color);
            drawString(1, 122, "Avoid the Enemies and score a touchdown!", 0x0000);
            drawString(1, 136, "Don't let the enemies destroy the field!", 0x0000);
            drawString(45, 150, "Press A or SELECT to begin.", 0x0000);

            state = START_NODRAW;
            break;
        case START_NODRAW:
            // Start the app by switching the state to APP_INIT when A or Start is hit
                
            if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                state = APP_INIT;
            }
                
            if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
                state = APP_INIT;
            }

            break;
        case APP_INIT:
            // Initialize the app. Switch to the APP state.
            initializeAppState(&currentAppState);

            // Draw the initial state of the app
            fullDrawAppState(&currentAppState);
            
            state = APP;
            break;
        case APP_INCREMENT_LEVEL:
            // Reinitialize with a new level
            reinitializeAppState(&currentAppState);
            
            // Draw the initial state of the app
            fullDrawAppState(&currentAppState);
            
            state = APP_WAIT;
            
            break;
        //This state pauses the game between levels
        case APP_WAIT:
                
            
            drawString(45, 150, "Press A or SELECT to begin.", 0x0000);
                
            //Return to Start screen if SELECT is hit
            if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
                state = START;
                break;
            }
        
            //Starts the game when Start or A is clicked
            if (KEY_DOWN(BUTTON_START, currentButtons) || KEY_DOWN(BUTTON_A, currentButtons)) {
                state = APP;
            }
            
            break;
        case APP:
            //Returns to the beginning if Select is hit
            if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
                state = START;
                break;
            }
            // Process the app for one frame, store the next state
            nextAppState = processAppState(&currentAppState, previousButtons, currentButtons);

            // Wait for VBlank before we do any drawing.
            waitForVBlank();

            // Undraw the previous state
            undrawAppState(&currentAppState);

            // Draw the current state
            drawAppState(&nextAppState);

            // Now set the current state as the next state for the next iter.
            currentAppState = nextAppState;

            // Check if the app is exiting. If it is, then go to the exit state.
            if (nextAppState.gameOver) state = APP_EXIT;
                
            if (nextAppState.won) state = APP_INCREMENT_LEVEL;


            break;
        case APP_EXIT:
            // Wait for VBlank
            waitForVBlank();

            drawFullScreenImageDMA(end);

            state = APP_EXIT_NODRAW;
            break;
        case APP_EXIT_NODRAW:
                //Returns to Start state if Select, A, or Start is hit
                if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
                    state = START;
                }
                
                if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                    state = START;
                }
                
                if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
                    state = START;
                }
            break;
        }

        // Store the current state of the buttons
        previousButtons = currentButtons;
    }

    return 0;
}
