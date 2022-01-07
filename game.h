//
// Created by Aleksandra Ruminska on 08/12/2019.
//

#ifndef WAR_GAME_H
#define WAR_GAME_H

#endif //WAR_GAME_H

void InitDeck(deck_t * deck, int deck_size, int cards_in_color);
void SwapCards(deck_t &deck1, deck_t &deck2);
void ShuffleCards(deck_t *deck, int deck_size);
void PutOnTheTable(struct stack *player1, struct stack *player2, struct stack *table_p1, struct stack *table_p2);
void PrintStack(struct stack *s, char name [12]);
int Battle(player_t *player1, player_t *player2, struct stack *table1, struct stack *table2);
int War(player_t * player1, player_t * player2, struct stack *table1, struct stack *table2, int no_of_wars, char mode, int borrowed_cards, int interaction_mode);
void FreeQueues(player_t * player);
int CheckOtherPlayer(player_t * player1, player_t * player2);
int PlayCards(deck_t* deck, int deck_size, int interaction_mode, char play_mode, int is_first);