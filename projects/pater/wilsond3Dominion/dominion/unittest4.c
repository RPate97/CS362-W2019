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
    //test getting the card at each hand position
    printf("Testing getting each card from the players hand\n");
    int cardTotal = 29; //set expected car total
    state->hand[state->whoseTurn][0] = curse; 
    state->hand[state->whoseTurn][1] = adventurer; //set some cards 
    state->hand[state->whoseTurn][2] = smithy; 
    state->hand[state->whoseTurn][3] = silver; 
    state->hand[state->whoseTurn][4] = copper;
    int x = 0; 
    int total = 0;
    for(x = 0; x < 5; x++){ //iterate through the hand
        total += handCard(x, state); //get each card and add them to a running total
    }
    char* msg = "failed to get the correct cards from the players hand";
    if(asserttrue(total, cardTotal, msg, __LINE__, __FILE__)){ //compare computed total to expected total
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestTwo(struct gameState *state){
    //test getting a card at position -1
    printf("Testing getting card the card at position -1 from the players hand\n");
    state->hand[state->whoseTurn][0] = curse; //set some cards
    state->hand[state->whoseTurn][1] = adventurer; 
    state->hand[state->whoseTurn][2] = smithy; 
    state->hand[state->whoseTurn][3] = silver; 
    state->hand[state->whoseTurn][4] = copper;
    int card = handCard(-1, state);
    char* msg = "failed to get detect -1 as invalid position";
    if(asserttrue(card, -1, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestThree(struct gameState *state){
    //test getting a card at position 6 (outside of range)
    printf("Testing getting each the card at position 6 from the players hand\n");
    state->hand[state->whoseTurn][0] = curse; //set some cards
    state->hand[state->whoseTurn][1] = adventurer; 
    state->hand[state->whoseTurn][2] = smithy; 
    state->hand[state->whoseTurn][3] = silver; 
    state->hand[state->whoseTurn][4] = copper;
    int card = handCard(6, state);
    char* msg = "failed to get detect 6 as invalid position";
    if(asserttrue(card, -1, msg, __LINE__, __FILE__)){
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}


int main (int argc, char** argv) {
    printf("***************************************************************\n");
    printf ("Starting test suite of function handCard.\n");

    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    
    initializeGame(2, k, 22, &G); //init game state
    runTestOne(&G);
    
    initializeGame(2, k, 22, &G); //i chose to reinit before every test to make sure nothing was off from the previous test. Not very efficient, but this is a test suite so it's not a big deal really
    runTestTwo(&G);               //better than passing a test that should of failed because my case isn't setup correctly 
    
    initializeGame(2, k, 22, &G);
    runTestThree(&G);

    return 0;
}