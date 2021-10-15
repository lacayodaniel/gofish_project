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

	return 0;
}

int remove_card(struct player* target, struct card* old_card){
	struct hand* iterator = target->card_list;
	struct hand* previous = NULL;
	if (iterator == NULL) { return -1; }
	printf("iterator s, %s\n",iterator->top.suit);
	printf("iterator c, %c\n",iterator->top.suit);
	while ((strcmp(iterator->top.suit, old_card->suit) != 0) && (strcmp(iterator->top.rank, old_card->rank) != 0)){
		previous = iterator;
		iterator = iterator->next;
		if (iterator == NULL) { return -1; }
	}
	if (previous != NULL){
		previous->next = iterator->next;
	} else {
		target->card_list = iterator->next;
	}
	free(iterator);
	return 0;
}

// 0->game continue 1->game over
int game_over(struct player* target){
	size_t bookLen = strlen(target->book);
	if (bookLen == 7) { return 1; }
	return 0;
}
