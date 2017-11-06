
//------------------------------------
//	Include Libraries 
//------------------------------------
#include "game.h"


//------------------------------------
//	01. FUNCTION create_new_game
//------------------------------------
game* create_new_game(char* p1, char* p2){
	//1. We create the variable for hosting the game
	game* g = (game*)malloc(1 * sizeof(game));  

	//2. We use the names passed as arguments 
	(*g).p1 = (char*)malloc((strlen(p1) + 1) * sizeof(char));
	strcpy((*g).p1, p1);

	(*g).p2 = (char*)malloc((strlen(p1) + 1) * sizeof(char));
	strcpy((*g).p2, p2);

	//3. We set the mode to the one passed by parameter
	int mode = 0;
	if (strcmp(p1, "Computer") == 0)
		mode = mode + 2;
	if (strcmp(p2, "Computer") == 0)
		mode = mode + 1;
	(*g).mode = mode;

	//4. We set the status to be 1; i.e., player1 moves first
	(*g).status = 1;

	//5. We initialise the board to contain all positions empty
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
			(*g).board[i][j] = ' ';

	//6. We return the game
	return g;
}

//------------------------------------
//	02. FUNCTION display_board 
//------------------------------------
void display_board(game* g){
	printf("------------------\n   GAME STATUS   \n------------------\n\n");
	for (int j = 0; j < COLUMNS; j++) {
		printf("| %d ", j + 1);
	}
	printf("|\n");
	for (int j = 0; j < COLUMNS; j++) {
		printf("|---");
	}
	printf("|\n");
	for (int i = ROWS - 1; i >= 0; i--) {
		for (int j = 0; j < COLUMNS; j++) {
			switch ((*g).board[i][j]) {
			case ' ':
				printf("|   ");
				break;
			case 'X':
				printf("| X ");
				break;
			case 'O':
				printf("| O ");
				break;
			}
			
		}
		printf("|\n");
		for (int j = 0; j < COLUMNS; j++) {
			printf("|---");
		}
		printf("|\n");
	}
	printf("\n");
}

//------------------------------------
//	03. FUNCTION display_game_status 
//------------------------------------
void display_game_status(game* g) {
	display_board(g);
	printf("Player ");
	if ((*g).status == 1) {
		printf("%s", (*g).p1);
	}
	else {
		printf("%s", (*g).p2);
	}
	printf(" moves next\n");
}

//--------------------------------------------------
// 04. FUNCTION my_getchar
//--------------------------------------------------
char my_get_char() {
	//1. We create the variable for hosting the char
	char my_char = ' ';

	//2. We create an extra variable to consume any other characters entered until a return is pressed
	bool line_consumed = False;
	char dummy_char = ' ';

	//3. We consume the first char entered, i.e., the one we are interested at
	my_char = getchar();

	//4. While still there are remaining characters
	while (line_consumed == False) {
		//4.1. We consume the next character
		dummy_char = getchar();

		//4.2. If the new character is the end of line one, we can ensure we have consumed the entire line.
		if (dummy_char == '\n')
			line_consumed = True;
	}

	//5. We return the first character entered by the user, i.e., the one we are interested at
	return my_char;
}

//------------------------------------
//	05. FUNCTION ask_for_column 
//------------------------------------
int ask_for_column(game* g) {
	int col = 0;
	while (col < 1 || col > COLUMNS) {
		printf("Enter a column from 1 to %d: \n", COLUMNS);
		scanf("%d", &col);
		printf("\n");
	}
	return col;
}

//------------------------------------
//	06. FUNCTION user_movement 
//------------------------------------
int user_movement(game* g) {
	return 	ask_for_column(g);
}

//------------------------------------
//	07. FUNCTION computer_movement 
//------------------------------------
int computer_movement(game* g) {
	return gen_num(1, 7);
}

//------------------------------------
//	07.1 EXTRA FUNCTION gen_num 
//------------------------------------
int gen_num(int lb, int ub) {
	//1. We create the output variable with an initial value.
	int res = 0;

	//2. We assign num to a random value in the desired range
	res = (rand() % (ub - lb)) + lb;

	//3. We return the output variable
	return res;
}
//------------------------------------
//	08. FUNCTION new_movement 
//------------------------------------
void new_movement(game* g) {
	int col;
	bool isColumnFull = True;
	while (isColumnFull) {
		isColumnFull = False;
		if ((*g).mode == 0 || ((*g).mode == 2 && (*g).status == 2) || ((*g).mode == 1 && (*g).status == 1)) {
			col = user_movement(g) - 1;
		}
		else {
			col = computer_movement(g) - 1;
		}
		// printf("Column: %d", col);

		for (int i = 0; i < ROWS; i++) {
			if ((*g).board[i][col] == ' ') {
				if ((*g).status == 1) {
					(*g).board[i][col] = 'X';
					break;
				}
				else {
					(*g).board[i][col] = 'O';
					break;
				}
			}
			else if (i == ROWS - 1) {
				printf("This column is full! Try another column!\n");
				isColumnFull = True;
			}
		}
	}
}

//------------------------------------
//	09. FUNCTION winning_row 
//------------------------------------
bool winning_row(game* g, int row, int ply) {
	int strike = 0;
	char player_character = (ply == 1) ? 'X' : 'O';
	for (int j = 0; j < COLUMNS; j++) {
			
		if ((*g).board[row][j] == player_character) {
			strike = strike + 1;
			if (strike == CONNECT) {
				return True;
			}
		}
		else {
			strike = 0;
		}
	}
	return False;
}

//------------------------------------
//	10. FUNCTION winning_column 
//------------------------------------
bool winning_column(game* g, int column, int ply) {
	int strike = 0;
	char player_character = ( ply == 1 ) ? 'X' : 'O';
	for (int i = 0; i < ROWS; i++) {
		if ((*g).board[i][column] == player_character) {
			strike = strike + 1;
			if (strike == CONNECT) {
				return True;
			}
		}
		else {
			strike = 0;
		}
	}
	return False;
}

//------------------------------------
//	11. FUNCTION winning_diagonal 
//------------------------------------
bool winning_diagonal(game* g, int diagonal, int ply, bool left) {
	int strike = 0;
	int i;
	char player_character = ( ply == 1 ) ? 'X': 'O';
	if (left) {
		for (int k = 0; k < COLUMNS; k++) {
			i = diagonal;
			for (int j = k; j < COLUMNS; j++) {
				if (i < ROWS) {
					if ((*g).board[i][j] == player_character) {
						strike = strike + 1;
						if (strike == CONNECT) {
							return True;
						}
					}
					else {
						strike = 0;
					}

					i++;
				}
			}
		}
	}
	else {
		for (int k = COLUMNS - 1; k >= 0; k--) {
			i = diagonal;
			for (int j = k; j >= 0; j--) {
				if (i < ROWS) {
					if ((*g).board[i][j] == player_character) {
						strike = strike + 1;
						if (strike == CONNECT) {
							return True;
						}
					}
					else {
						strike = 0;
					}
					i++;
				}
			}
		}
	}
	return False;
}

//------------------------------------
//	12. FUNCTION winning_player 
//------------------------------------
bool winning_player(game* g, int ply) {
	bool winnerExists = False;

	for (int row = 0; row < ROWS; row++) {
		winnerExists = winning_row(g, row, ply);
		if (winnerExists) {
			display_board(g);
			if (ply == 1) {
				printf("Player %s has won!", (*g).p1);
			}
			else {
				printf("Player %s has won!", (*g).p2);
			}
			return winnerExists;
		}
	}

	for (int col = 0; col < COLUMNS; col++) {
		winnerExists = winning_column(g, col, ply);
		if (winnerExists) {
			display_board(g);
			if (ply == 1) {
				printf("Player %s has won!", (*g).p1);
			}
			else {
				printf("Player %s has won!", (*g).p2);
			}
			return winnerExists;
		}
	}

	
	for (int row = 0; row < ROWS; row++) {
		winnerExists = winning_diagonal(g, row, ply, True);
		if (winnerExists) {
			display_board(g);
			if (ply == 1) {
				printf("Player %s has won!", (*g).p1);
			}
			else {
				printf("Player %s has won!", (*g).p2);
			}
			return winnerExists;
		}
		winnerExists = winning_diagonal(g, row, ply, False);
		if (winnerExists) {
			display_board(g);
			if (ply == 1) {
				printf("Player %s has won!", (*g).p1);
			}
			else {
				printf("Player %s has won!", (*g).p2);
			}
			return winnerExists;
		}
	}
	return winnerExists;
}

//------------------------------------
//	13. FUNCTION update_status 
//------------------------------------
void update_status(game* g) {
	if ((*g).status == 1) {
		(*g).status = 2;
	}
	else {
		(*g).status = 1;
	}
}

//------------------------------------
//	14. FUNCTION play_game 
//------------------------------------
void play_game(char* p1, char* p2){
	game* g = create_new_game(p1, p2);
	bool longLiveTheWinner = False;
	while (!longLiveTheWinner) {
		display_game_status(g);
		new_movement(g);
		longLiveTheWinner = winning_player(g, (*g).status);
		update_status(g);
	}
	printf("?!");
}
