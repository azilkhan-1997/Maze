#include "ofApp.h"
#include "ofxTweener.h"		// ����� ��� ��������

//--------------------------------------------------------------
void ofApp::setup(){
	// ������������� �� ������� ��������� ����������
	widthMaze_.addListener(this, &ofApp::widthMazeChanged);
	heightMaze_.addListener(this, &ofApp::heightMazeChanged);
	generateMazeButton_.addListener(this, &ofApp::generateMazeButtonClick);
	runPlayerButton_.addListener(this, &ofApp::runPlayerClick);
	// �������� ����� setup � ������
	mazeUiPanel_.setup();
	// � ��������������� ��������� ��� �������� ����������
	mazeUiPanel_.add(widthMaze_.setup("Width Maze", 3, 2, 100));
	mazeUiPanel_.add(heightMaze_.setup("Height Maze", 3, 2, 100));
	mazeUiPanel_.add(generateMazeButton_.setup("Generate Maze"));
	mazeUiPanel_.add(runPlayerButton_.setup("Find short way"));
}

//--------------------------------------------------------------
void ofApp::update(){
	Tweener.update();	// ���������� ��������
	maze_.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::azure, ofColor::orange);
	maze_.draw();
	mazeUiPanel_.draw();
}

void ofApp::exit()
{
	// ������������ �� �������
	heightMaze_.removeListener(this, &ofApp::heightMazeChanged);
	widthMaze_.removeListener(this, &ofApp::widthMazeChanged);
	generateMazeButton_.removeListener(this, &ofApp::generateMazeButtonClick);
	runPlayerButton_.removeListener(this, &ofApp::runPlayerClick);
}

void ofApp::widthMazeChanged(int& width)
{
}

void ofApp::heightMazeChanged(int& height)
{
}

void ofApp::generateMazeButtonClick()
{
	maze_.setup(widthMaze_, heightMaze_);
}

void ofApp::runPlayerClick()
{
	maze_.run();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	maze_.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	maze_.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	maze_.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	maze_.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	maze_.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
	maze_.mouseScrolled(x, y, scrollX, scrollY);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	maze_.windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
