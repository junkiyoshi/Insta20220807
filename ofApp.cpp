
#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetColor(0);
	ofNoFill();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 15, true, true, true);
	this->word = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int size = 15;
	for (int x = -330; x <= 330; x += size) {

		for (int y = -330; y <= 330; y += size) {

			auto radius = ofMap(ofNoise(x * 0.008, y * 0.008, ofGetFrameNum() * 0.035), 0, 1, 50, 430);
			auto param = abs(radius - glm::length(glm::vec2(x, y)));
			int word_index = ofRandom(this->word.size());

			if (param < 50) {

				ofPushMatrix();
				ofTranslate(x - size * 0.5, y + size * 0.5);

				auto rad = atan2(y, x);
				ofRotate(rad * RAD_TO_DEG + 90);

				ofPath chara_path = this->font.getCharacterAsPoints(this->word[word_index], true, false);
				vector<ofPolyline> outline = chara_path.getOutline();

				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					ofNextContour(true);

					auto vertices = outline[outline_index].getVertices();
					ofVertices(vertices);
				}
				ofEndShape(true);

				ofPopMatrix();
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}