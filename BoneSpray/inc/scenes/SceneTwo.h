#pragma once

#include "ofxSceneManager/src/ofxScene.h"

class SceneTwo : public ofxScene {
public:
	void setup();
	void update();
	void draw();

	bool bFill;
	bool bWireframe;
	bool bDrawNormals;
	bool bDrawAxes;
	bool bDrawLights;
	bool bMousePressed;
	bool bSplitFaces;

	ofImage texture;
	int mode;

	ofCylinderPrimitive cylinder;

	ofLight pointLight;
	ofLight pointLight2;
	ofLight pointLight3;
	ofMaterial material;

	ofVboMesh topCap, bottomCap, body;
	ofCamera cam;
};