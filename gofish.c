#include <stdio.h>
#include "deck.h"

int main(int args, char* argv[]) 
{
	fprintf(stdout, "Put your code here.\n");
	fprintf(stdout, "called shuffled returned : %d\n", shuffle());
	
	struct deck *copy_deck = &deck_instance;
	printf("deck 0 %s\n", copy_deck->list);
	printf("%zu\n", deck_size());
	
	return 0;
}


