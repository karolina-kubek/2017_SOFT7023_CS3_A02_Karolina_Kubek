
//------------------------------------
//	Define 
//------------------------------------
#ifndef _GAME_
#define _GAME_

#define _CRT_SECURE_NO_WARNINGS

#define CONNECT 4
#define ROWS 6
#define COLUMNS 7

//------------------------------------
//	Include Libraries 
//------------------------------------
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------
//	Datatype game
//------------------------------------
struct _game {
	char* p1;
	char* p2;
	int mode;
	int status;
	char board[ROWS][COLUMNS];
};

typedef struct _game game;

//------------------------------------
//	Datatype bool
//------------------------------------
enum Boolean { False, True };
typedef enum Boolean bool;

//------------------------------------
//	01. FUNCTION create_new_game
//------------------------------------
game* create_new_game(char* p1, char* p2);

//------------------------------------
//	02. FUNCTION display_board 
//------------------------------------
void display_board(game* g);

//------------------------------------
//	03. FUNCTION display_game_status 
//------------------------------------
void display_game_status(game* g);

//--------------------------------------------------
// 04. FUNCTION my_getchar
//--------------------------------------------------
char my_get_char();

//------------------------------------
//	05. FUNCTION ask_for_column 
//------------------------------------
int ask_for_column(game* g);

//------------------------------------
//	06. FUNCTION user_movement 
//------------------------------------
int user_movement(game* g);

//------------------------------------
//	07. FUNCTION computer_movement 
//------------------------------------
int computer_movement(game* g);

//------------------------------------
//	07.1 EXTRA FUNCTION gen_num 
//------------------------------------
int gen_num(int lb, int ub);

//------------------------------------
//	08. FUNCTION new_movement 
//------------------------------------
void new_movement(game* g);

//------------------------------------
//	09. FUNCTION winning_row 
//------------------------------------
bool winning_row(game* g, int row, int ply);

//------------------------------------
//	10. FUNCTION winning_column 
//------------------------------------
bool winning_column(game* g, int column, int ply);

//------------------------------------
//	11. FUNCTION winning_diagonal 
//------------------------------------
bool winning_diagonal(game* g, int diagonal, int ply, bool left);

//------------------------------------
//	12. FUNCTION winning_player 
//------------------------------------
bool winning_player(game* g, int ply);

//------------------------------------
//	13. FUNCTION update_status 
//------------------------------------
void update_status(game* g);

//------------------------------------
//	14. FUNCTION play_game 
//------------------------------------
void play_game(char* p1, char* p2);

//------------------------------------
//	End of file 
//------------------------------------
#endif

