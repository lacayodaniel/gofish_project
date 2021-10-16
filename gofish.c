#include "deck.h"
#include "gofish.h"
#include "player.h"



int main(int args, char* argv[])
{

	shuffle();
	deal_player_cards(&user);
	deal_player_cards(&computer);

	char *p1format = "Player 1's";
	char *p2format = "Player 2's";

	int val = 1;
	int hasCard = 0;
	char *userInput = malloc(sizeof(user.card_list->top.rank));
	while (game_over(&user) == game_over(&computer)) {
		// show player cards
		printHand(&user, p1format);
		printHand(&computer, p2format);
		if (val == 1) {
			userInput = user_play(&user);
			hasCard = search(&computer, userInput);
			if (hasCard == 1){
				printf("    -found a match!\n");
				printf("%d cards transfered\n", transfer_cards(&computer, &user, userInput));
			} else {
				printf("    -Player 2 has no %s 's\n", userInput);
				val = 0;
			}
		} else {
			userInput = computer_play(&computer);
			hasCard = search(&user, userInput);
			if (hasCard == 1){
				printf("    -found a match!\n");
			} else {
				printf("    -Player 1 has no %s 's\n", userInput);
				val = 1;
			}
		}

	}

	//struct card removedCard = user.card_list->top;
	//remove_card(&user, &removedCard);
	//printHand(user.card_list, handFormat);
	//printHand(computer.card_list, handFormat);
	//printf("user.hand_size: %d", user.hand_size);
	char *result = user_play(&user);
	printf("search result: %d\n", search(&computer,result));
	char *result2 = computer_play(&computer);
	printf("computer guess: %s\n", result2);
	return 0;
}

void printHand(struct player *target, char *handFormat){
	struct hand* templist = target->card_list;
	printf("%s Hand: ", handFormat);
	while (templist != NULL){
		printf("%s%s ", templist->top.rank, templist->top.suit);
		templist = templist->next;
	}
	printf("\n%s Book: %s\n", handFormat, target->book);
}
