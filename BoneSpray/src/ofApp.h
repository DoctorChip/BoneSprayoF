#pragma once

#include "ofMain.h"
#include "ofxSceneManager/src/ofxSceneManager.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

		bool cursorHidden;

		int current_scene;
		ofxSceneManager sceneManager;
};
