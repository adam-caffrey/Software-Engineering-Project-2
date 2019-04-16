/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <string.h>


/*
 * This function creates the board for the first time
 *
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){

    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4)
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;
        }
    }
}


 /*
 * This function creates players for the first time
 *
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){
	int i;
	int limit=6, count=0, colour;
	char *colours[6] = {"RED", "BLUE", "GREEN", "YELLOW", "PINK", "ORANGE"};
  int array[6];


	for(i=0; i<6; i++){
	    i<1?printf("\nPlease enter the name of the player\n") : printf("\nPlease enter the name of the next player\n");
		printf("Name: ");
		fgets(players[i].name,10,stdin);
		if(players[i].name[0] =='\n' && i<2)
		{
			printf("\n\tThere are too few players to start the game\n");
			i--;
		}
		else if(players[i].name[0] =='\n')
			break;
		else{
		players[i].name[strlen(players[i].name) - 1] = '\0'; //removes \n from the end of the players name due to fgets and replaces it with \0
		count++; //counts the players
		}
	}

	printf("\n\t1) RED  2) BLUE  3) GREEN  4) YELLOW  5) PINK  6) ORANGE\n\n");
	for(int i=0; i<count; i++)
	{
		printf("%s, please select your colour: ", players[i].name);
		scanf("%d", &colour);
		colour--;

		if (array[colour] != -1 && colour<6)
		{
			printf("\tYour colour is %s\n\n", colours[colour]);
			players[i].col = colour;
			players[i].token = colour;
			array[colour] = -1;
		}
		else
		{
			printf("\n\tThis colour is already taken\n\tPlease choose again\n\n");
			i--;
		}
	}


	return count;
    }
