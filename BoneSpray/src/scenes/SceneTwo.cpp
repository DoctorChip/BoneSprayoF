#include "ofxSceneManager/src/ofxScene.h"
#include "scenes/SceneTwo.h"

void SceneTwo::setup()
{
	setSceneDuration(0.0, 0.0);
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofBackground(20);
}

void SceneTwo::update()
{
	for (int i = 0; i<particles.size(); i++) {
		particles[i].update();
	}
}

void SceneTwo::draw()
{	
	ofSetColor(255);

	for (int i = 0; i<particles.size(); i++) {
		particle &p = particles[i];
		p.draw();
	}

	for (int i = 0; i<50; i++) {
		createParticle();
	}

	while (particles.size()>10000) {
		particles.erase(particles.begin());
	}

}

void SceneTwo::createParticle() {
	particle p;
	ofColor col(ofRandom(50, 225), ofRandom(50,225), ofRandom(50,225), ofRandom(0.3, 1));
	p.setup();
	p.pos.set(ofRandomWidth(), ofRandomHeight());
	p.color = col;
	particles.push_back(p);
}