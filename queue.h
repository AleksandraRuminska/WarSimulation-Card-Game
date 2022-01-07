//
// Created by Aleksandra Ruminska on 08/12/2019.
//

#ifndef WAR_QUEUE_H
#define WAR_QUEUE_H

#endif //WAR_QUEUE_H
#define MAX_COLOR_SIZE 9

struct deck_t {
    int card_value;
    char color[MAX_COLOR_SIZE];
};

typedef struct queue {
    struct deck_t card;
    struct queue * next;
}queue_t;

struct stack {
    int number_of_cards;
    queue_t * elements;
};

typedef struct stack player_t;
typedef struct stack table;
typedef struct deck_t card;


int CheckIfEmpty(struct stack s);
void AddToBeginning(struct stack * s, card new_card);
void AddToEnd(struct stack * s, card new_card);
card RemoveFromBeginning(struct stack * s) ;
void MoveBetweenQueues(struct stack * destination, struct stack * source, int where_to_move);
