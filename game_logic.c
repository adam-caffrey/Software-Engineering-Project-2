/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE || board[i][j].type == CLEARED)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    int limit = numPlayers*4, i, x;
	
	print_board(board);

	for (i=0; i<limit; i++)
	{
		i<numPlayers? printf("\n%s, please select position for your first token\n", players[i].name) : printf("\n%s, please select position for your next token\n", players[i%numPlayers].name);
		scanf("%d", &x);
		
		if(x>5){
			printf("\n\tThis is not a valid position\n\tPlease choose a different position");
			i--;
		}
		else if ((i<=5 && board[x][0].stack_count>0) || (i<=10 && board[x][0].stack_count>1) || (i<=15 && board[x][0].stack_count>2) || (i<=20 && board[x][0].stack_count>3) || (i<=25 && board[x][0].stack_count>4))
		{
			printf("\n\tThis stack level hasnt been filled\n\tPlease enter a different position\n");
			i--;
		}
		else if(board[x][0].stack_count>0 && board[x][0].stack->col == players[i%numPlayers].col)
		{
			printf("\n\tYou cannot stack your tokens on top of one another\n\tPlease choose a different position\n");
			i--;
		}
		else{
			
			token *curr = board[x][0].stack;
			board[x][0].stack = malloc(sizeof(token));
			board[x][0].stack->col = players[i%numPlayers].col;
			board[x][0].stack->next = curr;
			board[x][0].stack_count++;
			print_board(board);
			
		}
		if(i==limit-1)
		printf("\n\tAll tokens have been placed\n");	
	}
	return;
}


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    bool win = 0, repeat=0, release= 1;
	int choice, x, y, upOrDown;
	char tokens[6] = {'R', 'B', 'G', 'Y', 'P', 'O'};
	srand(time(0));
	int dice;
	
	for(int i =0; !win ;i++)
	{
		
		if(!repeat){
			dice = rand()%6;
		printf("\n%s, The dice has been rolled and the result is %d\nToken: %c\n", players[i%numPlayers].name, dice, tokens[players[i].token]);
			printf("\nWould you like to move a token up or down?\n1) yes\n2) no\n");
			scanf("%d", &choice);
			
		}
		
		if(choice==1)
		{
			
			printf("\nEnter the position of the token you would like to move\nRow: ");
			scanf("%d", &x);
			printf("Column: ");
			scanf("%d", &y);
			
			if(board[x][y].type == OBSTACLE)
					{
						int l, k;
						for(k=0; k<y; k++)
						{
							for(l=0; l<6; l++)
							{
								if(board[l][k].stack != NULL)
								{
									printf("\n\tThis token cannot be moved yet\n");
									break;
								}
								if(board[l][k].stack == NULL && l==5 && k==y-1 )
									board[x][y].type == CLEARED;
							}
							if(board[l][k].stack != NULL)
								break;
						}
					}
			if(board[x][y].stack==NULL || board[x][y].stack->col != players[i%numPlayers].col || board[x][y].type == OBSTACLE)
			{
				if(board[x][y].type != OBSTACLE)
				printf("\n\tThis is not a valid choice as it is not your token.\n\tPlease choose again\n");
				
				i--;
				repeat=1;
			}
			else{
				
				if(x==0)
					upOrDown=2;
				else if(x==5)
					upOrDown=1;
				else{
				printf("\n1) up\n2) down\n");
				scanf("%d", &upOrDown);
				}
				
				token* curr = board[x][y].stack;
				if(curr != NULL)
				{
					board[x][y].stack = curr->next;
					free(curr);
				}
				if(upOrDown == 1)
					x--;
				else if(upOrDown == 2)
					x++;
				
				curr = board[x][y].stack;
				board[x][y].stack = malloc(sizeof(token));
				board[x][y].stack->col = players[i%numPlayers].col;
				board[x][y].stack->next = curr;
			
				print_board(board);
				repeat = 0;
			}
		}
		
		if(!repeat)
		{
			for(int j=0; j<9; j++)
			{
				//condition to check whether there are any tokens in the row the dice landed on
				if(board[dice][j].stack != NULL && j!=8)
				{
					release =1;
					if(board[dice][j].type == OBSTACLE)
					{
						for(int k=0; k<9; k++)
							for(int l=0; l<6; l++)	
							{
								if(board[dice][k].stack != NULL)//checks if there are other tokens on row that can be moved
								{
									release=1;
									break;
								}
								else if(board[l][k].stack != NULL && k<j && l!=dice)//checks if there
									release=0;
							}
					}//end of if token is on an obstacle
					else
						break;
					
				}//end of if statement looking for a token
				else
					release=0;
				
			}//end of for loop		
				
				
				
				//if condition dictates whether the token can be released when in an obstacle
				//default is set to release the token
			if(release)
			{	
				while(release)
				{											
					printf("\nPlease select a token in row %d to be moved forward\n", dice);
					scanf("%d", &y);
					
					if(board[dice][y].stack!=NULL && y<9)
					{
						//check to see if there are any tokens behind the obstacle stuck token
						if(board[dice][y].type == OBSTACLE)
						{
							int k, l;
							for(k=0; k<y; k++)
							{
								for(l=0; l<6; l++)
								{
									if(board[l][k].stack != NULL)
									{
										printf("\n\tThis token cannot be moved yet\n");
										release=0;
										break;
									}
								}
								if(board[l][k].stack != NULL)
									break;
							}
						}
						else 
							break;
					}
					else
						printf("\n\tThere are no tokens here\n\tPlease enter a different position\n");
				}
				//places the the token in the next column to move forward
				//eg a push for a stack
				y++;
				token *curr = board[dice][y].stack;				
				board[dice][y].stack = malloc(sizeof(token));
				board[dice][y].stack->col = board[dice][y-1].stack->col ;
				board[dice][y].stack->next = curr;
					
				//releases the token that was moved forward from its previous position
				//eg a pop for a stack
				curr = board[dice][y-1].stack;
				if(curr != NULL){
					board[dice][y-1].stack = curr->next;
					free(curr);
				}
				
				print_board(board);
					
				//condition to win the game
				if(y==8)
					players[i].finishLine++;
					
			}
			
			else{
				printf("\n\tThere were no tokens to be moved\n");
				print_board(board);
			}
		}
		
		//condition for winning the game
		if(players[i].finishLine == 3)
		{
			printf("\n\t***Player %s has won!!!***\n\n\t\tGAME OVER", players[i].name);
			win = 1;
		}
		
	}
	
}



