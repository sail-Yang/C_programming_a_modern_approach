/*Deals a random hand of cards*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 13

int main(void){
	bool in_hand[NUM_SUITS][NUM_RANKS] = {false};
	int num_cards, rank, suit;
	char *rank_code[] = {"2","3","4","5","6","7","8","9","10","J of ","Q of ","K of ","Ace of "};
	char *suit_code[] = {"clubs","spades","diamonds","hearts"};
	
	srand((unsigned) time(NULL));
	
	printf("Enter number of cards in hand:");
	scanf("%d",&num_cards);
	
	printf("Your hands");
	while (num_cards > 0){
		suit = rand()% NUM_SUITS;
		rank = rand()% NUM_RANKS;
		if (!in_hand[suit][rank]){
			in_hand[suit][rank] = true;
			num_cards--;
			printf("%s%s\n ",rank_code[rank],suit_code[suit]);
		}
	}
	printf("\n");
	
	return 0;
}
