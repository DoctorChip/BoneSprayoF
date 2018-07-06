#pragma once

#include "ofxSceneManager/src/ofxScene.h"

class SceneOne : public ofxScene {
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

	ofSpherePrimitive sphere;
	ofIcoSpherePrimitive icoSphere;
	ofPlanePrimitive plane;
	ofCylinderPrimitive cylinder;
	ofConePrimitive cone;
	ofBoxPrimitive box;

	ofLight pointLight;
	ofLight pointLight2;
	ofLight pointLight3;
	ofMaterial material;

	ofVboMesh boxSides[ofBoxPrimitive::SIDES_TOTAL];
	ofVboMesh deformPlane;
	ofVboMesh topCap, bottomCap, body;
	vector<ofMeshFace> triangles;
	ofCamera cam;
};
