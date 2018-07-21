#pragma once
#include "ofxSceneManager/src/ofxScene.h"
#include "jack/port_manager.h"

class SceneOne : public ofxScene {
public:

	SceneOne(port_manager* portMan);

	void setup();
	void update();
	void draw();
	void willFadeOut();

	ofCamera cam;
	ofImage texture;
	ofLight pointLight;
	ofMaterial material;

	port_manager* portManager;
	port_manager::midi_port* midi_port;

	vector<ofBoxPrimitive> notes;
};
