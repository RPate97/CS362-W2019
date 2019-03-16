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

int runTestOne(struct gameState *state){
    //testing salvager on adventurer card
    printf("1. Testing salvager on the adventurer card\n");
    state->hand[state->whoseTurn][0] = salvager; //place adventurer in hand
    state->hand[state->whoseTurn][1] = adventurer; //place adventurer in hand
    int startingCoins = state->coins;
    int expectedResult = startingCoins + 6; //expecting starting count plus value of adventurer (6)
    
    int choice1 = 1; //setup choices
    int choice2 = 1;
    int choice3 = 0;
    int cardPos = 0;
    cardEffect(salvager, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    char* msg = "incorrect coins value";
    char* msg2 = "incorrect number of buys value";
    if(asserttrue(state->coins, expectedResult, msg, __LINE__, __FILE__)){
        if(asserttrue(state->numBuys, 2, msg2, __LINE__, __FILE__)){
            printf("TEST PASSED\n");
        }else{
            printf("TEST FAILED\n");
        }
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestTwo(struct gameState *state){
    //testing salvager on treasure card (gold)
    printf("2. Testing salvager on a gold treasure card\n");
    state->hand[state->whoseTurn][0] = salvager; //place adventurer in hand
    state->hand[state->whoseTurn][1] = gold; //place adventurer in hand
    int startingCoins = state->coins;
    int expectedResult = startingCoins + 6; //expecting starting count plus value of adventurer (6)
    
    int choice1 = 1; //setup choices
    int choice2 = 1;
    int choice3 = 0;
    int cardPos = 0;
    cardEffect(salvager, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    char* msg = "incorrect coins value";
    char* msg2 = "incorrect number of buys value";
    if(asserttrue(state->coins, expectedResult, msg, __LINE__, __FILE__)){
        if(asserttrue(state->numBuys, 2, msg2, __LINE__, __FILE__)){
            printf("TEST PASSED\n");
        }else{
            printf("TEST FAILED\n");
        }
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
    return 0;
}

int runTestThree(struct gameState *state){
    //testing salvager on itself (shouldn't work)
    printf("3. Testing salvager on the itself\n");
    state->hand[state->whoseTurn][0] = salvager; //place adventurer in hand
    int startingCoins = state->coins;
    int expectedResult = startingCoins; //expecting starting count plus value of adventurer (6)
    
    int choice1 = 1; //setup choices
    int choice2 = 0;
    int choice3 = 0;
    int cardPos = 0;
    cardEffect(salvager, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    char* msg = "incorrect coins value";
    char* msg2 = "incorrect number of buys value";
    if(asserttrue(state->coins, expectedResult, msg, __LINE__, __FILE__)){
        if(asserttrue(state->numBuys, 1, msg2, __LINE__, __FILE__)){
            printf("TEST PASSED\n");
        }else{
            printf("TEST FAILED\n");
        }
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
    return 0;
}

int runTestFour(struct gameState *state){
    //testing salvager on negative number for card (shouldn't work)
    printf("4. Testing salvager on a card that doesn't exist (negative number)\n");
    state->hand[state->whoseTurn][0] = salvager; //place adventurer in hand
    state->hand[state->whoseTurn][1] = adventurer; //place adventurer in hand
    int startingCoins = state->coins;
    int expectedResult = startingCoins; //expecting starting count plus value of adventurer (6)
    
    int choice1 = 1; //setup choices
    int choice2 = -1;
    int choice3 = 0;
    int cardPos = 0;
    cardEffect(salvager, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    char* msg = "incorrect coins value";
    char* msg2 = "incorrect number of buys value";
    if(asserttrue(state->coins, expectedResult, msg, __LINE__, __FILE__)){
        if(asserttrue(state->numBuys, 2, msg2, __LINE__, __FILE__)){
            printf("TEST PASSED\n");
        }else{
            printf("TEST FAILED\n");
        }
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
    return 0;
}

int main (int argc, char** argv) {
    printf("***************************************************************\n"); //formatting
    printf ("Starting test suite of salvager card.\n"); //caption
    
    int gameSeed = 9999;
    struct gameState G;
    struct gameState back;
    int numPlayers = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(numPlayers, k, gameSeed , &G);
    
    memcpy(&back, &G, sizeof(struct gameState)); //copy gamestate into backup so i can compare between them and switch back to the original easily
    runTestOne(&G); //run the tests
    
    memcpy(&G, &back, sizeof(struct gameState));
    runTestTwo(&G);
    
    memcpy(&G, &back, sizeof(struct gameState));
    runTestThree(&G);

    memcpy(&G, &back, sizeof(struct gameState));
    runTestFour(&G);
    return 0; //return 0
}