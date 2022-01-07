//
// Created by Aleksandra Ruminska on 08/12/2019.
//

#include <iostream>
#include <stdlib.h>
#include "queue.h"
using namespace std;

//Checking if the queue is empty
int CheckIfEmpty(struct stack s){
    if(s.number_of_cards == 0){
        return 1;
    }

    return 0;
}

//Adding card at the beginning of the queue
void AddToBeginning(struct stack * s, card new_card) {
    queue_t * new_item;

    if(s->number_of_cards==0){

        if(s->elements == NULL){
            s->elements=(queue_t*) malloc(sizeof(queue_t));
        }
        s->elements->card=new_card;

        s->elements->next=NULL;

    }else {

        new_item = (queue_t*) malloc(sizeof(queue_t));
        new_item->card = new_card;
        new_item->next = s->elements;

        s->elements = new_item;
    }

    s->number_of_cards++;
}

//Adding card at the end of the queue
void AddToEnd(struct stack * s, card new_card) {

    if(s->elements == NULL){
        s->elements = (queue_t*) malloc(sizeof(queue_t));
        s->elements->card = new_card;
        s->number_of_cards++;
        s->elements->next = NULL;
        return;
    } else {

        queue_t * current = s->elements;

        while(true){

            if(current->next == NULL){
                break;
            }else {
                current = current->next;
            }
        }

        current->next = (queue_t*) malloc(sizeof(queue_t));
        current->next->card = new_card;
        current->next->next = NULL;

    }

    s->number_of_cards++;
}

//Removing card from the beginning of the queue
card RemoveFromBeginning(struct stack * s) {
    queue_t * next_item = NULL;
    card removed;
    removed.card_value = -1;

    if (s->elements == NULL){
        cout << "No card to remove";
        return removed;
    }

    next_item = (s->elements)->next;

    removed = (s->elements)->card;

    s->elements = next_item;

    s->number_of_cards--;

    return removed;
}

//Removing card from one queue and adding to other
void MoveBetweenQueues(struct stack * destination, struct stack * source, int where_to_move) {
    card element;

    if(CheckIfEmpty(*source)==0) {
        element = (RemoveFromBeginning(source));


        if (where_to_move == 0) {
            AddToBeginning(destination, element);
        } else {
            AddToEnd(destination, element);
        }
    }
}