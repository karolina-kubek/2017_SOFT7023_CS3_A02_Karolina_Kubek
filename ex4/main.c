
//------------------------------------
//	Define 
//------------------------------------
#define _CRT_SECURE_NO_WARNINGS

//------------------------------------
//	Include Libraries 
//------------------------------------
#include <time.h>
#include <string.h>
#include "game.h"

//------------------------------------
//	FUNCTION main 
//------------------------------------
int main(int argc, char* argv[]) {
	//1. We set the seed for generating random numbers (in case the "Computer" acts as one of the players)
	srand((unsigned int) time(NULL));

	//2. We parse the input arguments to the program
	//2.1. The first argument is the name of the first player
	char* p1 = (char*)malloc(strlen("Kala") + 1 * sizeof(char));
	strcpy(p1, "Kala");

	//2.2. The second argument is the name of the second player
	char* p2 = (char*)malloc(strlen("Tony") + 1 * sizeof(char));
	strcpy(p2, "Tony");

	//3. We call to the main function of the game
	play_game(p1, p2);

	//4. We finish the application returning 0
	return 0;
}
