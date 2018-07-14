#pragma once

#include "ofxSceneManager/src/ofxScene.h"
#include "models/particle.h"

class SceneTwo : public ofxScene {
public:
	void setup();
	void update();
	void draw();
	void createParticle();

	vector<particle> particles;
};