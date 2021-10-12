
#include "deck.h"

int shuffle(){
	char* SUITS[5] = {"H", "C", "S", "D"};
	char* RANKS[14] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
	struct card templist[52];
	int i,j,n=0;
	
	for(i=0;i<4;i++){
		for(j=0;j<13;j++){
			struct card *anon_card = {*SUITS[i], *RANKS[j]};
			templist[n] = *anon_card;
			n++;
		}
	}
	n--;
	struct deck deck_instance = {*templist, n};
	
	return 0;
	
}
