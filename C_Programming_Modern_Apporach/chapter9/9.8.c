#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int roll_dice(void);
bool play_game(void);

int main(){
	bool result;
	char ch;
	int wins=0,loses=0;
	do{
		result = play_game();
		if(result){
			wins = wins +1;
		}else{
			loses = loses+1;
		}
		printf("\n\n");
		printf("Play again?\n");
		/*这里要注意，不这么写的话，第二次读的会是空格*/ 
		ch = getchar();
		getchar();
		if(ch == 'y'||ch == 'Y'){
			continue;
		}else{
			printf("Wins:%d  Losses:%d",wins,loses);
			return 0;
		}
	}while(1);
	return 0;
}

int roll_dice(void){
	int roll1,roll2,sum;
	srand((unsigned int)time(0));
	roll1 = rand()%6+1;
	roll2 = rand()%6+1;
	sum = roll1+roll2;
	return sum;
}

bool play_game(void){
	int roll,point;
	roll = roll_dice();
	printf("You rolled:%d\n",roll);
	if(roll==7 || roll == 11){
		printf("You win!\n");
		return true;
	}else if(roll == 2 || roll == 3||roll ==12){
		printf("You lose!\n");
		return false;
	}else {
		point = roll;
		printf("Your point is %d\n",point);
		for(;;){
			roll = roll_dice();
			printf("You rolled:%d\n",roll);
			if (roll == point){
				printf("You win!\n");
				return true;
			}else if (roll == 7){
				printf("You lose!\n");
				return false;
			}else{
				continue;
			}
		}
	}
}
