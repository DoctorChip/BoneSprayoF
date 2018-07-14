#pragma once

#include "ofMain.h"

class particle {
public:

	void setup();
	void draw();
	void update();

	ofVec2f pos, vel, acc, oldpos;
	float angle;
	ofColor color;
	int age;
};