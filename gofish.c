#include "deck.h"
void printHand(struct hand* cardInHand, char *handFormat);


int main(int args, char* argv[]) 
{
	struct player user = {NULL, NULL, 0};
	struct player computer = {NULL, NULL, 0};
	shuffle();
	deal_player_cards(&user);
	deal_player_cards(&computer);
	// show player cards
	char *handFormat = "Player 1's Hand:";
	printHand(user.card_list, handFormat);
	char *p2HandFormat = "Player 2's Hand:";
	printHand(computer.card_list, p2HandFormat);
	struct card removedCard = user.card_list->top;
	//remove_card(&user, &removedCard);
	//printHand(user.card_list, handFormat);
	//printHand(computer.card_list, handFormat);
	
	return 0;
}

void printHand(struct hand* cardInHand, char *handFormat){
	printf("%s ", handFormat);
	while (cardInHand != NULL){
		printf("%s", cardInHand->top.rank);
		printf("%s ", cardInHand->top.suit);
		cardInHand = cardInHand->next;
	}
	printf("\n");
}
