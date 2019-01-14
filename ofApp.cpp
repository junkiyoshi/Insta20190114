#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->draw_sphere(glm::vec3(-250, 0, 0), 450, ofColor(239));
	this->draw_sphere(glm::vec3(500, 500, 0), 200, ofColor(239, 0, 0));
	this->draw_sphere(glm::vec3(500, 0, 0), 200, ofColor(0, 239, 0));
	this->draw_sphere(glm::vec3(500, -500, 0), 200, ofColor(0, 0, 239));

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_sphere(glm::vec3 location, float radius, ofColor color) {

	vector<glm::vec3> locations;
	for (int i = 0; i < 120; i++) {

		glm::vec3 random_location = glm::vec3(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0015), 0, 1, -1, 1),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0015), 0, 1, -1, 1),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0015), 0, 1, -1, 1)
		);

		glm::vec3 l = glm::normalize(random_location) * radius;
		locations.push_back(l + location);
	}

	for (int out_index = 0; out_index < locations.size(); out_index++) {

		ofSetColor(color);
		ofDrawSphere(locations[out_index], 5);

		vector<glm::vec3> near_locations;
		for (int in_index = 0; in_index < locations.size(); in_index++) {

			if (glm::length(locations[out_index] - locations[in_index]) < radius * 0.25) {

				ofDrawLine(locations[out_index], locations[in_index]);
				near_locations.push_back(locations[in_index]);
			}
		}

		if (near_locations.size() > 3) {


			for (int i = 0; i < near_locations.size() - 2; i++) {

				ofSetColor(color, 200);
				ofBeginShape();
				ofVertex(near_locations[i]);
				ofVertex(near_locations[i + 1]);
				ofVertex(near_locations[i + 2]);
				ofEndShape(true);
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}