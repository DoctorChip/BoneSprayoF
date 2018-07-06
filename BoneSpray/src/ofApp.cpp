#include "ofApp.h"
#include "jack/jack_interface.h"

#include "ofxSceneManager/src/ofxSceneManager.h"
#include "scenes/SceneOne.h"
#include "scenes/SceneTwo.h"

#pragma comment(lib, "libjack.lib")

#define MIDI_PORT_COUNT 3

void ofApp::setup(){

	// Jack
	//jack::activate();
	//jack::create_midi_array(MIDI_PORT_COUNT);

	// Window
	ofHideCursor();
	cursorHidden = true;

	// Scene Manager
	sceneManager.addScene(ofPtr<ofxScene>(new SceneOne()));
	sceneManager.addScene(ofPtr<ofxScene>(new SceneTwo()));
	sceneManager.run();
}

void ofApp::update(){
	sceneManager.update();
}

void ofApp::draw(){
	sceneManager.draw();
}

void ofApp::keyPressed(int key){

	// Enter - toggle fullscreen mode
	if (key == 13) ofToggleFullscreen();

	// C - toggle mouse
	else if (key == 99) {
		cursorHidden ? ofShowCursor() : ofHideCursor();
		cursorHidden = !cursorHidden;
	}

	else if (key >= 49 && key <= 58) {
		sceneManager.changeScene(key - 49);
	}
}