#include "deck.h"

int shuffle(){
	printf("shuffling cards...\n");
	char* SUITS[5] = {"H", "C", "S", "D"};
	char* RANKS[14] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
	int i,j,n=0;
	struct card anon_card;
	for(i=0; i<4; i++){
		for(j=0; j<13; j++){
			// = { *SUITS[i], *RANKS[j] };
			strcpy(anon_card.suit, SUITS[i]);
			strcpy(anon_card.rank, RANKS[j]);
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

int deal_player_cards(struct player* target){
	if (deck_size() >=7 ){
		for (int i=0; i<7; i++){
			int error = add_card(target, next_card());
			if (error == -1) { return -1; }
		}
	} else {
		for (int i=0; i<deck_size(); i++){
			int error = add_card(target, next_card());
			if (error == -1) { return -1; }
		}
	}
	return 0;
}

struct card* next_card(){
	struct card* temp = &deck_instance.list[deck_instance.top_card];
	deck_instance.top_card++;
	return temp;
}

size_t deck_size(){
	return 52 - deck_instance.top_card;
}
