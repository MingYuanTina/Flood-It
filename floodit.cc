// CS 246 Assignment 2 Quesetion 4 1b
// Name : Tina Li
// Student ID: 20571774
// Description: The program imitates the game floodit 
// 				, which allows users to insert color each time 
// 				and update the grid until all the color in the grid same

#include <iostream>
#include <string>
#include <cstdlib>
#include "cell.h"
#include "game.h"
#include "textdisplay.h"
#include "PRNG.h"
#include <unistd.h>
using namespace std;

PRNG prng;

int main(int argc, char * argv[]){
	// Declare variables
	string cmd_size = "-size", cmd_moves = "-moves", cmd_val = "-seed";
	int size = 10, moves = 20, seed = 0;	// set default values
	int index = 1;							// set counter index to 1
	uint32_t temp = getpid();				// set random numbers

	/* Chec Arguments
		1. Size argument requires following condition
			a. prompt is -size
			b. size is number greater or equal to 2
			c. both prompt and size are given
		2. Moves arugments requires following conditions
			a. prompt is -moves
			b. moves is number greater or equal to 1
			c. both prompt and moves are given
		3. Seed argument requires following condition
			a. prompt is -val
			b. val is number greater than 0
			c. both prompt and val are given
		4. And input not meet above conditions is error exception */
	while (index < argc){
		if ((argv[index] == cmd_size) &&
			(index < argc - 1) &&
			(atoi(argv[index+1]) >= 2)){
			size = atoi(argv[index+1]);
			//cout << "size argument:" << size << endl;
		} else if ((argv[index] == cmd_moves) &&
			(index < argc - 1) && 
			(atoi(argv[index+1]) >= 1)) {
			moves = atoi(argv[index+1]);
			//cout << "move argument:" << moves << endl;
		} else if ((argv[index] == cmd_val) &&
			(index < argc - 1) &&
			(atoi(argv[index+1]) > 0)){
			seed = atoi(argv[index+1]);
			//cout << "val argument:" << val << endl;
		} else {
			cerr << "Usage: ./floodit-sample [ -size N (width and height of game ) >= 2) ] |" << 
			" [ -moves M (number of moves until game is over) >= 1) ] " <<
			"| [ -seed S (seed for random-number generator (1..INT_MAX)) ]" << endl;
			exit (1);
		}
		index += 2;
	}

	// Generate the random number
	if (seed > 0) {
		prng.seed((uint32_t)seed);
	} else {
		prng.seed(temp);
	}
	
	Game *game = new Game(size, moves);	//make a new game
	game->print();						// initialize new grid
	bool notFail = true;				// checker to track if print number of moves
	while (true){
		int turn = game->getTurns();	// assign number of moves left
		// If checker is true, the print out number of moves
		if (notFail){
			// If moves left not 1, print out x moves left
			// Otherwise, print out x move left
			if (turn != 1) {
				cout << turn << " moves left" << endl;
			} else {
				cout << turn << " move left" << endl;
			} // end if
		} // end if

		// Check if user wins the game.
		// If yes, print out prompt and break to end the game
		if (game->isWon()){
			cout << "Won" << endl; // print out prompt
			break;
		} // end if

		// Check if user loss the game
		// if yes, print out prompt and break to end the game
		if (game->getTurns() == 0){
			cout << "Lost" << endl; // print out prompt
			break;
		} // end if

		string input;  // string read in by program
		int number;    // number (color) converted from input
		cin >> input;  // read in user input
		stringstream ss(input); // stringstream to read input
		ss >> number;  // convert string to number

		// Three condition to check user input
		// 1. If input is is not a number, invalid move
		// 2. If number if not within 0 to 4, invalid move
		// 3 Otherwise, valid moves and changes the grid
		if (ss.fail()){
			// If end by user, break the game
			if (ss.eof()) {
				break;
			} else {
				cerr << "Invalid move" << endl; // print out prompt
				ss.clear();
				ss.ignore();
			}
			notFail = false;

		// Condition 2: invalid moves
		} else if ((number < 0) || (number > 4)){
			cerr << "Invalid move" << endl; // print out prompt
			notFail = false; // checker 

		// Condition 3: valid moves
		} else {
			notFail = true;
			game->change(number); // update the grid by user input
			game->print();		  // print out grid 
		}
	}

	delete game; // delete game object
	return 0; 	// return 0
}
