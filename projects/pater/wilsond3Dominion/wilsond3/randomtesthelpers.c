#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "randomtesthelpers.h"

//make a deepcopy of a gameState
void copyGameState(struct gameState *state, struct gameState *backupState){
    backupState->numPlayers = state->numPlayers; //copy numplayers

    int x = 0;
    for(x = 0; x <= treasure_map; x++){ 
        backupState->supplyCount[x] = state->supplyCount[x]; //copy supplies
    }

    for(x = 0; x <= treasure_map; x++){ 
        backupState->embargoTokens[x] = state->embargoTokens[x]; //copy embargo tokens
    }

    //copy misc
    backupState->outpostPlayed = state->outpostPlayed;
    backupState->outpostTurn = state->outpostTurn;
    backupState->whoseTurn = state->whoseTurn;
    backupState->phase = state->phase;
    backupState->numActions = state->numActions;
    backupState->coins = state->coins;
    backupState->numBuys = state->numBuys;

    //copy hands
    for(x = 0; x <= state->numPlayers; x++){
        int y;
        for(y = 0; y < 5; y++){
            backupState->hand[x][y] = state->hand[x][y];
        }
        backupState->handCount[x] = state->handCount[x];
    }

    //copy decks
    for(x = 0; x <= state->numPlayers; x++){
        int y;
        for(y = 0; y < state->deckCount[x]; y++){
            backupState->deck[x][y] = state->deck[x][y];
        }
        backupState->deckCount[x] = state->deckCount[x];
    }

    //copy discards
    for(x = 0; x <= state->numPlayers; x++){
        int y;
        for(y = 0; y < state->discardCount[x]; y++){
            backupState->discard[x][y] = state->discard[x][y];
        }
        backupState->discardCount[x] = state->discardCount[x];
    }

    backupState->playedCardCount = state->playedCardCount;
}

//generates a random gameState
void generateGameState(struct gameState *state){
    state->numPlayers = rand() % (4 + 1 - 2) + 2; //get num players

    int x = 0;
    for(x = 0; x <= treasure_map; x++){ //fill supply array
        if(state->numPlayers == 2){
            state->supplyCount[x] = rand() % 11; //up to 10 if 2 players
        }else if(state->numPlayers == 3){
            state->supplyCount[x] = rand() % 21; //up to 20 if three players
        }else{
            state->supplyCount[x] = rand() % 31; //up to 30 if four players
        }
    }

    for(x = 0; x <= treasure_map; x++){
        state->embargoTokens[x] = rand() % 2;
    }

    state->outpostPlayed = 0; //default 0
    state->outpostTurn = 0; //default 0
    state->whoseTurn = rand() % state->numPlayers; //gen random players turn
    state->phase = 0; //either buy or action phase 0 or 1
    state->numActions = 1; //always start with 1 action no matter what
    state->coins = 0; //coins come from playing treasure so start with 0 always
    state->numBuys = 1; //default 1 buy
    
    //generate hands
    for(x = 0; x < state->numPlayers; x++){ //iterate through each player
        int y;
        for(y = 0; y < 5; y++){
            state->hand[x][y] = rand() % 27; //generate hands of random cards up to int 27
        }
        state->handCount[x] = 5; //set handcount to 5
    }

    //generate decks
    for(x = 0; x < state->numPlayers; x++){
        int y = 0;
        int deckSize = rand() % 51; //generate deck size number up to 30
        for(y = 0; y < deckSize; y++){
            state->deck[x][y] = rand() % 27; //generate decks of random cards up to int 27
        }
        for(y = 0; y < 6; y++){ //add in default coppers
            state->deck[x][y+deckSize] = copper;
        }
        for(y = 0; y < 3; y++){
            state->deck[x][y+deckSize] = estate;
        }
        state->deckCount[x] = (deckSize+10); //set decksize
        shuffle(x, state); //shuffle deck
    }

    //generate discards
    for(x = 0; x < state->numPlayers; x++){
        int y;
        int discardSize = rand() % 50; //generate discard size number up to 50
        for(y = 0; y < discardSize; y++){
            state->discard[x][y] = rand() % 27; //generate discards of random cards up to int 27
        }
        state->discardCount[x] = discardSize;
    }

    //set playedCards to 0
    for(x = 0; x < 500; x++){
        state->playedCards[x] = 0;
    }

    state->playedCardCount = 0;

    return;
}

//print a gamestate structure
int printGameState(struct gameState *state){
    printf("numplayers: %d\n", state->numPlayers);
    
    int x = 0;
    for(x = 0; x <= treasure_map; x++){
        printf("supple %d: %d\n", x, state->supplyCount[x]);
    }

    for(x = 0; x <= treasure_map; x++){
        printf("embargo %d: %d\n", x, state->embargoTokens[x]);
        state->embargoTokens[x] = rand() % 2;
    }

    printf("outpostPlayed: %d\n", state->outpostPlayed);
    printf("outpostTurn: %d\n", state->outpostTurn);
    printf("whoseTurn: %d\n", state->whoseTurn);
    printf("phase: %d\n", state->phase);
    printf("numActions: %d\n", state->numActions);
    printf("coins: %d\n", state->coins);
    printf("numBuys: %d\n", state->numBuys);
    
    //print hands
    for(x = 0; x < state->numPlayers; x++){ 
        printf("hand %d:", x);
        int y;
        for(y = 0; y < 5; y++){
            printf("%d, ", state->hand[x][y]);
        }
        printf("\nhandCount: %d\n", state->handCount[x]);
    }

    //print decks
    for(x = 0; x < state->numPlayers; x++){
        printf("deck %d:", x);
        int y;
        for(y = 0; y < state->deckCount[x]; y++){
            printf("%d, ", state->deck[x][y]);
        }
        printf("\ndeckCount: %d\n", state->deckCount[x]);
    }

    //generate discards
    for(x = 0; x < state->numPlayers; x++){
        printf("discard %d:", x);
        int y;
        for(y = 0; y < state->discardCount[x]; y++){
            printf("%d, ", state->discard[x][y]);
        }
        printf("\ndiscardCount: %d\n", state->discardCount[x]);
    }

    //print playcards
    printf("playedCards: ");
    for(x = 0; x < 500; x++){
        printf("%d, ", state->playedCards[x]);
    }
    printf("\n");

    printf("playedCardCount: %d\n", state->playedCardCount);

    return 0;
}