#pragma once

#include "ofMain.h"
#include "Sudoku.h"
#include "ofxGui.h"

#define ROWS_MAX 9
#define COLS_MAX 9
#define GRID_MAX 5000

class ofApp : public ofBaseApp {

	public:

		Sudoku Board; // allows for Sudoku functions to be called in ofApp class
		
		// member variables associated with the grid 
		int nx;
		int ny;
		int xmin = 0;
		int xmax = 800;
		int ymin = 0;
		int ymax = 800;
		int x_step = 100;
		int y_step = 100;
		ofRectangle grid[ROWS_MAX][COLS_MAX];

		// member variables associated with inputted values from user
		int filled = 0;
		int index_i[GRID_MAX];
		int index_j[GRID_MAX];
		ofImage* images = new ofImage[9];
		ofImage* filledImages = new ofImage[GRID_MAX];

		// member variables associated with default images
		int random = 0;
		int matX[GRID_MAX];
		int matY[GRID_MAX];
		ofImage* starterImages = new ofImage[GRID_MAX];

		// flag variables to determine when the user is 'allowed' to input values
		bool inputFlag = false;
		bool startFlag = true;
		
		bool solResult; // for Sudoku class check function

		// member variables and strings associated with the text on the screen
		string str = "";
		string title = "SUDOKU";
		string tip1 = "Fill in each square of the grid with any digit\n1 through 9 so that the sums of each individual\nrow, column, and 3x3 section within the 9x9 grid\nare equal to 45.";
		string tip2 = "The most important rule of Sudoku is to avoid \nrepeating a number within the same row, \ncolumn, and 3x3 grid. Doing so will result in an\nincorrect solution.";
		string start = "To choose a solution, press a number 1-4 on \nthe keyboard, then press the down-arrow key.";
		string play = "Click on a box and press a number 1 through\n9 to add it to the puzzle. When the puzzle is filled,\npress the up-arrow key to check your solution"; 
		string solution = "After you press the up-arrow key, check\nthe debug window to see the outcome of your \npuzzle.";
		ofTrueTypeFont font;

		// methods associated with the game
		void drawGrid();
		void insideGrid(int x, int y);
		void startPics();
		void startMatrix(int key);
		void text();
		void userInput(int key);
		void inputPics();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg); 
};
