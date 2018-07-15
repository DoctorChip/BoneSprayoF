#include "ofxSceneManager/src/ofxScene.h"
#include "scenes/SceneTwo.h"
#include "jack/port_manager.h"

SceneTwo::SceneTwo(port_manager* portMan)
{
	portManager = portMan;
}

void SceneTwo::setup()
{
	setSceneDuration(0.0, 0.0);
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofBackground(20);

	midi_port = portManager->find_midi_port(0);
}

void SceneTwo::update()
{
	for (int i = 0; i<particles.size(); i++) {
		particles[i].update();
	}
}


void SceneTwo::draw()
{	
	if (midi_port != NULL)
	{
		port_manager::NOTE_EVENT evt = midi_port->buffer.evt;
		if (evt == port_manager::NOTE_EVENT::OFF) {
			ofClear(20);
			return;
		}
	}

	// Particles
	for (int i = 0; i<particles.size(); i++) {
		particle &p = particles[i];
		p.draw();
	}

	for (int i = 0; i<50; i++) {
		createParticle();
	}

	while (particles.size()>5000) {
		particles.erase(particles.begin());
	}

}

void SceneTwo::createParticle() {
	particle p;
	ofColor col(ofRandom(50, 80), ofRandom(50,150), ofRandom(80,170), ofRandom(0.3, 1));
	p.setup();
	p.pos.set(ofRandomWidth(), ofRandomHeight());
	p.color = col;
	particles.push_back(p);
}