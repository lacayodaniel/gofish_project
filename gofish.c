#include <stdio.h>
#include "deck.h"

int main(int args, char* argv[]) 
{
	struct player user = {NULL, NULL, 0};
	struct player computer = {NULL, NULL, 0};
	int b = shuffle();
	printf("deck 0 %s\n", deck_instance.list);
	printf("%zu\n", deck_size());
	int a = deal_player_cards(&user);
	return 0;
}


