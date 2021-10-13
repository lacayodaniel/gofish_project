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
	deck_instance.top_card = 0; // top card is the element position of the top card in the array
	return 0;
	
}

void swap(struct card *a, struct card *b){
	struct card temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Function: next_card
 * -------------------
 *  Return a pointer to the top card on the deck.
 *  Removes that card from the deck. 
 *
 *  returns: pointer to the top card on the deck.
 */
struct card* next_card( ){
	struct card* temp = &deck_instance.list[deck_instance.top_card];
	deck_instance.top_card++;
	return temp;


}



size_t deck_size(){
	int a = 0;
	return 52 - deck_instance.top_card;
}
