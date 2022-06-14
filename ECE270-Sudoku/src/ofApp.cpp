#include "ofApp.h"
#include "ofMain.h"
#include "Sudoku.h"
#include "ofxGui.h"

void ofApp::text()
{
	/* sets color of text to black and 
	uploads to screen with font and size 
	declared in setup() */

	ofSetColor(0, 0, 0);
	font.drawString(title, 1100, 80);
	font.drawString("To Start:", 1100, 120);
	font.drawString(start, 1000, 150);
	font.drawString("To Play:", 1100, 220);
	font.drawString(play, 1000, 250);
	font.drawString(solution, 1000, 340);
	font.drawString("Tips:", 1100, 420);
	font.drawString(tip1, 1000, 450);
	font.drawString(tip2, 1000, 560);
}

void ofApp::drawGrid()
{
	/* functions uses sampling to assign values 
	of the grid[i][j] ofRectangle object to draw
	a 9x9 grid to the screen */

	nx = (xmax - xmin) / x_step + 1;
	ny = (ymax - ymin) / y_step + 1;

	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			grid[i][j].x = (xmin + i * x_step);
			grid[i][j].y = (ymin + j * y_step);
			grid[i][j].width = x_step;
			grid[i][j].height = y_step;
		}
	}

	for (int i = 0; i < ROWS_MAX; i++)
	{
		for (int j = 0; j < COLS_MAX; j++)
		{
			ofSetColor(255, 255, 255);
			ofFill();
			ofDrawRectangle(grid[i][j]);

			ofNoFill();
			ofSetColor(0, 0, 0);
			ofDrawRectangle(grid[i][j]);
		}
	}
}

void ofApp::startMatrix(int key)
{
	/* flips a coin to determine number
	of random values of matrix[i][j] to
	show as clues

	depending on which number solution 
	the user selected on the load screen,
	values of that solution[i][j] are 
	assigned to matrix[i][j] at the i and 
	j positions that the coin is equal to 0 */

	int coin;
	for (int i = 0; i < ROWS_MAX; i++)
	{
		for (int j = 0; j < COLS_MAX; j++)
		{
			coin = rand() % 2;
			if (coin == 0)
			{
				if (key == 1)
				{
					Board.matrix[i][j] = Board.solution1[i][j];
				}
				else if (key == 2)
				{
					Board.matrix[i][j] = Board.solution2[i][j];
				}
				else if (key == 3)
				{
					Board.matrix[i][j] = Board.solution3[i][j];
				}
				else if (key == 4)
				{
					Board.matrix[i][j] = Board.solution4[i][j];
				}
			}
		}
	}

	/* when a value of matrix[i][j] equals 0,
	the values of i and j are stored in the
	corresponding matX and matY arrays

	the image number that is the same value of
	matrix[i][j] is stored in a starterImages
	array at the counted position

	counter increases each time matrix[i][j]
	does not equal 0 */

	for (int i = 0; i < ROWS_MAX; i++)
	{
		for (int j = 0; j < COLS_MAX; j++)
		{
			if (Board.matrix[i][j] != 0)
			{
				matX[random] = j;
				matY[random] = i;
				starterImages[random] = images[Board.matrix[i][j] - 1];
				random++;
			}
		}
	}
} 

void ofApp::startPics()
{
	/* at each counted value, each image
	stored in the starterImages array is
	drawn at the matX[i] and matY[i]
	position multiplied by 100

	each position is multiplied by 100 so
	that they go inside of the appropriate
	square within the grid */

	for (int i = 0; i < random; i++)
	{
		ofSetColor(216, 212, 255); // pastel purple 
		starterImages[i].draw(matX[i] * 100, matY[i] * 100);
	}
}

void ofApp::insideGrid(int x, int y)
{
	/* when the user clicks on a square 
	within the board/grid, the square will 
	highlight grey to let them know it 
	has been pressed (which indicates they
	are able to input their number value) */

	for (int i = 0; i < ROWS_MAX; i++)
	{
		for (int j = 0; j < COLS_MAX; j++)
		{
			bool inResult = grid[i][j].inside(x, y);
			if (inResult == true)
			{
				index_i[filled] = i;
				index_j[filled] = j;
				
				ofSetColor(128, 128, 128);
				ofFill();
				ofDrawRectangle(grid[index_i[filled]][index_j[filled]]);

			}
		}
	}
}

 void ofApp::userInput(int key)
{
	/* when a key is pressed and the inputFlag
	is true so that the user can type, the image
	of that same number key is stored inside of the
	filledImages array, which will then be 
	outputted onto the screen in the square within 
	the grid that the user has pressed */

	int input;
	if (key <= 58 && key > 48 && inputFlag == true)
	{
		input = key - 48; 
		// input is (- 48) because (decimal) ASCII for 1-9 are 49-58  
		
		Board.matrix[index_j[filled]][index_i[filled]] = input;
		filledImages[filled] = images[input - 1]; 
		// input is (- 1) so that the correct image[0-8] is outputted
		
		Board.printMatrix();
		inputFlag = false;
		/* inputFlag changes back to 'false' so that the user is 
		only allowed to input one value at a time */
		
		filled++;
	}

	/* when the program is run, the screen is blank
	other than the directions to the game. when the 
	down-arrow key is pressed, the grid will print. 
	
	if the key pressed is the up-arrow key, the 
	check function within the Sudoku class is run 
	to see whether the user has solved the puzzle 
	
	in order to pick a solution, the user must press
	a number key one through four. when they pick 
	their number and press the down-arrow key, the   
	startMatrix() function will run through to pick
	the random clues and then show the number image 
	of those clues on the screen 
	
	the startFlag indicates when the user is allowed
	to choose their solution. it is initialized to 
	true for when the program runs, but changes to
	false when the user presses a key to choose a 
	solution. it never changes back to true so that
	the user cannot overlap two or more puzzle
	solutions */

	if (inputFlag == false && key == OF_KEY_UP)
	{
		solResult = Board.checkWin();
		// cout << "\n" << solResult << endl;
	}
	else if (inputFlag == false && key == OF_KEY_DOWN)
	{
		drawGrid();
		startPics();
	}
	if (startFlag == true && key <= 52 && key > 48)
	{
		startMatrix(key - 48);
		Board.printMatrix();
		startFlag = false;
	}
}

 void ofApp::inputPics()
{
	/* at each counted value (filled), the
	image of each typed (input) value stored 
	inside of the filledImages array is
	drawn at the index_i[i] and index_j[i]
	position multiplied by 100 
	
	starterImages[i] is separate from 
	filledImages[i] so that the clues 
	are untouched when the user inputs 
	their own values */

	for (int i = 0; i < filled; i++)
	{
		ofSetColor(249, 249, 236); // light yellow
		filledImages[i].draw(index_i[i] * 100, index_j[i] * 100);
	}
} 

//--------------------------------------------------------------
void ofApp::setup(){
	srand(time(NULL));
	ofSetFrameRate(30);
	ofSetWindowShape(1500, 1500);
	ofSetBackgroundAuto(false);
	ofSetBackgroundColor(255, 255, 255);
	
	/* each image of a number 1 through 
	9 is loaded into the program with the 
	following ofImage function calls */

	images[0].load("num1.png");
	images[1].load("num2.png");
	images[2].load("num3.png");
	images[3].load("num4.png");
	images[4].load("num5.png");
	images[5].load("num6.png");
	images[6].load("num7.png");
	images[7].load("num8.png");
	images[8].load("num9.png");

	font.load("PublicSans-VariableFont_wght.ttf", 15);
	// loads font to program with desired font size

	/* the initial, empty matrix[i][j] is printed, 
	then printed again with random clues from solution
	in their appropriate spots within the matrix after
	startMatrix() function is called */

	Board.printMatrix();

}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	text();
	inputPics();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	userInput(key);	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	/* inputFlag changing to 'true' indicates
	that the user is allowed to input a value
	on the grid */

	inputFlag = true;
	insideGrid(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
