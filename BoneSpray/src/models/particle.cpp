#include "models/particle.h"
#include "ofMain.h"

void particle::setup() {
	vel.x = 2 * ofRandomf();
	vel.y = 2 * ofRandomf();
	angle = ofRandomf()*TWO_PI;
	age = 0;
}

void particle::draw() {
	ofSetColor(color, ofMap(age, 0, 2000, 255, 0, true));
	ofLine(oldpos.x, oldpos.y, pos.x, pos.y);
}

void particle::update() {
	angle += ofSignedNoise(pos.x, pos.y)*TWO_PI;
	vel.rotate(angle);
	oldpos = pos;
	pos += vel;
	age++;
}

