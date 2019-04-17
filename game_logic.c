/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>

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
                if(board[i][j].type == OBSTACLE)
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
    //TO BE IMPLEMENTED
}
