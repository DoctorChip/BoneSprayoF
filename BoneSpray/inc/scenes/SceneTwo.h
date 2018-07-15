#pragma once

#include "ofxSceneManager/src/ofxScene.h"
#include "models/particle.h"
#include "jack/port_manager.h"

class SceneTwo : public ofxScene {
public:
	SceneTwo(port_manager* portMan);

	void setup();
	void update();
	void draw();
	void createParticle();

	port_manager* portManager;
	port_manager::midi_port* midi_port;

	vector<particle> particles;
};