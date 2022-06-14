#include "Sudoku.h"
#include "ofApp.h"
#include "ofxGui.h"

void Sudoku::printMatrix() {

	/* prints matrix[i][j] 
	
	function is called in ofApp::setup() 
	to show empty matrix and where random 
	clues end up
	
	matrix[i][j] is also set to print after
	every input value from the user */

	for (int i = 0; i < ROWS_MAX; i++) {
		cout << "\n";
		for (int j = 0; j < COLS_MAX; j++) {
			cout << " " << matrix[i][j];
		}
	}

	cout << "\n";
}

bool Sudoku::checkWin()
{
	/* when the up-arrow key is pressed, this
	function compares matrix[i][j] at that 
	moment to the solution that was determined
	when the program was run and keeps count of 
	every value that is similar */

	int count = 0;
	for (int i = 0; i < ROWS_MAX; i++)
	{
		for (int j = 0; j < COLS_MAX; j++)
		{
			if (matrix[i][j] == solution1[i][j])
			{
				count++;
			}
			else if (matrix[i][j] == solution2[i][j])
			{
				count++;
			}
			else if (matrix[i][j] == solution3[i][j])
			{
				count++;
			}
			else if (matrix[i][j] == solution4[i][j])
			{
				count++;
			}
		}
	}
	
	/* when the function is done checking 
	similarities, the number of identical 
	values are printed. if count equals the 
	max number of identical values, the 
	prompt for a correct solution will print. 
	the prompt for a incorrect solution will 
	print if count equals any value other 
	than 81 */

	cout << "\nCorrect Guesses: " << count << endl;
	if (count == 81)
	{
		cout << "\nCongrats -- You've\nsolved the puzzle !!";
		return(true);
	}
	else
	{
		cout << "\nOpe, you're missing\nsome values. You\nstill need " + to_string(81-count) + " values\nto get the correct\nsolution";
		return(false);
	}
}

