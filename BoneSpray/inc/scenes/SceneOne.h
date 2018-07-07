#pragma once
#include "ofxSceneManager/src/ofxScene.h"

class SceneOne : public ofxScene {
public:
	void setup();
	void update();
	void draw();

	ofImage texture;
	ofCylinderPrimitive cylinder;

	ofLight pointLight;
	ofLight pointLight2;
	ofLight pointLight3;
	ofMaterial material;

	ofVboMesh topCap, bottomCap, body;
	ofCamera cam;
};
