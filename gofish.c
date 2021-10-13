#include <stdio.h>
#include "deck.h"

int main(int args, char* argv[]) 
{
	fprintf(stdout, "Put your code here.\n");
	fprintf(stdout, "called shuffled returned : %d\n", shuffle());
	
	printf("deck 0 %s\n", deck_instance.list);
	printf("%zu\n", deck_size());
	struct card* nextcard = next_card();
	return 0;
}


