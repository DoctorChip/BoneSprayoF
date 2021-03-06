#include "ofApp.h"
#include "jack/port_manager.h"
#include "ofxSceneManager/src/ofxSceneManager.h"
#include "scenes/SceneOne.h"
#include "scenes/SceneTwo.h"
#pragma comment(lib, "libjack.lib")

port_manager ofApp::portManager;

void ofApp::setup(){

	// Jack
	portManager.activate();
	portManager.create_midi_array(midi_port_count);

	// Pause until keypress
	std::cout << "Jack started. Press a key to continue..." << std::endl;
	cin.get();

	// Window
	ofHideCursor();
	cursorHidden = true;
	//ofSetFullscreen(true);

	// Scene Manager
	current_scene = 0;
	sceneManager.addScene(ofPtr<ofxScene>(new SceneOne(&portManager)));
	sceneManager.addScene(ofPtr<ofxScene>(new SceneTwo(&portManager)));
	sceneManager.run();

	// Jack to Scene Binding
	// TODO
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

		// Get scene ID - if current, do nothing
		int scene_id = key - 49;
		if (scene_id == current_scene) return;

		current_scene = scene_id;
		sceneManager.changeScene(scene_id);
	}
}