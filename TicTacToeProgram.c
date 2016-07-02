/*
Tic-Tac-Toe Game Program
Derek O'Brien
CIS 170 Section 01

This program will diplay tic tac toe board, allow users to pick location and 
display their mark in that location, and check and determine if their is winner
or cats game.
*/

#include <stdio.h>
#include <stdlib.h>
void displayBoard(char board[3][3]);
int selectLocation();
void setTurn(char, char board[][3], char, int);
int checkForWin(char board[][3], int, char);
char compMove(char board[][3]);

int main()
{
	char board[3][3] = { '1', '2', '3',
						'4', '5', '6',
						'7', '8', '9'};
 	char player, location;
	int i, versus = 0, turn = 1, check = 0;
 	
	
	displayBoard(board);
	printf("\nPlayer One is X \nPlayer Two is O");
	printf("\n\n");		 

	while(versus != 1 && versus != 2)  //User choose vs comp or player
	{
		printf("Press 1 to play computer");
		printf("\nPress 2 to play two player: ");
		scanf("%d", &versus);		
	}

	while(1)
	{
	    if (check == 1) //check return of 1 ends game if win or draw
	    {
			break;
		}
	    player = 'X';
	    location = selectLocation();
	    setTurn(location, board, player, versus);
	    system("cls");
		displayBoard(board);
		check =  checkForWin(board, turn++, player);
		
		if (check == 1)
	    {
			break;
		}
	    player = 'O';
	    if (versus == 1) //If versus computer, computer makes move.
	    	location = compMove(board);	
	    else
		   	location = selectLocation(); //two player game, second player makes move.
		setTurn(location, board, player, versus);
		system("cls");
		displayBoard(board);
		check =  checkForWin(board, turn++, player);
		}
	
	return 0;
}

void displayBoard(char board[3][3])
{
	int r, c;
	printf("   Tic Tac Toe\n");
	
	for (r=0; r<3; r++)
	{
		for (c=0; c<3; c++)
		{	
			printf("%c\t", board[r][c]);
		} 
		printf("\n");
	}
	//function that will display the actual game board
	//that is recieved as a 3x3 array argument from the calling function
}

int selectLocation()
{
	char location;
	printf("Enter where you would like to place your mark: ");
	scanf("\n%c", &location);

	return location;
	//function that will ask the user to enter the location for a
	//particular player (x or o) and return the location
}

void setTurn(char location, char board[][3], char player, int versus)
{
	//function that will set the x or the o in the proper position within a gameboard 

	int r, c;
	
	while (1)
	{
		int i = 1;
		for (r=0; r<3; r++)
		{
			for (c=0; c<3; c++)
			{	
				if (location == board[r][c])
				{ 
					board[r][c] = player; 
					r = 4;
					break;
				}i++;			
			}
		} 
		if (i > 9) //executes if a valid position was not selected
		{
			if (versus == 1) //computer picked invalid slot, call to pick new position
				location = compMove(board);
			else
			{
				printf("Please enter a valid location! : ");
				scanf("\n%c", &location);
			}
				continue;			
		}
	 	else
		 	break;	
	}	
}

int checkForWin(char board[][3], int turn, char player)
{
	//function that will determine if there is a winner or if it is a Cats game.
	int check = 0; //check value of 0 lets game proceed
	if (turn <= 9)
	{
		if (board[0][0] == board [0][1] && board[0][1] == board[0][2]		     //top row winner
			|| board[1][0] == board [1][1] && board[1][1] == board[1][2]		 //mid row winner	
			|| board[2][0] == board [2][1] && board[2][1] == board[2][2]         //bot row winner
			|| board[0][0] == board [1][0] && board[1][0] == board[2][0]		 //1st col winner
			|| board[0][1] == board [1][1] && board[1][1] == board[2][1]		 //2nd col winner	
			|| board[0][2] == board [1][2] && board[1][2] == board[2][2]		 //3rd col winner	
			|| board[0][0] == board [1][1] && board[1][1] == board[2][2]		 //diag \ winner	
			|| board[0][2] == board [1][1] && board[1][1] == board[2][0])		 //diag / winner
		{
			if (player == 'X')
				printf("Player One is the Winner!");
			else
				printf("Player Two is the Winner!");
			check = 1; //return value of check = 1 ends game
		}
		else if (turn == 9)	
		{
			printf("Cats!");
			check = 1; //return value of check = 1 ends game
		}
	}
	return check; 
}

char compMove(char board[][3]) //A.I. for computer decision to pick mark location (go for win, defend from loss, place mark)
{
	int num;
	char location, mark;
	int r, c;
	
	int count = 1;
	
	while (1)
	{
		if (count == 1) //first computer checks to go for the win
			mark = 'O';
		else if (count == 2) //if computer can't win with move it now checks to defend
			mark = 'X';
		else
			break;
	
	    if (((board[1][0] == mark && board [2][0] == mark) || 
			(board[0][1] == mark && board [0][2] == mark) ||
			(board[1][1] == mark && board [2][2] == mark )) && board[0][0] == '1') // check position 1
			{
				location = '1';
				break;
			}
	
		else if (((board[1][1] == mark && board [2][1] == mark) || 
				 (board[0][0] == mark && board [0][2] == mark)) && board[0][1] == '2') // check position 2	
			{
				location = '2';
				break;
			}
	
		else if (((board[1][2] == mark && board [2][2] == mark) || 
				 (board[0][0] == mark && board [0][1] == mark) ||
				 (board[1][1] == mark && board [2][0] == mark)) && board[0][2] == '3') // check position 3
			{
				location = '3';
				break;	
			}
	
		else if (((board[0][0] == mark && board [2][0] == mark) || 
				 (board[1][1] == mark && board [1][2] == mark)) && board[1][0] == '4') // check position 4
			{
				location = '4';
				break;
			}
		
		else if (((board[0][1] == mark && board [2][1] == mark) ||
				 (board[1][0] == mark && board [1][2] == mark) ||
				 (board[0][0] == mark && board [2][2] == mark) ||
				 (board[0][2] == mark && board [2][0] == mark)) && board[1][1] == '5') // check position 5
			{
				location = '5';
				break;
			}
	
		else if (((board[0][2] == mark && board [2][2] == mark) ||
			     (board[1][0] == mark && board [1][1] == mark)) && board[1][2] == '6') // check position 6
			{
				location = '6';
				break;
			}
	
	    else if (((board[0][0] == mark && board [1][0] == mark) || 
				 (board[2][1] == mark && board [2][2] == mark) ||
				 (board[1][1] == mark && board [0][2] == mark)) && board[2][0] == '7') // check position 7
			{
				location = '7';
				break;				
			}
	
		else if (((board[0][1] == mark && board [1][1] == mark) ||
				 (board[2][0] == mark && board [2][2] == mark)) && board[2][1] == '8') // check position 8
			{
				location = '8';
				break;
			}
	
		else if (((board[0][2] == mark && board [1][2] == mark) ||
			     (board[2][0] == mark && board [2][1] == mark) ||
				 (board[0][0] == mark && board [1][1] == mark)) && board[2][2] == '9') // check position 9
			{
				location = '9';
				break;
			}
		else
			{
				count += 1; //increments count to now have the computer check to defend
				continue;
			}
	}
	
	while (count == 3) //if computer can not win or lose from next move, the computer randomly selects position
	{ 	
		srand(time(0)); 
		num=rand() % (9 - 1 + 1) + 1;
		location = num + '0';
	    break; 	
	} 
	return location;
}
