#include "ofxSceneManager/src/ofxScene.h"
#include "scenes/SceneTwo.h"

void SceneTwo::setup() {

	setSceneDuration(0.0, 0.0);

	ofSetVerticalSync(true);
	ofBackground(20);

	// GL_REPEAT for texture wrap only works with NON-ARB textures //
	ofDisableArbTex();
	texture.load("of.png");
	texture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

	bFill = true;
	bWireframe = true;
	bDrawNormals = false;
	bDrawAxes = false;
	bDrawLights = false;
	bMousePressed = false;
	bSplitFaces = false;

	float width = ofGetWidth() * .12;
	float height = ofGetHeight() * .12;


	cylinder.set(width*.7, height*2.2);

	mode = 0;

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

void SceneTwo::update() {
	pointLight.setPosition((ofGetWidth()*.5) + cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight() / 2, 500);
	pointLight2.setPosition((ofGetWidth()*.5) + cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
		ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);

	pointLight3.setPosition(
		cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
		sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
		cos(ofGetElapsedTimef()*.2) * ofGetWidth()
	);

}

void SceneTwo::draw() {
	
	ofClear(0);

	float spinX = sin(ofGetElapsedTimef()*.35f);
	float spinY = cos(ofGetElapsedTimef()*.075f);

	if (bMousePressed) {
		spinX = spinY = 0.0f;
	}

	cam.setGlobalPosition({ 0,0,cam.getImagePlaneDistance(ofGetCurrentViewport()) });
	cam.begin();

	ofEnableDepthTest();

	ofEnableLighting();
	pointLight.enable();
	pointLight2.enable();
	pointLight3.enable();

	// draw the outer sphere
	material.begin();
	ofNoFill();
	ofDrawSphere(0, 0, max(ofGetWidth(),ofGetHeight()));
	material.end();

	if (mode == 1 || mode == 3) texture.getTexture().bind();

	float screenWidth = ofGetWidth();
	float screenHeight = ofGetHeight();

	cylinder.setPosition(-screenWidth / 4, 0, 0);

	// Cylinder //
	if (mode == 3) {
		topCap = cylinder.getTopCapMesh();
		bottomCap = cylinder.getBottomCapMesh();
		body = cylinder.getCylinderMesh();
	}

	cylinder.rotateDeg(spinX, 1.0, 0.0, 0.0);
	cylinder.rotateDeg(spinY, 0, 1.0, 0.0);
	if (bFill) {
		material.begin();
		ofFill();
		if (mode == 3) {
			cylinder.transformGL();
			ofPushMatrix(); {
				if (topCap.getNumNormals() > 0) {
					ofTranslate(topCap.getNormal(0) * (cos(ofGetElapsedTimef() * 5) + 1)*.5f * 100);
					topCap.draw();
				}
			} ofPopMatrix();
			ofPushMatrix(); {
				if (bottomCap.getNumNormals() > 0) {
					ofTranslate(bottomCap.getNormal(0) * (cos(ofGetElapsedTimef() * 4) + 1)*.5f * 100);
					bottomCap.draw();
				}
			} ofPopMatrix();
			ofPushMatrix(); {
				float scale = (cos(ofGetElapsedTimef() * 3) + 1)*.5f + .2;
				ofScale(scale, scale, scale);
				body.draw();
			} ofPopMatrix();
			cylinder.restoreTransformGL();
		}
		else {
			cylinder.draw();
		}
		material.end();
	}

	if (bWireframe) {
		ofNoFill();
		ofSetColor(0, 0, 0);
		cylinder.setScale(1.01f);
		cylinder.drawWireframe();
		cylinder.setScale(1.0f);
	}

	if (!bFill && bWireframe) {
		material.end();
	}

	if (mode == 1 || mode == 3) texture.getTexture().unbind();

	material.end();
	ofDisableLighting();

	if (bDrawLights) {
		ofFill();
		ofSetColor(pointLight.getDiffuseColor());
		pointLight.draw();
		ofSetColor(pointLight2.getDiffuseColor());
		pointLight2.draw();
		ofSetColor(pointLight3.getDiffuseColor());
		pointLight3.draw();
	}

	if (bDrawNormals) {
		ofSetColor(225, 0, 255);
		cylinder.drawNormals(20, bSplitFaces);
	}
	if (bDrawAxes) {
		cylinder.drawAxes(cylinder.getHeight() + 30);
	}

	ofDisableDepthTest();

	ofFill();

	cam.end();
}
