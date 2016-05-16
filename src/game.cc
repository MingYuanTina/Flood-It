#include <iostream>
#include "game.h"
#include "cell.h"
#include "textdisplay.h"
#include "PRNG.h"
using namespace std;

extern PRNG prng;

/*********** Construtor ***********
     Purpose: Initialize fields in the cell

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
Game::Game(int size, int moves): gridSize(size){
	this->turns = moves;	// initialize turns as input
	this->display = new TextDisplay(this->gridSize); // create objec test display
	this->grid = new Cell*[this->gridSize]; // create row of the grid
	// create each columne of the grid
	for (int i = 0; i < this->gridSize; i++){
		grid[i] = new Cell[this->gridSize];
	}

	// Go through each cells in the grid
	// 1. set coodinates, including row and columne to each cell
	// 2. set cells to textDisplay
	// 3. generate random number and call notify to assign to cell grid
	for (int row = 0; row < this->gridSize; row++){
		for (int col = 0; col < this->gridSize; col++){
			grid[row][col].setCoords(row, col); // 1
			grid[row][col].Cell::addDisplay(this->display); // 2
			grid[row][col].notify(prng(4)); // 3
		}
	}


	// Go through each cell and check the grid to add neighbours
	// 1. If top left corner, add cells below and right as neighbours
	// 2. If top right corner, add cells below and left as neighbours
	// 3. If bottom left corner, add cells above and right as neighbours
	// 4. If bottom right corner, add cells above and left as neighbours
	// 5. If top row, add cells left, right and below as neighbours
	// 6. If left column, add cells above, below and right as neighbours
	// 7. If bottom row, add cells below, left and right as neighbours
	// 8. If right columne, add cells above, below and left as neighbours
	// 9. If center cells, add cells above, below, left and right as neighbours 
	for (int row = 0; row < this->gridSize; row++){
		for (int col = 0; col < this->gridSize; col++){
			// Condition 1.  top left corner
			if (row == 0 && col == 0){
				grid[row][col].addNeighbour(&grid[row+1][col]);
				grid[row][col].addNeighbour(&grid[row][col+1]);

			// Condition 2. top right corner
			} else if (row == 0 && col == this->gridSize - 1){
				grid[row][col].addNeighbour(&grid[row][col-1]);
				grid[row][col].addNeighbour(&grid[row+1][col]);

			// Condition 3. bottom left corner
			} else if (row == this->gridSize - 1 && col == 0){
				grid[row][col].addNeighbour(&grid[row-1][col]);
				grid[row][col].addNeighbour(&grid[row][col+1]);

			// Condition 4. bottom right corner
			} else if (row == this->gridSize -1 && col == this->gridSize -1){
				grid[row][col].addNeighbour(&grid[row-1][col]);
				grid[row][col].addNeighbour(&grid[row][col-1]);

			// Condition 5. top row
			} else if (row == 0){
				grid[row][col].addNeighbour(&grid[row+1][col]);
				grid[row][col].addNeighbour(&grid[row][col+1]);
				grid[row][col].addNeighbour(&grid[row][col-1]);

			// Condition 6. left columne
			} else if (col == 0){
				grid[row][col].addNeighbour(&grid[row+1][col]);
				grid[row][col].addNeighbour(&grid[row-1][col]);
				grid[row][col].addNeighbour(&grid[row][col+1]);

			// Condition 7. bottom row
			} else if (row == this->gridSize - 1){
				grid[row][col].addNeighbour(&grid[row-1][col]);
				grid[row][col].addNeighbour(&grid[row][col+1]);
				grid[row][col].addNeighbour(&grid[row][col-1]);

			// Condition 8 right columne
			} else if (col == this->gridSize - 1){
				grid[row][col].addNeighbour(&grid[row][col-1]);
				grid[row][col].addNeighbour(&grid[row+1][col]);
				grid[row][col].addNeighbour(&grid[row-1][col]);

			// Condition 9 center cells
			} else {
				grid[row][col].addNeighbour(&grid[row][col+1]);
				grid[row][col].addNeighbour(&grid[row][col-1]);
				grid[row][col].addNeighbour(&grid[row+1][col]);
				grid[row][col].addNeighbour(&grid[row-1][col]);
			} // end if
		} // end for
	} // end for
}

/*********** Construtor ***********
     Purpose: Initialize fields in the cell

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
Game::~Game(){
	// Delete each row of grid
	for (int i = 0; i < this->gridSize; i++){
		delete [] grid[i];
	} // end for
	delete [] this->grid; // delete the grid

	delete this->display; // delete textdisplay
}


/*********** Construtor ***********
     Purpose: Initialize fields in the cell

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
int Game::getTurns(){
	return this->turns; // return number of moves left
} 


/*********** Construtor ***********
     Purpose: Initialize fields in the cell

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
bool Game::isWon(){
	return this->display->filled(); // check if user wins
}

/*********** Construtor ***********
     Purpose: Initialize fields in the cell

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
void Game::change(int state){
	grid[0][0].notify(state + 5); // call cell notify with state add 5
	this->turns--;				  // decrement number of moves by 1
}

/*********** Construtor ***********
     Purpose: Initialize fields in the cell

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
void Game::print(){
	this->display->print(); 	// call print to print grid
}

