#include "ofxSceneManager/src/ofxScene.h"
#include "scenes/SceneOne.h"

void SceneOne::setup()
{
	setSceneDuration(0.01, 0.01);

	ofSetVerticalSync(true);
	ofBackground(100);

	texture.load("of.png");
	texture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

	float width = ofGetWidth() * .12;
	float height = ofGetHeight() * .12;

	cylinder.set(width*.7, height*2.2);

	ofSetSmoothLighting(true);
	pointLight.setDiffuseColor(ofFloatColor(.85, .85, .55));
	pointLight.setSpecularColor(ofFloatColor(1.f, 1.f, 1.f));

	pointLight2.setDiffuseColor(ofFloatColor(238.f / 255.f, 57.f / 255.f, 135.f / 255.f));
	pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));

	pointLight3.setDiffuseColor(ofFloatColor(19.f / 255.f, 94.f / 255.f, 77.f / 255.f));
	pointLight3.setSpecularColor(ofFloatColor(18.f / 255.f, 150.f / 255.f, 135.f / 255.f));

	material.setShininess(120);
	material.setSpecularColor(ofColor(255, 255, 255, 255));
	ofSetSphereResolution(24);
}

void SceneOne::update()
{
	pointLight.setPosition((ofGetWidth()*.5) + cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight() / 2, 500);
	pointLight2.setPosition((ofGetWidth()*.5) + cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
		ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);

	pointLight3.setPosition(
		cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
		sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
		cos(ofGetElapsedTimef()*.2) * ofGetWidth()
	);
}

void SceneOne::draw()
{
	ofClear(0);

	float spinX = sin(ofGetElapsedTimef()*.35f);
	float spinY = cos(ofGetElapsedTimef()*.075f);

	cam.setGlobalPosition({ 0,0,cam.getImagePlaneDistance(ofGetCurrentViewport()) });
	cam.begin();

	ofEnableDepthTest();
	ofEnableLighting();
	pointLight.enable();
	pointLight2.enable();
	pointLight3.enable();

	float screenWidth = ofGetWidth();
	float screenHeight = ofGetHeight();

	// Cylinder //
	cylinder.setPosition(screenWidth / 4, 0, 0);
	cylinder.rotateDeg(spinX, 1.0, 0.0, 0.0);
	cylinder.rotateDeg(spinY, 0, 1.0, 0.0);

	material.begin();
	ofFill();
	cylinder.draw();
	material.end();

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
	cylinder.set(0, 0, 0);
	std::cout << "Exit scene" << std::endl;
}