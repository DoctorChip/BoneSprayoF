#include "models/particle.h"
#include "ofMain.h"

void particle::setup() {
	vel.x = 5 * ofRandomf();
	vel.y = 5 * ofRandomf();
	angle = ofRandomf()*TWO_PI;
	age = 0;
}

void particle::draw() {
	ofSetColor(color, ofMap(age, 0, 100, 50, 255, true));
	ofSetLineWidth(ofMap(age, 0, 100, 0, 2, true));
	ofLine(oldpos.x, oldpos.y, pos.x, pos.y);
}

void particle::update() {
	angle += ofSignedNoise(pos.x, pos.y)*TWO_PI;
	vel.rotate(angle);
	oldpos = pos;
	pos += vel;
	age++;
}

