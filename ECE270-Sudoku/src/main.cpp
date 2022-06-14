#include "ofMain.h"
#include "ofApp.h"
#include "Sudoku.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1500,1500,OF_WINDOW);			// <-------- setup the GL context

	srand(time(NULL));
	ofRunApp(new ofApp());
}
