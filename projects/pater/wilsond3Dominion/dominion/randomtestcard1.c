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
    if(state->handCount[state->whoseTurn] != backupState->handCount[backupState->whoseTurn] + 2){
        printf("*****************************\n");
        printf("Starting GameState: \n");
        printGameState(backupState); //print gamestate 
        printf("Starting handCount: %d\n", backupState->handCount[backupState->whoseTurn]); //print relevant values
        printf("Ending handCount: %d\n", state->handCount[state->whoseTurn]);
        printf("Error incorrect number of cards in hand after playing smithy\n"); //print error
    }else if(state->discardCount[state->whoseTurn] <= backupState->discardCount[backupState->whoseTurn]){ //check if number of discards correct
        printf("*****************************\n");
        printf("Starting GameState: \n");
        printGameState(backupState); //print gamestate 
        printf("Starting Discard Count: %d\n", backupState->discardCount[backupState->whoseTurn]); //print relevant values
        printf("Ending Discards: %d\n", state->discardCount[state->whoseTurn]);
        printf("Error incorrect number of discards after playing smithy\n"); //print error
        return 0;
    }else{
        return 1;
    }
    return 2;
}

int main (int argc, char** argv) {
    printf("TESTING CARD: Smithy\n");
    srand(time(0));

    struct gameState state; //create states
    struct gameState backupState;

    int numPassed = 0; //setup oracle vars
    int numFailed = 0;
    int totalRan = 0;
    do{
        generateGameState(&state); //generate random state

        state.hand[state.whoseTurn][0] = smithy; //put smithy in hand since we're testing it
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