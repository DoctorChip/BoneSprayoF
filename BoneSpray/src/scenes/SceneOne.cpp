#include "ofxSceneManager/src/ofxScene.h"
#include "scenes/SceneOne.h"
#include "jack/port_manager.h"

SceneOne::SceneOne(port_manager* portMan)
{
	portManager = portMan;
}

void SceneOne::setup()
{
	setSceneDuration(0.01, 0.01);
	midi_port = portManager->find_midi_port(1);

	ofSetVerticalSync(true);
	ofBackground(100);

	texture.load("of.png");
	texture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

	ofSetSmoothLighting(true);
	pointLight.setDiffuseColor(ofFloatColor(.85, .85, .55));
	pointLight.setSpecularColor(ofFloatColor(1.f, 1.f, 1.f));
	material.setShininess(120);
	material.setSpecularColor(ofColor(255, 255, 255, 255));
}

void SceneOne::update()
{
	pointLight.setPosition((ofGetWidth()*.5) + cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight() / 2, 500);
}

void SceneOne::draw()
{
	ofClear(0);

	// Get midi data from port
	port_manager::midi_port_event *midi = new port_manager::midi_port_event;
	if (midi_port != NULL) *midi = midi_port -> buffer;

	// Calculate note position
	int width = ofGetWidth();
	int height = ofGetHeight();
	int midi_pos = ofMap(midi -> note, 0, 127, 0, width, true);

	// Create note and add to array
	if (midi != NULL && midi -> evt == port_manager::NOTE_EVENT::ON)
	{
		ofBoxPrimitive box;
		box.setPosition(midi_pos, height /2, 0);
		notes.push_back(box);
	}

	// Scene config
	cam.setGlobalPosition({ 0,0,cam.getImagePlaneDistance(ofGetCurrentViewport()) });
	cam.begin();
	ofEnableDepthTest();
	ofEnableLighting();
	pointLight.enable();

	material.begin();
	ofFill();

	// Render notes
	for (int i = 0; i < notes.size();  i++)
	{
		notes[i].draw();
	};

	material.end();

	// Cleanup
	ofDisableLighting();
	ofDisableDepthTest();
	ofFill();
	cam.end();
}

/*
 *	Callback event, called on scene exit
 */
void SceneOne::willFadeOut()
{
	std::cout << "Exit scene" << std::endl;
}