#include <iostream>
#include <sstream>
#include "textdisplay.h"
#include "cell.h"

using namespace std;

/*********** TestDisplay ***********
     Purpose: Initialize TestDipslay

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
TextDisplay::TextDisplay(int n): gridSize(n) {
	this->theDisplay = new char*[this->gridSize]; // Create char array
	// Create columne for each row 
	for (unsigned int i = 0; i < this->gridSize; i++){	
		theDisplay[i] = new char[this->gridSize];
	} // end for

	// Assign each cell char by '0'
	for (unsigned int i = 0; i < this->gridSize; i++){
		for (unsigned int j = 0; j < this->gridSize; j++) {
			theDisplay[i][j] = '0';
		} // end for
	} // end for

	// Assign each colour member to zero
	for (unsigned int i = 0; i < 5; i++) {
		colours[i] = 0;
	} // end for
}

/*********** ~TestDisplay ***********
     Purpose: Destructor to delete two dimensional grid

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
TextDisplay::~TextDisplay(){
	// Delete each columne of text display
	for (unsigned int i = 0; i < this->gridSize; i++){
		delete [] theDisplay[i];
	}
	delete [] theDisplay; // delete rows of display
}

/*********** notify ***********
     Purpose: notify based on input and determine 
     	and char value for each cell

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
void TextDisplay::notify(int r, int c, char ch){
	if ((ch - '0') > 4) {  			// when initializing the grid
		theDisplay[r][c] = ch - 5;  // need to -5 since it is added to distinsh between calling when initialzing and when 
									// during playing game.
		unsigned int i = ch - '0' - 5;
		colours[i] += 1;  			// update the total number of colour.
	} else {
		char prve = theDisplay[r][c];  // store current colour of the cell in this location.
		unsigned int i = prve - '0';   // convert to int (colour index)
		colours[i] -= 1;  			   // decrement 1 since it will be overwritten.
		theDisplay[r][c] = ch ;  	   // update new colour
		unsigned int current = ch - '0';  
		colours[current] += 1;         // update the number of new colour in the grid
	} // end if
}

/*********** filled ***********
     Purpose: check colors if elemente 
     	have the same dimension size as grid size

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
bool TextDisplay::filled(){
	unsigned int total = gridSize*gridSize; // assign number of cells to total
	// Go through each colors 
	// 1. If any color have the same number of grid, user win
	// 2. Otherwise, user haven't win yet
	for (int i = 0; i < 5; i++) {
		// Step 2: check if color counter same with total
		if (colours[i] == total) {	
			return true; // return true
		} // end if
	} // end for
	return false; // return false
}

/*********** print ***********
     Purpose: print each cell that being assigned

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
void TextDisplay::print(){
	// Go through each row of grid
	// Go through each columne of the grid
	for (unsigned int row = 0; row < this->gridSize; row++){
		for (unsigned int col = 0; col < this->gridSize; col++){
			cout << theDisplay[row][col]; // print out value of char
		}
		cout << endl; // new line after each row
	}
}

