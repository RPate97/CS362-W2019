#include "randomtesthelpers.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//validate ending game state
int validateResults(struct gameState *state, struct gameState *backupState){
    if(state->numActions != (backupState->numActions - 1)){ //check if number of actions correct
        printf("*****************************\n");
        printf("Starting GameState: \n");
        printGameState(backupState); //print gamestate
        printf("Starting Actions: %d\n", backupState->numActions); //print relevant values
        printf("Ending Actions: %d\n", state->numActions);
        printf("Error incorrect number of actions after playing adventurer\n"); //print error
        return 0;
    }else if(state->coins <= backupState->coins){ //check if number of coins correct
        printf("*****************************\n");
        printf("Starting GameState: \n");
        printGameState(backupState); //print gamestate
        printf("Starting coins: %d\n", backupState->coins); //print relevant values
        printf("Ending coins: %d\n", state->coins);
        printf("Error incorrect number of coins after playing adventurer\n"); //print error
        return 0;
    }else if(state->discardCount[state->whoseTurn] <= backupState->discardCount[backupState->whoseTurn]){ //check if number of discards correct
        printf("*****************************\n");
        printf("Starting GameState: \n");
        printGameState(backupState); //print gamestate 
        printf("Starting Discard Count: %d\n", backupState->discardCount[backupState->whoseTurn]); //print relevant values
        printf("Ending Discards: %d\n", state->discardCount[state->whoseTurn]);
        printf("Error incorrect number of discards after playing adventurer\n"); //print error
        return 0;
    }else{
        return 1;
    }
}

int main (int argc, char** argv) {
    printf("TESTING CARD: Adventurer\n");
    srand(time(0));

    struct gameState state; //create states
    struct gameState backupState;

    int numPassed = 0; //setup oracle vars
    int numFailed = 0;
    int totalRan = 0;
    do{
        generateGameState(&state); //generate random state

        int deckIsEmpty = rand() % 101; //gen random number for if deck is empty (doing this to get full coverage of the adventurer card function) 1% chance
        if(deckIsEmpty == 100){
            int curPlayer = state.whoseTurn;
            int y;
            for(y = 0; y < state.deckCount[curPlayer]; y++){
                state.discard[curPlayer][y] = state.deck[curPlayer][y]; //copy deck into discards
                state.deck[curPlayer][y] = 0; //0 out the deck
            }
            state.deckCount[curPlayer] = 0; //set deck count to 0
        }

        state.hand[state.whoseTurn][0] = adventurer; //put adventurer in hand since we're testing it
        copyGameState(&state, &backupState); //create backup of gamestate for comparison and reset
        playCard(0, 0, 0, 0, &state);
        if(validateResults(&state, &backupState) == 0){
            printf("TEST %d\n", totalRan);
            printf("TEST FAILED\n");
            numFailed++;
        }else{
            //printf("TEST PASSED\n");
            numPassed++;
        }

        //printf("seg 6\n");
        copyGameState(&backupState, &state); //copy backup back to state so it can be run again
        totalRan++;
    }while(numFailed < 1000 && totalRan < 10000); //run until 1000 failures or 10000 tests
    printf("*****************************\n");
    printf("Total number of tests ran: %d\n", totalRan); //print overall results
    printf("Total Failures: %d\n", numFailed);
    printf("Total Successes: %d\n", numPassed);
    float percent = ((float)numPassed / (float)totalRan) * 100;
    printf("%.2f%% of tests passed\n", percent); //print success percentage

    return 0;
}
