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

		bool bFill;
		bool bWireframe;
		bool bDrawLights;

		ofxSceneManager sceneManager;

		ofImage texture;
		ofSpherePrimitive sphere;
		vector<ofMeshFace> triangles;

		ofLight pointLight;
		ofLight pointLight2;
		ofLight pointLight3;
		ofMaterial material;

		ofCamera cam;
};
