#pragma once

#include "ofMain.h"
#include "ofxSceneManager/src/ofxSceneManager.h"
#include "jack/port_manager.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

		bool cursorHidden;

		int midi_port_count = 2;
		int current_scene;
		ofxSceneManager sceneManager;
		static port_manager portManager;
};
