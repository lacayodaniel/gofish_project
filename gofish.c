#include "deck.h"
#include "gofish.h"
//#include "player.h"

int main(int args, char* argv[])
{
	char *p1format = "Player 1's";
	char *p2format = "Player 2's";
	int isUserTurn;
	char *userInput = malloc(sizeof(user.card_list->top.rank));
	char *bookCard = malloc(sizeof(user.card_list->top.rank));
	char play[2] = "Y";
	while (strcmp(play, "Y") == 0){
		shuffle();
		isUserTurn = 1;
		while (game_over(&user) == game_over(&computer)) {
			// deal cards if either player needs them
			if (user.hand_size == 0){
				deal_player_cards(&user);
			}
			if (computer.hand_size == 0){
				deal_player_cards(&computer);
			}
			// show player cards
			printHand(&user, p1format);
			printHand(&computer, p2format);
			// player turn
			if (isUserTurn == 1) {
				userInput = user_play(&user);
				// if computer has requested card
				if (search(&computer, userInput) == 1){
					printf("    -Player 2 has ");
					searchPrint(&computer, userInput);
					printf("    -Player 1 has ");
					searchPrint(&user, userInput);
					transfer_cards(&computer, &user, userInput);
					// if a book was formed
					bookCard = check_add_book(&user);
					if (strcmp(bookCard, "0") != 0){
						printf("    -Player 1 books %s\n", bookCard);
						strcat(bookCard, " ");
						strcat(user.book, bookCard);
					}
					printf("    -Player 1 gets another turn\n");
				}
				// if computer does NOT have requested card
				else {
					printf("    -Player 2 has no %s's\n", userInput);
					add_card(&user, next_card());
					printf("    -Go Fish, Player 1 draws %s%s\n", user.card_list->top.rank, user.card_list->top.suit);
					// if card drawn was card requested
					if (strcmp(user.card_list->top.rank, userInput) == 0){
						printf("    -Player 1 drew their requested rank: %s\n", userInput);
						// if a book was formed
						bookCard = check_add_book(&user);
						if (strcmp(bookCard, "0") != 0){
							printf("    -Player 1 books %s\n", bookCard);
							strcat(bookCard, " ");
							strcat(user.book, bookCard);
						}
						printf("    -Player 1 gets another turn\n");
					}
					// if card draw was random
					else {
						// if book was formed
						bookCard = check_add_book(&user);
						if (strcmp(bookCard, "0") != 0){
							printf("    -Player 1 books %s\n", bookCard);
							strcat(bookCard, " ");
							strcat(user.book, bookCard);
						}
						printf("    -Player 2's turn\n");
						isUserTurn = 0;
					} // end card drawn was random
				} // end computer does NOT have requested rank
			} // end user turn
			// computer turn
			else {
				userInput = computer_play(&computer);
				// if user has requested rank
				if (search(&user, userInput) == 1){
					printf("    -Player 1 has ");
					searchPrint(&user, userInput);
					printf("    -Player 2 has ");
					searchPrint(&computer, userInput);
					transfer_cards(&user, &computer, userInput);
					// if a book was formed
					bookCard = check_add_book(&computer);
					if (strcmp(bookCard, "0") != 0){
						printf("    -Player 2 books %s\n", bookCard);
						strcat(bookCard, " ");
						strcat(computer.book, bookCard);
					}
					printf("    -Player 2 gets another turn\n");
				}
				// if user does NOT have requested card
				else {
					printf("    -Player 1 has no %s's\n", userInput);
					add_card(&computer, next_card());
					printf("    -Go Fish, Player 2 draws a card\n");
					// if card drawn was card requested
					if (strcmp(computer.card_list->top.rank, userInput) == 0){
						printf("    -Player 2 drew their requested rank: %s\n", userInput);
						// if a book was formed
						bookCard = check_add_book(&computer);
						if (strcmp(bookCard, "0") != 0){
							printf("    -Player 2 books %s\n", bookCard);
							strcat(bookCard, " ");
							strcat(computer.book, bookCard);
						}
						printf("    -Player 2 gets another turn\n");
					}
					// if card drawn was random
					else{
						// if book was formed
						bookCard = check_add_book(&computer);
						if (strcmp(bookCard, "0") != 0){
							printf("    -Player 2 books %s\n", bookCard);
							strcat(bookCard, " ");
							strcat(computer.book, bookCard);
						}
						printf("    -Player 1's turn\n");
						isUserTurn = 1;
					} // end card drawn was random
				} // end user does NOT have requested rank
			} // end computers turn
			printf("\n");
		} // end while game is not over
		// show player cards
		printHand(&user, p1format);
		printHand(&computer, p2format);
		if (game_over(&user) == 1){
			printf("Player 1 wins! %lu-%lu\n", (strlen(user.book))/2,(strlen(computer.book))/2);
		} else {
			printf("Player 2 wins! %lu-%lu\n", (strlen(computer.book))/2,(strlen(user.book))/2);
		}
		//play = "X";
		strcpy(play, "X");
		while ((strcmp(play, "Y") != 0) && (strcmp(play, "N") != 0)){
			printf("Do you want to play again [Y/N]: ");
			scanf("%s", play);
		}
		reset_player(&user);
		reset_player(&computer);
	} // end play again loop
	printf("Exiting\n");
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
