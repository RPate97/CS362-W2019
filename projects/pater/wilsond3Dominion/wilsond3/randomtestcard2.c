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
int validateResults(struct gameState *state, struct gameState *backupState, int choice){

    int choiceCost = getCost(handCard(choice, state)); //get cost of card being discarded
    int failedOne = 0;
    int failedTwo = 0;
    int failedThree = 0;
    if(state->numBuys != (backupState->numBuys + 1)){ //check if number of actions correct
        failedOne = 1;
    }
    if(state->coins != backupState->coins + choiceCost){ //check if number of coins correct
        failedTwo = 2;
    }
    if(state->playedCardCount <= backupState->playedCardCount){ //check if number of discards correct
        failedThree = 3;
    }

    if(failedOne == 0 && failedTwo == 0 && failedThree == 0){ //return 0 if all tests passed
        return 0;
    }else{ //print game state if any test failed
        printf("*****************************\n");
        printf("Starting GameState: \n");
        printGameState(backupState); //print gamestate 
    }

    if(failedOne == 1){ //print relevant values based on which test failed
        printf("Starting Buys: %d\n", backupState->numBuys); //print relevant values
        printf("Ending Buys: %d\n", state->numBuys);
        printf("Error incorrect number of buyss after playing salvager\n"); //print error
        return 0;
    }
    if(failedTwo == 2){
        printf("Starting coins: %d\n", backupState->coins); //print relevant values
        printf("Ending coins: %d\n", state->coins);
        printf("Error incorrect number of coins after playing salvager\n"); //print error
        return 0;
    }
    if(failedThree == 3){
        printf("Starting Played Count: %d\n", backupState->playedCardCount); //print relevant values
        printf("Ending Played Count: %d\n", state->playedCardCount);
        printf("Error incorrect number of played cards after playing salvager\n"); //print error
        return 0;
    }

    return 2;
}

int main (int argc, char** argv) {
    printf("TESTING CARD: Salvager\n");
    srand(time(0));

    struct gameState state; //create states
    struct gameState backupState;

    int numPassed = 0; //setup oracle vars
    int numFailed = 0;
    int totalRan = 0;
    do{
        generateGameState(&state); //generate random state

        state.hand[state.whoseTurn][0] = salvager; //put smithy in hand since we're testing it
        copyGameState(&state, &backupState); //create backup of gamestate for comparison and reset
        int choice1 = (rand() % 4) + 1; //randomly generate choice of card to trash
        playCard(0, choice1, 0, 0, &state); //play the card
        if(validateResults(&state, &backupState, choice1) == 0){
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