#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "game.h"
using namespace std;

// Aleksandra Rumińska
// War - game, experiment 1, experiment 2
// Iteration mode 1 is use for the game
//Iteration mode 0 is use for experiments


int main(){


    int deck_size = 0;
    char play_mode;
    int nr_of_moves = 0;
    int cards_in_color;
    int interaction_mode = 1;
    int number_of_simulations = 1000;
    int is_first=0;


    cout << "Enter interaction mode (0 or 1):  ";
    cin >> interaction_mode;
    cout << endl;

    if(!cin){
        cout << "ERROR - wrong data" << endl;
        cin.clear();
        cin.ignore(65535, '\n');
        return -1;
    }

    if(interaction_mode != 0 && interaction_mode != 1){
        cout << "Wrong value" << endl;
        return -1;
    }

    if(interaction_mode == 1) {
        cout << "Choose size of deck: 20, 24, 28, 32, 36, 40, 44, 48, 52" << endl;
        cin >> deck_size;
        cout << endl;

        if(!cin){
            cout << "ERROR - wrong data" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
            return -1;
        }

        if (deck_size != 20 && deck_size != 24 && deck_size != 28 && deck_size != 32 && deck_size != 36 &&
            deck_size != 40 && deck_size != 44 && deck_size != 48 && deck_size != 52) {
            cout << "Wrong size of the deck! Try again!" << endl;
            return -1;
        }

        cout << "Enter a mode 'A' or 'B': ";
        cin >> play_mode;
        cout << endl;

        if(!cin){
            cout << "ERROR - wrong data" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
            return -1;
        }

        if (play_mode != 'A' && play_mode != 'B') {
            cout << "Wrong mode! Try again!" << endl;
            return -1;
        }

    }


    if (interaction_mode ==0) {

        double mean_value = 0.0;
        cout << endl;

        for (int a = 0; a < 2; a++) { //game mode
            if (a == 0) {
                play_mode = 'A';
            } else {
                play_mode = 'B';
            }
            for (int aa = 20; aa <= 52; aa += 4) {
                mean_value = 0.0;

                cards_in_color = aa/4;
                struct deck_t * deck;
                deck = (deck_t*) malloc(aa*sizeof(deck_t));
                InitDeck(deck, aa, cards_in_color);

                for (int aaa = 0; aaa < number_of_simulations; aaa++) {

                    is_first = aaa;
                    nr_of_moves = PlayCards(deck, aa, interaction_mode, play_mode, is_first);
                    mean_value += nr_of_moves;

                }

                mean_value = mean_value / number_of_simulations;
                cout << "Mode: " << play_mode << ", Deck size: " << aa << ", " << ", Moves= " << nr_of_moves << endl << endl;
                // The line below is used in the first experiment
                cout << "Mode: " << play_mode << ", Deck size: " << aa << ", " << ", Mean= " << mean_value;
                free(deck);
            }

        }
    }//end iteration mode 1
    else {
        cards_in_color = deck_size/4;
        struct deck_t deck[deck_size];
        InitDeck(deck, deck_size, cards_in_color);
        nr_of_moves = PlayCards(deck, deck_size, interaction_mode, play_mode, is_first);
    }



    cout << endl;

    return 0;
}