#include <iostream>
#include <string>
#include "cell.h"
using namespace std;

TextDisplay *Cell::display = NULL;


/*********** Construtor ***********
     Purpose: Initialize fields in the cell

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
Cell::Cell(){
	/* Initialize each filed in cell to true
		1. inProgress to true
		2. state: current color 
		3. prevState: previous color
		4. numNeighbours: number of neighbour 
		5. initalize: starting status
		6. row: row number of the grid
		7. col: columne number of the grid */
	inProgress = true; 
	state = 0;
	prevState = 0;
	numNeighbours = 0;
	initialize = true;
	row = 0;
	col = 0;

	// Initialize every neighbour as NULL
	for (int i = 0; i < MAX_NEIGHBOURS; i++){
		neighbours[i] = NULL;
	}
}

/*********** getState ***********
     Purpose: return current state as of color

     Returns: Nothing

     Errors: Nothing

     Globals: none
************************************/
int Cell::getState(){
	return this->state;
}

/*********** setState ***********
     Purpose: Store current state as of previous
     		  every time new color set to current color

     Returns: void

     Errors: Nothing

     Globals: none
************************************/
void Cell::setState(int change){
	prevState = state;	// set current color to previous color
	state = change;		// set user input ot current color
}

/*********** setState ***********
     Purpose: Set up row and column for each cell

     Returns: void

     Errors: Nothing

     Globals: none
************************************/
void Cell::setCoords(int row, int col){
	this->row = row;	// assign row number as input
	this->col = col;	// assign column numeber as input
}

/*********** addNeighbour ***********
     Purpose: Add neighbours of the cells

     Returns: void

     Errors: Nothing

     Globals: none
************************************/
void Cell::addNeighbour(Cell* neighbour){
	this->neighbours[numNeighbours] = neighbour; // assign neightbour as input
	++numNeighbours;	// increment counter of neighbour by one
}

/*********** addDisplay ***********
     Purpose: Set up a pointer to text display 
     		  to update changes of colours of cells

     Returns: void

     Errors: Nothing

     Globals: none
************************************/
void Cell::addDisplay(TextDisplay* display){
	Cell::display = display;
}

/*********** notifyDisplay ***********
     Purpose: update new state of color 
     			on this cell to text display

     Returns: void

     Errors: Nothing

     Globals: none
************************************/
void Cell::notifyDisplay() {
	if (initialize == 1) {
		display->notify(row,col,(state+5)+'0');
		initialize = 0;
	} else {
		display->notify(row,col,state+'0');
	}
}

/*********** notifyDisplay ***********
     Purpose: update new state of color 
     			on this cell to text display

     Returns: void

     Errors: Nothing

     Globals: none
************************************/
void Cell::notifyNeighbours() {
	for (int i = 0; i < numNeighbours; i++) {
		neighbours[i]->notify(state,prevState);
	}
}

/*********** notify ***********
     Purpose: update cell color by user input

     Returns: void

     Errors: Nothing

     Globals: none
************************************/
void Cell::notify(int current, int previous){

	// This is the condition when initialize the grid. set initial colour of cell
	if (initialize == true) { 
		this->state = current;
		this->prevState = current;
		notifyDisplay(); // initialize the grid of TextDisplay

	// This is the condition while playing game
	} else if (previous == -1) {  
		if (current > 4) {  // change coulour of origin cell (row 0, col 0)
			setInProgress(); // reset inProgress member of all cells to true
			current -= 5;  // interpret the colour to the right form (5 was added when it is passed by game)
		}
		if (current != state) {  // when new colour and current colour of a cell is different
			inProgress = false;  // indicate this cell changed colour already
			setState(current);   // change colour
			notifyDisplay();     // update the new colour to TextDisplay
			notifyNeighbours();  // notify neighbours the change
		}

	// the colour of cell notified by a neigbour has the same colour with the cell notifying
	} else if (previous == state) {  
		if (inProgress == true) {   // if this cell didn't change its colour yet.
			notify(current); // change colour
		}
	}
}

/*********** notifyReset ***********
	Purpose: go through each neighbour 
		and call setInProgress to reset 
		status of inProgress if necessary

     Returns: void

     Errors: Nothing

     Globals: none
************************************/
void Cell::notifyReset() {
	// Go through each neighbour 
	for (int i = 0; i < numNeighbours; i++) {
		neighbours[i]->setInProgress(); // call to set inProgress
	} // end for
}

/*********** setInProgress ***********
	Purpose: check status of progress 
		and reset status of progress if necessary 

     Returns: void

     Errors: Nothing

     Globals: none
************************************/
void Cell::setInProgress() {
	// If inProgress set as false
	// reset inProgress to true and call notifyReset
	if (inProgress == false) {
		inProgress = true;
		notifyReset();
	}
}


