#include "ofApp.h"

#define STRINGIFY(A) #A

//--------------------------------------------------------------
void ofApp::setup(){
    
    lightSize = 256;
    cat4.load("yVkiKwx.png");
    occluders.allocate(cat4.getWidth(), cat4.getHeight(), GL_RGBA);
    occluders.begin();
    cat4.draw(0, 0);
    occluders.end();
    
   /*
    for (int i = 0; i<cat4.getWidth(); i++) {
        for (int j = 0; j< cat4.getHeight(); j++) {
        
        }
    }*/
    
    ofBackground(0);
    ofDisableArbTex();  // <-- Very Important
    lightRender.setup(cat4.getWidth(), cat4.getHeight());
    ofBackground(0);
    
    lightRender.setRenderFuction(this, &ofApp::renderObjects);
    
    lightRender.addLight(255, 255);
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    lightRender.renderLights();
    
    if(lightRender.lights.size()) lightRender.lights[0].pos.set(ofGetMouseX(), ofGetMouseY());
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    lightRender.draw();
    renderObjects();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::renderObjects() {
    ofFill();
    cat4.getTexture().draw(0, 0);
    //ofSetHexColor(0x90d4e3);
    //ofCircle(100,150,5);
    //occluders.draw(0, 0);
    
    
}