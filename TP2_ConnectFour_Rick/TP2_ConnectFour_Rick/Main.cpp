#include <iostream>
#include <time.h>

#define ERROR -1

const int HEIGHT = 6;
const int WIDTH = 7;
char grid[HEIGHT][WIDTH];


bool CheckHorizontal(int a, int b);
bool CheckVertical(int a, int b);
bool CheckDiagonalOne(int a, int b);
bool CheckDiagonalTwo(int a, int b);

void DisplayGrid();
void AssignGrid();
void ScoreBoard(int xScore,int oScore);
int DropPiece(int i, char player);

bool CheckWin(int Y, int X);
void WinReturn(int totalPieces, int currentPlayer);

int ConnectFour();

 // main, includes ConnectFour()
void main()
{
	ConnectFour();
	return;
}

// Heart of the Algorithm
int ConnectFour()
{
	int temp;
	int temp2 = 0;
	char rematch;
	char gameMode;
	int totalPieces = 0;
	bool gameIsWon = false;
	char currentPlayer = 'X';
	int xScore = 0; // X Player score Variables
	int oScore = 0; // O Player score Variables


	do // Ask player game mode loop
	{
		std::cout << " You are about to begin a match of Connect 4! " << std::endl << std::endl << std::endl; 
		std::cout << " Would you like to play against an AI or a player?" << std::endl;
		std::cout << " AI = 1 " << std::endl;
		std::cout << " Player vs Player = 2 " << std::endl;
		std::cout << "Choice : " << std::endl;
		std::cin >> gameMode;
	} while (gameMode !='1' && gameMode != '2');
	do // rematch + game loop
	{
		srand(time(NULL)); // Random Seed Initilization for "Smart" AI :D

		AssignGrid(); 
		DisplayGrid(); 

		while (gameIsWon == false)   // game loop
		{		
			if (currentPlayer == 'X')
			{
				currentPlayer = 'O';
				std::cout << " Your turn  " << currentPlayer << " Player, please choose a column by inputing the corresponding letter!!! " << std::endl;
			}
			else
			{
				currentPlayer = 'X';
				std::cout << " Your turn  " << currentPlayer << " Player, please choose a column by inputing the corresponding letter!!! " << std::endl;
			}
			while (totalPieces != 42 || temp >= 6 && temp <= 0) 
			{
				char input;
				char inputCapital;
				int aI = rand() %6;

				if (gameMode == '1' && currentPlayer == 'X')
				{
					temp = aI;
				}
				else
				{
					std::cin >> input;
					std::cout << std::endl;
					temp = input - 'a';
				}
				if (temp <= 6 && temp >= 0)
				{
					break;
				}
				else
				{
					std::cout << "It might help if you actually type a letter from A to G, jeeeeez :P " << std::endl;
				}
			}
			if (totalPieces == 42)
			{
				break;
			}
			temp2 = DropPiece(temp, currentPlayer);
			if (temp2 == ERROR) // returned from DropPiece if the chosen value is at max capacity
			{
				std::cout << " The Vertical line is full dude, can't put it there. ";
			}
			else
			{
				gameIsWon = CheckWin(temp2, temp);
				totalPieces++;
				DisplayGrid();
			}
		}// shit,shit,shit bad Ricky, dont lose sight of this curly brace bruh.
		WinReturn(totalPieces, currentPlayer);
		if (currentPlayer == 'X')
		{
			xScore++;
		}
		else
		{
			oScore++;
		}
		ScoreBoard(xScore, oScore); // Call method to display the score
		std::cout << " Rematch? 'Y' or 'y' for yes, anything else is a no! :  " ;
		std::cin >> rematch;
		gameIsWon = false;
	} while (rematch == 'Y' || rematch == 'y');
	return 0;
}

// This method returns the score tally of both players
void ScoreBoard(int xScore, int oScore)
{
	std::cout << " X Player Score: " << xScore << std::endl;
	std::cout << " O Player Score: " << oScore << std::endl;
	if (xScore > oScore)
	{
		std::cout << " X Player is winning!!! Git Gud O Player! " << std::endl << std::endl;
	}
	else if (xScore < oScore)
	{
		std::cout << " O Player is Winning!!! Git Gud X Player! " << std::endl;
	}
	else
	{
		std::cout << " Game is a tie, Good Luck Boys! " << std::endl;
	}
}

// This method returns the win text or draw text
void WinReturn(int totalPieces, int currentPlayer) // This method returns the win text or draw text
{
	char c = currentPlayer;
	if (totalPieces == 42)
	{
		std::cout << " no more room, gg m8s " << std::endl;
		return;
	}
	if (currentPlayer == 'X')
	{
		std::cout << " Damn " << c << " player, you the real deal! " << std::endl;
	}
	else
	{
		std::cout << " Damn " << c << " player, you the real deal! " << std::endl;
	}
	return;
}

// This method simply displays the game board
void DisplayGrid()
{
	std::cout << "  __   __   __   __   __   __   __ " << std::endl;
	std::cout << " /a/  /b/  /c/  /d/  /e/  /f/  /g/  " << std::endl;
	std::cout << " ``   ``   ``   ``   ``   ``   ``  " << std::endl;
	std::cout << "  ^    ^    ^    ^    ^    ^    ^  " << std::endl;

	for (int i = 0; i < HEIGHT; i++) // loops 6 times.
	{
		std::cout << "===================================";
		std::cout << std::endl;		
		for (int j = 0; j < WIDTH; j++)
		{			
			std::cout << "| ";			
			std::cout << grid[i][j];
			if (j <= WIDTH - 1)
			{
				std::cout << " |";
			}			
		}		
		std::cout << std::endl;
		std::cout << "===================================" << std::endl;
	}
}   

// this is the method necessary to replace ' ' characters by 'X' or 'O'.
void AssignGrid() 
{
	std::cout << std::endl;
	for (int x = 0; x <= 5; x++)
	{
		for (int y = 0; y <= 6; y++)
		{
			grid[x][y] = ' ';
		}
	}
}

// This method is used to drop a piece into a column until a peice is intercepted by a piece already in place
int DropPiece(int i, char currentPlayer)
{
	if (i >= 0 && i <= 6)
	{
		if (grid[0][i] == ' ')  //see mon InitializeGrid
		{
			int p;
			for (p = 5; p >= 0; p--) // deiterate
			{
				if (grid[p][i] == ' ')
				{
					grid[p][i] = currentPlayer;
					return p;
				}
			}
		}
	}
	return ERROR;
}

// This method is used to verify the 4 latter verification methods
bool CheckWin(int a, int b)
{
	if (CheckVertical(a, b) == true
		|| CheckHorizontal(a, b) == true
		|| CheckDiagonalOne(a, b) == true
		|| CheckDiagonalTwo(a, b) == true)
		return true;
	else
		return false;
}

// This method verifies the Horizontal row for a series of 4 identical characters of either 'X' or 'O'
bool CheckHorizontal(int a, int b)
{
	int horizontal = 1;
	char player = grid[a][b];
	int x;

	for (x = b - 1; grid[a][x] == player && x >= 0; x--, horizontal++);
	for (x = b + 1; grid[a][x] == player && x <= 6; x++, horizontal++);
	if (horizontal >= 4)
	{
		return true;
	}
	return false;
}

// This method verifies the Vertical column for a series of 4 identical characters of either 'X' or 'O'
bool CheckVertical(int a, int b)
{
	int vertical = 1;
	char player = grid[a][b];
	int y;

	for (y = a + 1; grid[y][b] == player && y <= 5; y++, vertical++);
	for (y = a - 1; grid[y][b] == player && y >= 0; y--, vertical++);
	if (vertical >= 4)
	{
		return true;
	}
	return false;
}

// This method verifies the Diagonal ( \ ) for a series of 4 identical characters of either 'X' or 'O'
bool CheckDiagonalOne(int a, int b)
{
	int diagonal = 1;
	char player = grid[a][b];
	int y;
	int x;

	for (y = a - 1, x = b - 1; grid[y][x] == player && y >= 0 && x >= 0; diagonal++, y--, y--);
	for (y = a + 1, x = b + 1; grid[y][x] == player && y <= 5 && x <= 6; diagonal++, y++, x++);
	if (diagonal >= 4)
	{
		return true;
	}
	return false;
}

// This method verifies the Diagonal ( / ) for a series of 4 identical characters of either 'X' or 'O'
bool CheckDiagonalTwo(int a, int b)
{
	int diagonal = 1;
	char player = grid[a][b];
	int y;
	int x;

	for (y = a - 1, x = b + 1; grid[y][x] == player && y >= 0 && x <= 6; diagonal++, y--, x++);
	for (y = a + 1, x = b - 1; grid[y][x] == player && y <= 5 && x >= 0; diagonal++, y++, x--);
	if (diagonal >= 4)
	{
		return true;
	}
	return false;
}