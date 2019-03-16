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
    int choice1 = 1; //setup choices
    int choice2 = 0;
    int choice3 = 0;
    int cardPos = 0;
    state->hand[state->whoseTurn][0] = village; //place adventurer in hand 
    
    //test if card is drawn, correct number of actions is added and card is discarded
    printf("1. Testing if the village draws a card\n");
    int expectedCards = state->handCount[state->whoseTurn]; //village draws a card then discards itself so number of cards should stay the same
    cardEffect(village, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    char* msg = "incorrect number of cards in hand";
    if(asserttrue(expectedCards, state->handCount[state->whoseTurn], msg, __LINE__, __FILE__)){ //check if correct number of cards in hand
        printf("TEST PASSED\n");
    }else{
        printf("TEST FAILED\n");
    }
    
    printf("2. Checking if actions are adjusted correctly\n");
    char* msg2 = "incorrect number of actions left";
    if(asserttrue(state->numActions, 3, msg2, __LINE__, __FILE__)){ //since I am testing by directly calling card effect rather than playCard I don't expect the actions from using the village cards to be counted so this test expects to get 3 actions
        printf("TEST PASSED\n");
    }else{
        printf("TEST FAILED\n");
    }

    printf("3. Checking if the village card has been discarded\n");
    char* msg3 = "village was not discarded";
    int foundVillage = 0;
    int x = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){
        if(state->hand[state->whoseTurn][x] == village){
            foundVillage = 1;
        }
    }
    if(asserttrue(foundVillage, 0, msg3, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
    }else{
        printf("TEST FAILED\n");
    }
    return 0;
}

int main (int argc, char** argv) {
    printf("***************************************************************\n"); //formatting
    printf ("Starting test suite of village card.\n"); //caption
    
    int gameSeed = 9999;
    struct gameState G;
    int numPlayers = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(numPlayers, k, gameSeed , &G);

    runTestOne(&G); //run the tests
    return 0; //return 0
}