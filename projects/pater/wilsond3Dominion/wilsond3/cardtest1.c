#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int asserttrue(int a, int b, char* msg, int line, const char* file){
    if(a != b){
        printf("Error on line %d in file %s: %s\n", line, file, msg);
        return 0;
    }else{
        return 1;
    }
}

int runTestOne(struct gameState *state, struct gameState *backState){
    //test choice 1 = +3 cards does add 3 cards
    printf("1. Testing if the smithy card adds 3 cards to the players hand.\n");
    int choice1 = 1;
    int choice2 = 0;
    int choice3 = 0;
    state->hand[state->whoseTurn][0] = smithy;
    int cardPos = 0;
    cardEffect(smithy, choice1, choice2, choice3, state, cardPos, 0);
    char* msg = "error playing smithy card did not add 3 to handCount";
    if(asserttrue(state->handCount[state->whoseTurn], (backState->handCount[state->whoseTurn] + 2), msg, __LINE__, __FILE__)){ //check if handcount is updated +2
        printf("TEST PASSED\n");
    }else{
        printf("TEST FAILED\n");
    }

    return 0;
}

int runTestTwo(struct gameState *state, struct gameState *backState){
    //test choice 1 = +3 cards does discard smithy card
    printf("2. Testing if the smithy card is discarded from the players hand.\n");
    int choice1 = 1;
    int choice2 = 0;
    int choice3 = 0;
    state->hand[state->whoseTurn][0] = smithy;
    int cardPos = 0;
    cardEffect(smithy, choice1, choice2, choice3, state, cardPos, 0);
    int x = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){
        if(state->hand[state->whoseTurn][x] == smithy){
            printf("TEST FAILED\n");
            return 1;
        }
    }
    printf("TEST PASSED\n");
    return 0;
}

int main (int argc, char** argv) {
    printf("***************************************************************\n"); //formatting
    printf ("Starting test suite of Smithy.\n"); //caption
    
    int gameSeed = 9999;
    struct gameState G;
    struct gameState back;
    int numPlayers = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(numPlayers, k, gameSeed , &G);
    
    memcpy(&back, &G, sizeof(struct gameState)); //copy gamestate into backup so i can compare between them and switch back to the original easily
    runTestOne(&G, &back); //run the tests
    
    memcpy(&G, &back, sizeof(struct gameState));
    runTestTwo(&G, &back);

    return 0; //return 0
}