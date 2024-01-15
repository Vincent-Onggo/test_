/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) Project
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] =
        {"2","3","4","5","6","7",
         "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
    /******** You complete ****************/
    for(int i=NUM_CARDS-1; i>0; i--){
        int j = rand() % (i+1);
        int temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }

}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Must use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id)
{
    /******** You complete ****************/
    cout << type[id%13] << "-" << suit[id/13];


}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Must use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id)
{
    /******** You complete ****************/
    return value[id%13];

}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
    /******** You complete ****************/
    for(int i=0; i<numCards; i++){
        printCard(hand[i]);
        cout << " ";
    }
    cout << endl;


}

/**
 * Should return the total score of the provided hand.
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    /******** You complete ****************/
    int handValue = 0;
    int numOfAces = 0;
    for(int i=0; i<numCards;i++){
        if(hand[i]%13 == 12){
            numOfAces++;
        }
        handValue += cardValue(hand[i]);
    }
    while(handValue > 21 and numOfAces > 0) {
        handValue -= 10;
        numOfAces--;
    }
    return handValue;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
    //---------------------------------------
    // Do not change this code -- Begin
    //---------------------------------------
    if(argc < 2){
        cout << "Error - Please provide the seed value." << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    srand(seed);

    int cards[52];
    int dhand[9];
    int phand[9];
    //---------------------------------------
    // Do not change this code -- End
    //---------------------------------------

    /******** You complete ****************/

    // initialize cards array
    memset(phand, -1, sizeof(phand));
    memset(dhand, -1, sizeof(dhand));
    char playAgainOpt = 'y';

    while(playAgainOpt == 'y'){
        for(int i=0; i<NUM_CARDS; i++){
            cards[i] = i;
        }

        // shuffle
        shuffle(cards);

        // first deal
        int topCard = 0;
        int dCount, pCount;
        dCount = 0; pCount = 0;
        for(int i=0; i<2; i++){
            phand[pCount] = cards[topCard];
            topCard++; pCount++;
            dhand[dCount] = cards[topCard];
            topCard++; dCount++;
        }

        // Interaction
        cout << "Dealer: ? ";
        printCard(dhand[1]);
        cout << endl;

        cout << "Player: ";
        printHand(phand, pCount);


        char choice;
        cout << "Type 'h' to hit and 's' to stay:\n";
        cin >> choice;
        bool bust = false;

        while(choice == 'h' or choice == 's'){
            cout << "Type 'h' to hit and 's' to stay:\n";
            cin >> choice;
            if(choice == 'h'){
                pCount+=1;
                phand[pCount-1] = cards[topCard];
                topCard += 1;
                int phandValue = getBestScore(phand, pCount);
                if(phandValue > 21) {
                    bust = true;
                }
                cout << "Player: ";
                printHand(phand, pCount);

                if(bust){
                    cout << "Player busts\n";
                    cout << "Lose " << getBestScore(phand, pCount) << " " << getBestScore(dhand, dCount) << endl;
                    break;
                }

            }

            cout << "Type 'h' to hit and 's' to stay:\n";
            cin >> choice;



            bool dealerbust = false;
            if(choice == 's'){
                int dhandvalue = getBestScore(dhand, dCount);
                while(dhandvalue < 17 and dhandvalue < 22){
                    dCount++;
                    dhand[dCount-1] = cards[topCard];
                    topCard++;
                    dhandvalue = getBestScore(dhand, dCount);
                    if(dhandvalue > 21){
                        dealerbust = true;
                    }
                }
                if(dealerbust){
                    cout << "Dealer: ";
                    printHand(dhand, dCount);
                    cout << "Dealer busts\n";
                    cout << "Win " << getBestScore(phand, pCount) << " " << getBestScore(dhand, dCount) << endl;
                    break;
                }
            }

            // no one busts
            if(!dealerbust and !bust and choice == 's'){
                if(getBestScore(phand,pCount) > getBestScore(dhand, dCount)){
                    cout << "Win " << getBestScore(phand, pCount) << " " << getBestScore(dhand, dCount) << endl;
                }else if(getBestScore(phand,pCount) < getBestScore(dhand, dCount)){
                    cout << "Lose " << getBestScore(phand, pCount) << " " << getBestScore(dhand, dCount) << endl;
                }else{
                    cout << "Tie " << getBestScore(phand, pCount) << " " << getBestScore(dhand, dCount) << endl;
                }
                break;
            }



        }
        if(choice != 'h' and choice != 's'){
            break;
        }





        cout << endl;
        cout << "Play again? [y/n]" << endl;
        cin >> playAgainOpt;
    }

    return 0;
}