#include "deck.h"
#include "gofish.h"
//#include "player.h"

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
	char *bookCard = malloc(sizeof(user.card_list->top.rank));
	while (game_over(&user) == game_over(&computer)) {
		// show player cards
		printHand(&user, p1format);
		printHand(&computer, p2format);
		if (val == 1) {
			userInput = user_play(&user);
			hasCard = search(&computer, userInput);
			if (hasCard == 1){
				printf("    -Player 2 has ");
				transfer_cards(&computer, &user, userInput);
				bookCard = check_add_book(&user);
				if (strcmp(bookCard, "0") != 0){
					printf("    -Player 1 books %s\n", bookCard);
					strcat(bookCard, " ");
					strcat(user.book, bookCard);
				}
			} else {
				printf("    -Player 2 has no %s's\n", userInput);
				struct card* cardDrawn = next_card();
				printf("    -Go Fish, Player 1 draws %s%s\n", cardDrawn->rank, cardDrawn->suit);
				add_card(&user, cardDrawn);
				val = 0;
			}
		} else {
			userInput = computer_play(&computer);
			hasCard = search(&user, userInput);
			if (hasCard == 1){
				printf("   -Player 1 has ");
				transfer_cards(&user, &computer, userInput);
				bookCard = check_add_book(&computer);
				if (strcmp(bookCard, "0") != 0){
					printf("    -Player 2 books %s\n", bookCard);
					strcat(bookCard, " ");
					strcat(computer.book, bookCard);
				}
			} else {
				printf("    -Player 1 has no %s's\n", userInput);
				struct card* cardDrawn = next_card();
				printf("    -Go Fish, Player 2 draws a card\n");
				add_card(&computer, cardDrawn);
				val = 1;
			}
		}

	}
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
