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

int runTestOne(){
    //get the cost of all cards in k and compare to known correct value
    printf("1. Testing returned card values against expected values\n");
    int numCards = 27;
    int vals[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4}; // init values and cards
    int cards[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    int x; 
    int failed = 1;
    for(x = 0; x < numCards; x++){ //loop through cards
        char* msg = "cardVals() test one failed on incorrect card value\n";
        if(asserttrue(getCost(cards[x]), vals[x], msg, __LINE__, __FILE__)){ //use asserttrue function to check if the cost is correct
            failed = 0; //set return to 1 to indicate failure
        }
    }
    if(failed == 0){ //print sucess if no mismatching values found
        printf("TEST PASSED\n");
    }else{ //if any cards where found with mismatching values print failure
        printf("TEST FAILED\n");
    }
    return failed;
}

int runTestTwo(){
    printf("2. Testing card value that doesn't exist: below range (-1)\n");
    char* msg = "cardVals() test two failed testing for a value that does not exist: -1\n";
    if(asserttrue(getCost(-1),-1, msg, __LINE__, __FILE__)){ //check for default value -1 for int that isn't in the switch
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }
}

int runTestThree(){
    printf("3. Testing card value that doesn't exist: above range (28)\n"); 
    char* msg = "cardVals() test two failed testing for a value that does not exist: 28\n";
    if(asserttrue(getCost(28),-1, msg, __LINE__, __FILE__)){ //check for default value -1 for int that isn't in the switch
        printf("TEST PASSED\n");
        return 0;
    }else{
        printf("TEST FAILED\n");
        return 1;
    }

}

int main (int argc, char** argv) {
    printf("***************************************************************\n"); //formatting
    printf ("Starting test suite of function getCost.\n"); //caption
    runTestOne(); //run the tests
    runTestTwo();
    runTestThree();
    return 0; //return 0
}