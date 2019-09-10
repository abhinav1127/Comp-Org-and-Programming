#ifndef GRAPHICS_SEEN
#define GRAPHICS_SEEN

#include "logic.h"

// This function will be used to draw everything about the state of your app
// including the background and whatnot.
void fullDrawAppState(AppState *state);

// This function will be used to undraw (i.e. erase) things that might
// move in a frame.
void undrawAppState(AppState *state);
// This function will be used to draw things that might have moved in a frame.
void drawAppState(AppState *state);

#endif
