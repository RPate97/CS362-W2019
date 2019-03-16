#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int asserttrue(int a, int b, char* msg, int line, const char* file){
    if(a != b){
        printf("Error on line %d in file %s: %s\n", line, file, msg);
        return 0;
    }else{
        return 1;
    }
}

int runTestOne(struct gameState *state){
    //test if hand has no treasure
    printf("1. Testing if the correct amount of coins are computed when the player has no treasure\n");
    state->hand[state->whoseTurn][0] = 0;
    state->hand[state->whoseTurn][1] = 0;
    state->hand[state->whoseTurn][2] = 0;
    state->hand[state->whoseTurn][3] = 0;
    state->hand[state->whoseTurn][4] = 0;
    updateCoins(state->whoseTurn, state, 0);
    char* msg = "updateCoins failed to compute the correct amount of coins for case 1";
    if(asserttrue(state->coins, 0, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestTwo(struct gameState *state){
    //test if hand has all treasure
    printf("2. Testing if the correct amount of coins are computed when the players whole hand is full of treasures\n");
    state->hand[state->whoseTurn][0] = copper;
    state->hand[state->whoseTurn][1] = silver;
    state->hand[state->whoseTurn][2] = gold;
    state->hand[state->whoseTurn][3] = gold;
    state->hand[state->whoseTurn][4] = gold;
    updateCoins(state->whoseTurn, state, 0);
    char* msg = "updateCoins failed to compute the correct amount of coins for case 2";
    if(asserttrue(state->coins, 12, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestThree(struct gameState *state){
    //test if hand has two gold
    printf("3. Testing if the correct amount of coins are computed when the player has two gold\n");
    state->hand[state->whoseTurn][0] = 0;
    state->hand[state->whoseTurn][1] = gold;
    state->hand[state->whoseTurn][2] = 0;
    state->hand[state->whoseTurn][3] = gold;
    state->hand[state->whoseTurn][4] = 0;
    updateCoins(state->whoseTurn, state, 0);
    char* msg = "updateCoins failed to compute the correct amount of coins for case 3";
    if(asserttrue(state->coins, 6, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestFour(struct gameState *state){
    //test if hand has three silver
    printf("4. Testing if the correct amount of coins are computed when the player has three silver\n");
    state->hand[state->whoseTurn][0] = silver;
    state->hand[state->whoseTurn][1] = 0;
    state->hand[state->whoseTurn][2] = silver;
    state->hand[state->whoseTurn][3] = 0;
    state->hand[state->whoseTurn][4] = silver;
    updateCoins(state->whoseTurn, state, 0);
    char* msg = "updateCoins failed to compute the correct amount of coins for case 4";
    if(asserttrue(state->coins, 6, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestFive(struct gameState *state){
    //test if hand has four copper
    printf("5. Testing if the correct amount of coins are computed when the player has four copper\n");
    state->hand[state->whoseTurn][0] = copper;
    state->hand[state->whoseTurn][1] = copper;
    state->hand[state->whoseTurn][2] = copper;
    state->hand[state->whoseTurn][3] = copper;
    state->hand[state->whoseTurn][4] = 0;
    updateCoins(state->whoseTurn, state, 0);
    char* msg = "updateCoins failed to compute the correct amount of coins for case 5";
    if(asserttrue(state->coins, 4, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}


int main (int argc, char** argv) {
    printf("***************************************************************\n");
    printf ("Starting test suite of function updateCoins.\n");

    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    
    initializeGame(2, k, 22, &G); //init game state
    runTestOne(&G);
    
    initializeGame(2, k, 22, &G); //i chose to reinit before every test to make sure nothing was off from the previous test. Not very efficient, but this is a test suite so it's not a big deal really
    runTestTwo(&G);               //better than passing a test that should of failed because my case isn't setup correctly 
    
    initializeGame(2, k, 22, &G);
    runTestThree(&G);
    
    initializeGame(2, k, 22, &G);
    runTestFour(&G);
    
    initializeGame(2, k, 22, &G);
    runTestFive(&G);

    return 0;
}