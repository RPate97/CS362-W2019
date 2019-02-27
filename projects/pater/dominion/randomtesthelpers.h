#ifndef _RANDOMTESTHELPERS_H
#define _RANDOMTESTHELPERS_H
#include "dominion.h"

void copyGameState(struct gameState*, struct gameState*);

void generateGameState(struct gameState*);

int printGameState(struct gameState*);

#endif