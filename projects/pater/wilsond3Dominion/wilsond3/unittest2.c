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
    //testing if the game is over when the province supply count is greater than 0 should be no
    printf("1. Testing if the game is over when the province supply is > 0\n");
    state->supplyCount[province] = 10;
    char* msg = "isGameOver() test one failed\n";
    if(asserttrue(isGameOver(state), 0, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestTwo(struct gameState *state){
    //testing if the game is over when the province supply count is = 0 should be yes
    printf("2. Testing if the game is over when the province supply is = 0\n");
    state->supplyCount[province] = 0;
    char* msg = "isGameOver() test two failed\n";
    if(asserttrue(isGameOver(state), 1, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestThree(struct gameState *state){
    //testing if the game is over when the supply count is negative should be yes to avoid double subtraction problems
    printf("3. Testing if the game is over when the province supply is < 0\n");
    state->supplyCount[province] = -1;
    char* msg = "isGameOver() test three failed";
    if(asserttrue(isGameOver(state), 1, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestFour(struct gameState *state){
    //testing if the game is over when tg different supplies that are not province are = 0 should be no
    printf("4. Testing if the game is over when two different supplies that are not province are = 0\n");
    state->supplyCount[curse] = 0;
    state->supplyCount[estate] = 0;
    char* msg = "isGameOver() test four failed\n";
    if(asserttrue(isGameOver(state), 0, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestFive(struct gameState *state){
    //testing if the game is over when three different supplies that are not province are = 0 should be yes
    printf("5. Testing if the game is over when three different supplies that are not province are = 0\n");
    state->supplyCount[curse] = 0;
    state->supplyCount[estate] = 0;
    state->supplyCount[duchy] = 0;
    char* msg = "isGameOver() test five failed\n";
    if(asserttrue(isGameOver(state), 1, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestSix(struct gameState *state){
    //testing if the game is over when three different supplies that are not province are negative should be yes to avoid double subtraction problems
    printf("6. Testing if the game is over when three different supplies that are not province are < 0\n");
    state->supplyCount[curse] = -1;
    state->supplyCount[estate] = -1;
    state->supplyCount[duchy] = -1;
    char* msg = "isGameOver() test six failed";
    if(asserttrue(isGameOver(state), 1, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int main (int argc, char** argv) {
    printf("***************************************************************\n");
    printf ("Starting test suite of function isGameOver.\n");

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
    
    initializeGame(2, k, 22, &G);
    runTestSix(&G);

    return 0;
}