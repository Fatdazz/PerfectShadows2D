#include "ofApp.h"

#define STRINGIFY(A) #A

//--------------------------------------------------------------
void ofApp::setup(){
    
    lightSize = 256;
    cat4.load("yVkiKwx.png");
    occludersFBO.allocate(lightSize, lightSize, GL_RGBA);
    
    occludersFBO.begin();
    ofClear(255,255,255, 0);
    cat4.drawSubsection(0, 0, lightSize, lightSize, (ofGetWindowWidth()/2) - lightSize/2, (ofGetWindowHeight()/2) - lightSize/2);
    occludersFBO.end();
    string VERT_SRC = STRINGIFY(
                                
            attribute vec4 a_position;
            attribute vec4 a_color;
            attribute vec2 a_texCoord0;
            uniform mat4 u_projTrans;
            
            varying vec2 vTexCoord0;
            varying vec4 vColor;
                                
            void main() {
                vColor = a_color;
                vTexCoord0 = a_texCoord0;
                gl_Position = u_projTrans * a_position;
            }
    
    
    );
    
    
    string shaderProgramShadowMap = STRINGIFY(
            //#define PI 3.14
                                              
            //inputs from vertex shader
            varying vec2 vTexCoord0;

            //uniform values
            uniform sampler2D u_texture;
            uniform vec2 resolution;
                                              
            //alpha threshold for our occlusion map
            const float THRESHOLD = 0.75;
                                              
            void main(void) {
                float distance = 1.0;
                for (float y=0.0; y<resolution.y; y+=1.0) {
                    //rectangular to polar filter
                    vec2 norm = vec2(vTexCoord0.s, y/resolution.y) * 2.0 - 1.0;
                    float theta = 3.14*1.5 + norm.x * 3.14;
                    float r = (1.0 + norm.y) * 0.5;
                    //coord which we will sample from occlude map
                    vec2 coord = vec2(-r * sin(theta), -r * cos(theta))/2.0 + 0.5;
                    //sample the occlusion map
                    vec4 data = texture2D(u_texture, coord);
                    //the current distance is how far from the top we've come
                    float dst = y/resolution.y;
                    //if we've hit an opaque fragment (occluder), then get new distance
                    //if the new distance is below the current, then we'll use that for our ray
                    float caster = data.a;
                    if (caster > THRESHOLD) {
                        distance = min(distance, dst);
                        //NOTE: we could probably use "break" or "return" here
                        }
                    }
                    gl_FragColor = vec4(vec3(distance), 1.0);
                }
    );
    
    
    //setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shadowMap.setupShaderFromSource(GL_VERTEX_SHADER, VERT_SRC);
    shadowMap.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgramShadowMap);
    shadowMap.linkProgram();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    shadowMap.begin();
    occludersFBO.draw(0,0);
    shadowMap.end();
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
