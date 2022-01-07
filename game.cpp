//
// Created by Aleksandra Ruminska on 08/12/2019.
//

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "game.h"
using namespace std;

char color1[] = {"HEARTS"};
char color2[] = {"DIAMONDS"};
char color3[] = {"SPADES"};
char color4[] = {"CLUBS"};

//Initialization of deck
void InitDeck(deck_t * deck, int deck_size, int cards_in_color) {
    int i;
    int j;
    int k;
    int min_val=0;

    for (j = 52, k=0 ; j>=deck_size; j -= 4, k++){
        min_val = 2 + k;
    }
    // cout << "Min value: " << min_val <<endl;

    for (i = 0; i < cards_in_color; i++){

        deck[i].card_value = min_val+i;
        strcpy(deck[i].color, color1);

        deck[i+cards_in_color].card_value = min_val+i;
        strcpy(deck[i+cards_in_color].color, color2);

        deck[i+2*cards_in_color].card_value = min_val+i;
        strcpy(deck[i+2*cards_in_color].color, color3);

        deck[i+3*cards_in_color].card_value = min_val+i;
        strcpy(deck[i+3*cards_in_color].color, color4);

        //cout << "D[i]: " << deck[i].card_value <<endl;
    }
}

//Changing 2 cards values
void SwapCards(deck_t &deck1, deck_t &deck2){
    deck_t temp = deck1;
    deck1 = deck2;
    deck2 = temp;
}

//Shuffling entire deck
void ShuffleCards(deck_t *deck, int deck_size) {
    int i;
    int s=0;

    srand(time(0));

    for(i=0; i<deck_size; i++){
        s = rand() % deck_size;
        SwapCards(deck[i], deck[s]);
    }
}


//Removing card from hand and putting it into table
void PutOnTheTable(struct stack *player1, struct stack *player2, struct stack *table_p1, struct stack *table_p2) {

    MoveBetweenQueues(table_p1, player1, 0);

    MoveBetweenQueues(table_p2, player2, 0);

    //cout << endl;
}

//Printing cards in hand/ on the table
void PrintStack(struct stack *s, char name [12]){
    cout << endl << "Cards for: " << name <<endl;
    cout << "Number of elements: " << s->number_of_cards <<endl;


    queue_t * current = s->elements;

    cout << "Cards: " <<endl;


    if (s->number_of_cards == 0){
        cout << "EMPTY! ";
        return;
    }


    while(true){
        if (current->card.card_value > 1 && current->card.card_value < 11) {
            cout << current->card.card_value << " " << current->card.color << ", ";
        } else {
            if(current->card.card_value == 11){
                cout << "J" << " " << current->card.color << ", ";
            }
            if(current->card.card_value == 12){
                cout << "Q" << " " << current->card.color << ", ";
            }
            if(current->card.card_value == 13){
                cout << "K" << " " << current->card.color << ", ";
            }
            if(current->card.card_value == 14){
                cout << "A" << " " << current->card.color << ", ";
            }
        }

        if(current->next == NULL){
            break;
        }else {
            current = current->next;
        }
    }

    cout << endl;
}

// Checking greater card
int Battle(player_t *player1, player_t *player2, struct stack *table1, struct stack *table2){

    int war = 0;

    if(table1->elements->card.card_value > table2->elements->card.card_value){

        MoveBetweenQueues(player1, table1, 1);

        MoveBetweenQueues(player1, table2, 1);

    } else {

        if(table2->elements->card.card_value > table1->elements->card.card_value) {
            MoveBetweenQueues(player2, table2, 1);

            MoveBetweenQueues(player2, table1, 1);

        } else {
            if(table1->elements->card.card_value == table2->elements->card.card_value){
                war = 1;
            }
        }
    }

    return war;
}


//Checking if the other player has more than 3 cards
int CheckOtherPlayer(player_t * player1, player_t * player2){
    if (player1->number_of_cards <= 3 && player1->number_of_cards != 0) {
        MoveBetweenQueues(player1, player2, 1);
        return 1;
    } else {
        if (player1->number_of_cards <= 3 && player1->number_of_cards != 1 ) {
            return 2;
        } else {
            return 0;
        }
    }
}

//War function
int War(player_t * player1, player_t * player2, struct stack *table1, struct stack *table2, int no_of_wars, char mode,
        int borrowed_cards, int interaction_mode){
    int i=0;
    int all_cards_tab1=0;
    int all_cards_tab2=0;
    int nr_player1_cards=0;
    int nr_player2_cards=0;
    int nr_of_moves = 0;

    if (mode == 'A' || ((mode == 'B' && no_of_wars>1) && borrowed_cards==1) ) {
        if(interaction_mode==1) {
            cout << endl << "IN WAR, MODE A P1= " << player1->number_of_cards << "P2= " << player2->number_of_cards
                 << endl;
        }
        if (player1->number_of_cards < 2){

            all_cards_tab1 = table1->number_of_cards;
            all_cards_tab2 = table2->number_of_cards;

            for(i=0; i<all_cards_tab2; i++){
                MoveBetweenQueues(player2, table2 ,1);
            }

            for(i=0; i<all_cards_tab1; i++){
                MoveBetweenQueues(player2, table1 ,1);
            }

            for(i=0; i<player2->number_of_cards; i++){
                MoveBetweenQueues(player2, player1 ,1);
            }

            return nr_of_moves;

        } else {
            if (player2->number_of_cards < 2){

                all_cards_tab1 = table1->number_of_cards;
                all_cards_tab2 = table2->number_of_cards;

                for(i=0; i<all_cards_tab1; i++){
                    MoveBetweenQueues(player1, table1 ,1);
                }

                for(i=0; i<all_cards_tab2; i++){
                    MoveBetweenQueues(player1, table2 ,1);
                }

                for(i=0; i<player2->number_of_cards; i++){
                    MoveBetweenQueues(player1, player2 ,1);
                }

                return nr_of_moves;
            } else {
                nr_of_moves += 2;
                PutOnTheTable(player1, player2, table1, table2);
                PutOnTheTable(player1, player2, table1, table2);
            }
        }

    } else {
        if(interaction_mode==1) {
            cout << endl << "IN WAR, MODE B P1= " << player1->number_of_cards << " P2= " << player2->number_of_cards
                 << endl;
        }
        nr_player1_cards = player1->number_of_cards;
        nr_player2_cards = player2->number_of_cards;

        borrowed_cards = 1;
        if (nr_player1_cards == 1) {

            if (CheckOtherPlayer(player2, player1) == 2){
                MoveBetweenQueues(player2, table2, 1);
                MoveBetweenQueues(player2, table1, 1);
            }
            nr_of_moves += 2;
            PutOnTheTable(player1, player2, table1, table2);
            PutOnTheTable(player2, player2, table1, table2);

        } else if (nr_player1_cards == 0) {

            if (CheckOtherPlayer(player2, player1) == 1){
                MoveBetweenQueues(player2, table2, 1);
                MoveBetweenQueues(player2, table1, 1);
            }
            nr_of_moves += 2;
            PutOnTheTable(player2, player2, table1, table1);
            PutOnTheTable(player2, player2, table2, table2);


        } else if (nr_player2_cards == 1) {

            if (CheckOtherPlayer(player1, player2) == 2){
                MoveBetweenQueues(player1, table1, 1);
                MoveBetweenQueues(player1, table2, 1);
            }
            nr_of_moves += 2;
            PutOnTheTable(player1, player2, table1, table2);
            PutOnTheTable(player1, player1, table2, table1);

        } else if (nr_player2_cards == 0) {

            if (CheckOtherPlayer(player1, player2) == 1){
                MoveBetweenQueues(player1, table1, 1);
                MoveBetweenQueues(player1, table2, 1);
            }

            nr_of_moves += 2;
            PutOnTheTable(player1, player1, table2, table2);
            PutOnTheTable(player1, player1, table1, table1);

        } else {
            borrowed_cards = 0;
            nr_of_moves += 2;
            PutOnTheTable(player1, player2, table1, table2);
            PutOnTheTable(player1, player2, table1, table2);
        }
    }
    if(interaction_mode==1) {
        cout << endl << "IN WAR, P1= " << player1->number_of_cards << " P2= " << player2->number_of_cards << endl;
        PrintStack(table1, "Table1");
        PrintStack(table2, "Table2");
        cout << endl << "IN WAR, P1= " << player1->number_of_cards << " P2= " << player2->number_of_cards << endl;

        cout << endl;
    }

    all_cards_tab1 = table1->number_of_cards;
    all_cards_tab2 = table2->number_of_cards;


    if(table1->elements->card.card_value > table2->elements->card.card_value){

        for(i=0; i<all_cards_tab1; i++) {
            MoveBetweenQueues(player1, table1, 1);
        }

        for(i=0; i<all_cards_tab2; i++) {
            MoveBetweenQueues(player1, table2, 1);
        }
        borrowed_cards = 0;

    } else {

        if(table2->elements->card.card_value > table1->elements->card.card_value) {

            for(i=0; i<all_cards_tab2; i++) {
                MoveBetweenQueues(player2, table2, 1);
            }

            for(i=0; i<all_cards_tab1; i++) {
                MoveBetweenQueues(player2, table1, 1);
            }
            borrowed_cards = 0;

        } else {

            if(table1->elements->card.card_value == table2->elements->card.card_value){
                return War(player1, player2, table1, table2, no_of_wars+1, mode, borrowed_cards, interaction_mode);
            }
        }
    }

    return nr_of_moves;
}

// Freeing allocated memory at the end
void FreeQueues(player_t * player) {
    int i=0;
    if (player != NULL) {

        while (i<(player->number_of_cards)) {
            queue_t * current = player->elements;

            while (current->next != NULL) {

                current = current->next;
            }

            current = NULL;
            free(current);
            i++;
        }
    }
}

//The main game
int PlayCards(deck_t* deck, int deck_size, int interaction_mode, char play_mode, int is_first){
    int i;
    int m;
    int nr_of_moves=0;
    player_t player1;
    player_t player2;
    table table1;
    table table2;
    int rank_p1=0;
    int rank_p2=0;

    player1.elements = NULL;
    player1.elements = (queue_t*) malloc(sizeof(queue_t));
    player2.elements = NULL;
    player2.elements = (queue_t*) malloc(sizeof(queue_t));

    table1.elements = NULL;
    table1.elements = (queue_t*) malloc(sizeof(queue_t));
    table1.number_of_cards=0;

    table2.elements = NULL;
    table2.elements = (queue_t*) malloc(sizeof(queue_t));
    table2.number_of_cards=0;

    //cout << endl;

    ShuffleCards(deck, deck_size);

    player1.elements->card = deck[0];
    player2.elements->card = deck[1];

    player1.elements->next = (queue_t*) malloc(sizeof(queue_t));
    player2.elements->next = (queue_t*) malloc(sizeof(queue_t));



    queue_t * next_p1 = player1.elements->next;
    queue_t * next_p2 = player2.elements->next;


    for (i=2; i<deck_size; i+=2) {
        next_p1->card = deck[i];
        next_p2->card = deck[i + 1];

        if (i == (deck_size - 2)) {
            next_p1->next=NULL;
            next_p2->next=NULL;

        } else {
            next_p1->next = (queue_t *) malloc(sizeof(queue_t));
            next_p2->next = (queue_t *) malloc(sizeof(queue_t));

            next_p1 = next_p1->next;
            next_p2 = next_p2->next;
        }
    }


    player1.number_of_cards=deck_size/2;
    player2.number_of_cards=deck_size/2;

    queue_t * temp1 = player1.elements;
    queue_t * temp2 = player2.elements;


    //if (is_first==0) {
    int sum=0;



    while (temp1 != NULL) {
        // if(temp1->card.card_value > 10){
        //rank_p1 += temp1->card.card_value;
        //    }else{
        rank_p1 += temp1->card.card_value;
        //}
        temp1 = temp1->next;
    }

    while (temp2!= NULL) {
        //  if(temp2->card.card_value > 10){
        // rank_p2 += temp2->card.card_value;
        //  }else{
        rank_p2 += temp2->card.card_value;
        //   }
        temp2 = temp2->next;
    }



    // }

    if(interaction_mode==1) {
        PrintStack(&player1, "Player 1");
        PrintStack(&player2, "Player 2 ");
        PrintStack(&table1, "Table 1");
        PrintStack(&table2, "Table 2");
    }


    do {

        PutOnTheTable(&player1, &player2, &table1, &table2);
        nr_of_moves++;

        if (Battle(&player1, &player2, &table1, &table2)==1) {


            nr_of_moves += War(&player1, &player2, &table1, &table2,1, play_mode, 0, interaction_mode);
            if(interaction_mode==1) {
                cout << endl << "AFTER WAR !!! " << endl;

                PrintStack(&player1, "Player 1");
                PrintStack(&player2, "Player 2 ");
            }

        }else{
            if(interaction_mode==1) {
                PrintStack(&player1, "Player 1");
                PrintStack(&player2, "Player 2 ");
            }
            //PrintStack(&table1, "Table 1");
            //PrintStack(&table2, "Table 2");
        }


        if (player1.number_of_cards == 0){
            if(interaction_mode==1) {
                cout << endl << endl << "Player 2 is the winner!" << endl;
                cout << endl << endl << "Moves: " << nr_of_moves << endl;
            }
            FreeQueues(&player1);
            FreeQueues(&player2);
            // The line below was used to show the outcome of experiment 2
            cout << deck_size << ", " << play_mode << ", " << rank_p1 << ", " << "0, " << rank_p2 << ", 1" << endl ;
        }

        if (player2.number_of_cards == 0) {
            if(interaction_mode==1) {
                cout << endl << endl << "Player 1 is the winner!" << endl;
                cout << endl << endl << "Moves: " << nr_of_moves << endl;
            }
            FreeQueues(&player1);
            FreeQueues(&player2);
            // The line below was used to show the outcome of experiment 2
            cout << deck_size << ", " << play_mode << ", " << rank_p1 << ", " << "1, " << rank_p2 << ", 0" << endl ;
        }

    } while(player1.number_of_cards>0 && player2.number_of_cards>0);

    return nr_of_moves;
}