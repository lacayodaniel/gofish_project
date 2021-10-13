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


