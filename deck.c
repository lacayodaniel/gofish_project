#include <time.h>
#include "deck.h"

int shuffle(){
	char* SUITS[5] = {"H", "C", "S", "D"};
	char* RANKS[14] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
	int i,j,n=0;
	
	for(i=0; i<4; i++){
		for(j=0; j<13; j++){
			struct card anon_card = {*SUITS[i], *RANKS[j]};
			deck_instance.list[n]=anon_card;
			n++;
		}
	}
	// different seed value each time
	srand ( time(NULL) );
	for(i=n-1; i>0; i--){
		// pick random index from 0 to i
		j = rand() % (i+1);
		swap(&deck_instance.list[i], &deck_instance.list[j]);
	}
	deck_instance.top_card = rand() % (52);
	printf(deck_instance.list);
	return 0;
	
}

void swap(struct card *a, struct card *b){
	struct card temp = *a;
	*a = *b;
	*b = temp;
}

size_t deck_size(){
	int a = 0;
	return sizeof(deck_instance.list)/3;
}
