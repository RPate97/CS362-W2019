#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
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
    //test with 2 coppers
    printf("1. Testing if the adventurer finds two coppers in the players deck.\n");

    state->hand[state->whoseTurn][0] = adventurer; //place adventurer in hand

    int x = 0; //loop var
    int expectedCopperCount = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //get the number of coppers starting in the players hand
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            expectedCopperCount++;
        }
    }
    expectedCopperCount += 2; //add two since we know there are only 2 coppers and no other treasure in the deck so we can expect that the adventurer will find two coppers

    state->deckCount[state->whoseTurn] = 0; //set deck count back to 0 since we're going to overwrite it
    for(x = 0; x < 20; x++){ //loop to 20 cards
        do{ 
            state->deck[state->whoseTurn][x] = rand() % 27; //randomly generate a car
        }while(state->deck[state->whoseTurn][x] == copper || state->deck[state->whoseTurn][x] == silver || state->deck[state->whoseTurn][x] == gold);//use a do while to prevent the card from being copper, silver, or gold since we want to control those ourselves
        state->deckCount[0]++; //add to deckcount once a card is finalized
    }
    int numOne = (rand() % 20) + 1;//generate two random numbers doesnt need to be that random really
    int numTwo;
    do{
        numTwo = (rand() % 20) + 1; //make sure it doesnt select 0 since we're gonna put the adventurer at 0
    }while(numOne == numTwo); //use do while to make sure they aren't the same

    state->deck[state->whoseTurn][numOne] = copper; //set card at those positions to copper
    state->deck[state->whoseTurn][numTwo] = copper;

    int choice1 = 1; //setup choices
    int choice2 = 0;
    int choice3 = 0;
    int cardPos = 0;
    cardEffect(adventurer, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    
    int copperCount = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //look through the players hand and count up the number of coppers
        if(state->hand[state->whoseTurn][x] == copper){
            copperCount++;
        }
    }

    char* msg = "incorrect number of treasures found in hand";
    if(asserttrue(copperCount, expectedCopperCount, msg, __LINE__, __FILE__)){ //check if the number of coppers equals the expected number
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestTwo(struct gameState *state){
    //test with 2 silvers
    printf("2. Testing if the adventurer finds two silvers in the players deck.\n");

    state->hand[state->whoseTurn][0] = adventurer; //place adventurer in hand

    int x = 0; //loop var
    int expectedCount = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //get the number of coppers starting in the players hand
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            expectedCount++;
        }
    }
    expectedCount += 2; //add two since we know there are only 2 coppers and no other treasure in the deck so we can expect that the adventurer will find two coppers

    state->deckCount[state->whoseTurn] = 0; //set deck count back to 0 since we're going to overwrite it
    for(x = 0; x < 20; x++){ //loop to 20 cards
        do{ 
            state->deck[state->whoseTurn][x] = rand() % 27; //randomly generate a car
        }while(state->deck[state->whoseTurn][x] == copper || state->deck[state->whoseTurn][x] == silver || state->deck[state->whoseTurn][x] == gold);//use a do while to prevent the card from being copper, silver, or gold since we want to control those ourselves
        state->deckCount[0]++; //add to deckcount once a card is finalized
    }
    int numOne = (rand() % 20) + 1;//generate two random numbers doesnt need to be that random really
    int numTwo;
    do{
        numTwo = (rand() % 20) + 1; //make sure it doesnt select 0 since we're gonna put the adventurer at 0
    }while(numOne == numTwo); //use do while to make sure they aren't the same

    state->deck[state->whoseTurn][numOne] = silver; //set card at those positions to copper
    state->deck[state->whoseTurn][numTwo] = silver;

    int choice1 = 1; //setup choices
    int choice2 = 0;
    int choice3 = 0;
    int cardPos = 0;
    cardEffect(adventurer, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    
    int count = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //look through the players hand and count up the number of coppers
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            count++;
        }
    }

    char* msg = "incorrect number of treasures found in hand"; 
    if(asserttrue(count, expectedCount, msg, __LINE__, __FILE__)){ //check if the number of coppers equals the expected number
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
    return 0;
}

int runTestThree(struct gameState *state){
    //test with 2 golds
    printf("3. Testing if the adventurer finds two golds in the players deck.\n");

    state->hand[state->whoseTurn][0] = adventurer; //place adventurer in hand

    int x = 0; //loop var
    int expectedCount = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //get the number of coppers starting in the players hand
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            expectedCount++;
        }
    }
    expectedCount += 2; //add two since we know there are only 2 coppers and no other treasure in the deck so we can expect that the adventurer will find two coppers

    state->deckCount[state->whoseTurn] = 0; //set deck count back to 0 since we're going to overwrite it
    for(x = 0; x < 20; x++){ //loop to 20 cards
        do{ 
            state->deck[state->whoseTurn][x] = rand() % 27; //randomly generate a car
        }while(state->deck[state->whoseTurn][x] == copper || state->deck[state->whoseTurn][x] == silver || state->deck[state->whoseTurn][x] == gold);//use a do while to prevent the card from being copper, silver, or gold since we want to control those ourselves
        state->deckCount[0]++; //add to deckcount once a card is finalized
    }
    int numOne = (rand() % 20) + 1;//generate two random numbers doesnt need to be that random really
    int numTwo;
    do{
        numTwo = (rand() % 20) + 1; //make sure it doesnt select 0 since we're gonna put the adventurer at 0
    }while(numOne == numTwo); //use do while to make sure they aren't the same

    state->deck[state->whoseTurn][numOne] = gold; //set card at those positions to copper
    state->deck[state->whoseTurn][numTwo] = gold;

    int choice1 = 1; //setup choices
    int choice2 = 0;
    int choice3 = 0;
    int cardPos = 0;
    cardEffect(adventurer, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    
    int count = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //look through the players hand and count up the number of coppers
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            count++;
        }
    }

    char* msg = "incorrect number of treasures found in hand"; 
    if(asserttrue(count, expectedCount, msg, __LINE__, __FILE__)){ //check if the number of coppers equals the expected number
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
    return 0;
}

int runTestFour(struct gameState *state){
    //test with copper and silver
    printf("4. Testing if the adventurer finds a copper and a silver in the players deck.\n");

    state->hand[state->whoseTurn][0] = adventurer; //place adventurer in hand

    int x = 0; //loop var
    int expectedCount = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //get the number of coppers starting in the players hand
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            expectedCount++;
        }
    }
    expectedCount += 2; //add two since we know there are only 2 coppers and no other treasure in the deck so we can expect that the adventurer will find two coppers

    state->deckCount[state->whoseTurn] = 0; //set deck count back to 0 since we're going to overwrite it
    for(x = 0; x < 20; x++){ //loop to 20 cards
        do{ 
            state->deck[state->whoseTurn][x] = rand() % 27; //randomly generate a car
        }while(state->deck[state->whoseTurn][x] == copper || state->deck[state->whoseTurn][x] == silver || state->deck[state->whoseTurn][x] == gold);//use a do while to prevent the card from being copper, silver, or gold since we want to control those ourselves
        state->deckCount[0]++; //add to deckcount once a card is finalized
    }
    int numOne = (rand() % 20) + 1;//generate two random numbers doesnt need to be that random really
    int numTwo;
    do{
        numTwo = (rand() % 20) + 1; //make sure it doesnt select 0 since we're gonna put the adventurer at 0
    }while(numOne == numTwo); //use do while to make sure they aren't the same

    state->deck[state->whoseTurn][numOne] = copper; //set card at those positions to copper
    state->deck[state->whoseTurn][numTwo] = silver;

    int choice1 = 1; //setup choices
    int choice2 = 0;
    int choice3 = 0;
    int cardPos = 0;
    cardEffect(adventurer, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    
    int count = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //look through the players hand and count up the number of coppers
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            count++;
        }
    }

    char* msg = "incorrect number of treasures found in hand"; 
    if(asserttrue(count, expectedCount, msg, __LINE__, __FILE__)){ //check if the number of coppers equals the expected number
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
    return 0;
}

int runTestFive(struct gameState *state){
    //test with silver and gold
    printf("5. Testing if the adventurer finds one silver and one gold in the players deck.\n");

    state->hand[state->whoseTurn][0] = adventurer; //place adventurer in hand

    int x = 0; //loop var
    int expectedCount = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //get the number of coppers starting in the players hand
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            expectedCount++;
        }
    }
    expectedCount += 2; //add two since we know there are only 2 coppers and no other treasure in the deck so we can expect that the adventurer will find two coppers

    state->deckCount[state->whoseTurn] = 0; //set deck count back to 0 since we're going to overwrite it
    for(x = 0; x < 20; x++){ //loop to 20 cards
        do{ 
            state->deck[state->whoseTurn][x] = rand() % 27; //randomly generate a car
        }while(state->deck[state->whoseTurn][x] == copper || state->deck[state->whoseTurn][x] == silver || state->deck[state->whoseTurn][x] == gold);//use a do while to prevent the card from being copper, silver, or gold since we want to control those ourselves
        state->deckCount[0]++; //add to deckcount once a card is finalized
    }
    int numOne = (rand() % 20) + 1;//generate two random numbers doesnt need to be that random really
    int numTwo;
    do{
        numTwo = (rand() % 20) + 1; //make sure it doesnt select 0 since we're gonna put the adventurer at 0
    }while(numOne == numTwo); //use do while to make sure they aren't the same

    state->deck[state->whoseTurn][numOne] = silver; //set card at those positions to copper
    state->deck[state->whoseTurn][numTwo] = gold;

    int choice1 = 1; //setup choices
    int choice2 = 0;
    int choice3 = 0;
    int cardPos = 0;
    cardEffect(adventurer, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    
    int count = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //look through the players hand and count up the number of coppers
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            count++;
        }
    }

    char* msg = "incorrect number of treasures found in hand"; 
    if(asserttrue(count, expectedCount, msg, __LINE__, __FILE__)){ //check if the number of coppers equals the expected number
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
    return 0;
}

int runTestSix(struct gameState *state){
    //test with copper and gold
    printf("6. Testing if the adventurer finds one copper and one gold in the players deck.\n");

    state->hand[state->whoseTurn][0] = adventurer; //place adventurer in hand

    int x = 0; //loop var
    int expectedCount = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //get the number of coppers starting in the players hand
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            expectedCount++;
        }
    }
    expectedCount += 2; //add two since we know there are only 2 coppers and no other treasure in the deck so we can expect that the adventurer will find two coppers

    state->deckCount[state->whoseTurn] = 0; //set deck count back to 0 since we're going to overwrite it
    for(x = 0; x < 20; x++){ //loop to 20 cards
        do{ 
            state->deck[state->whoseTurn][x] = rand() % 27; //randomly generate a car
        }while(state->deck[state->whoseTurn][x] == copper || state->deck[state->whoseTurn][x] == silver || state->deck[state->whoseTurn][x] == gold);//use a do while to prevent the card from being copper, silver, or gold since we want to control those ourselves
        state->deckCount[0]++; //add to deckcount once a card is finalized
    }
    int numOne = (rand() % 20) + 1;//generate two random numbers doesnt need to be that random really
    int numTwo;
    do{
        numTwo = (rand() % 20) + 1; //make sure it doesnt select 0 since we're gonna put the adventurer at 0
    }while(numOne == numTwo); //use do while to make sure they aren't the same

    state->deck[state->whoseTurn][numOne] = copper; //set card at those positions to copper
    state->deck[state->whoseTurn][numTwo] = gold;

    int choice1 = 1; //setup choices
    int choice2 = 0;
    int choice3 = 0;
    int cardPos = 0;
    cardEffect(adventurer, choice1, choice2, choice3, state, cardPos, 0); //start card effect
    
    int count = 0;
    for(x = 0; x < state->handCount[state->whoseTurn]; x++){ //look through the players hand and count up the number of coppers
        if(state->hand[state->whoseTurn][x] == copper || state->hand[state->whoseTurn][x] == silver || state->hand[state->whoseTurn][x] == gold){
            count++;
        }
    }

    char* msg = "incorrect number of treasures found in hand"; 
    if(asserttrue(count, expectedCount, msg, __LINE__, __FILE__)){ //check if the number of coppers equals the expected number
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
    return 0;
    return 0;
}


int main (int argc, char** argv) {
    printf("***************************************************************\n"); //formatting
    printf ("Starting test suite of Adventurer.\n"); //caption
    
    srand(time(0)); //set random seed for generating decks
    int gameSeed = 9999;
    struct gameState G;
    struct gameState back;
    int numPlayers = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(numPlayers, k, gameSeed , &G);
    
    memcpy(&back, &G, sizeof(struct gameState)); //copy gamestate into backup so i can compare between them and switch back to the original easily
    runTestOne(&G); //run the tests
    
    memcpy(&G, &back, sizeof(struct gameState)); //copy backup over into gamestate so I know the starting state is the same during each test
    runTestTwo(&G);
    
    memcpy(&G, &back, sizeof(struct gameState));
    runTestThree(&G);

    memcpy(&G, &back, sizeof(struct gameState));
    runTestFour(&G);

    memcpy(&G, &back, sizeof(struct gameState));
    runTestFive(&G);

    memcpy(&G, &back, sizeof(struct gameState));
    runTestSix(&G);
    return 0; //return 0
}