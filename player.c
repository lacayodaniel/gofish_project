#include "player.h"

/*
 * Function: add_card
 * -------------------
 *  Add a new card to the player's hand.
 *
 *  target: the target player
 *  new_card: pointer to the new card to add
 *
 *  returns: return 0 if no error, non-zero otherwise
 */
int add_card(struct player* target, struct card* new_card){
	struct hand* temp;
	temp = (struct hand*)malloc(sizeof(struct hand));
	if (temp == NULL) { return -1; }
	temp->top = *new_card;
	temp->next = target->card_list;
	target->card_list = temp;
	target->hand_size++;

	return 0;
}

int remove_card(struct player* target, struct card* old_card){
	struct hand* iterator = target->card_list;
	struct hand* previous = NULL;
	if (iterator == NULL) { return -1; }
	while ((strcmp(iterator->top.suit, old_card->suit) != 0) && (strcmp(iterator->top.rank, old_card->rank) != 0)){
		previous = iterator;
		iterator = iterator->next;
		if (iterator == NULL) { return -1; } // empty condition
	}
	if (previous != NULL){
		previous->next = iterator->next;
	} else {
		target->card_list = iterator->next;
	}
	target->hand_size--;
	free(iterator);
	return 0;
}

//1->target has rank 0->target does not have rank
int search(struct player* target, char *rank){
	struct hand* iterator = target->card_list;
	if (iterator == NULL) { return -1; }
	//printf("rank %s", iterator->top.rank);
	while (strcmp(iterator->top.rank, rank) != 0){
		iterator = iterator->next;
		if (iterator == NULL) { return 0; }
	}
	return 1;
}

int transfer_cards(struct player* src, struct player* dest, char *rank){
	int cardsTransfered = 0;
	struct hand* iterator = src->card_list;
	struct hand* previous = NULL;
	if (iterator == NULL) { return -1; }
	while (iterator != NULL){ // while list is not empty
		if (strcmp(iterator->top.rank, rank) == 0){ // if we have a match
			// add card to dest hand
			struct hand* filler = malloc(sizeof(struct hand));
			filler->top = iterator->top;
			filler->next = dest->card_list;
			dest->card_list = filler;
			dest->hand_size++;
			if (iterator == src->card_list){ // if the match is top level
				// remove card from src hand
				src->card_list = iterator->next;
			} else {
				// remove card from src hand
				previous->next = iterator->next;
			}
			src->hand_size--;
			cardsTransfered++;
		} else {
			previous = iterator;
		}
		iterator = iterator->next;
	}
	return cardsTransfered;
}

char* computer_play(struct player* target){
	struct hand* iterator = target->card_list;
	// produce [0,6]
	int randCard = (rand() % (int)(target->hand_size));
	for (int i = 0; i<randCard; i++){
		iterator = iterator->next;
	}
	char *pans = malloc(sizeof(target->card_list->top.rank));
	pans = iterator->top.rank;
	printf("Player 2's turn, enter a Rank: %s\n", pans);
	return pans;
}


char* user_play(struct player* target){
	char ans[3];
	char *pans = malloc(sizeof(ans));
	if (pans == NULL) {return NULL; }
	int userHasRank = 0;
	while (userHasRank == 0){
		printf("Player 1's turn, enter a Rank:");
		scanf("%s", pans);
		userHasRank = search(target, pans);
		if (userHasRank == 0){
			printf("Error - must have at least one card from rank to play\n");
		}
	}

	return pans;
}
// 0->game continue 1->game over
int game_over(struct player* target){
	size_t bookLen = strlen(target->book);
	if (bookLen == 7) { return 1; }
	return 0;
}
