//\ ofxXimea Example
//\ rev03122015 Nathan Wade 

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// XIMEA
	//configure 
	xiCam.openDialog(); //interactive CLI selection
	//xiCam.openDevice(2); //or set with known index
	xiCam.config(XI_MONO8); //XI_MONO8 or XI_RGB32 are implemented
	xiCam.setExposure(10000);
	xiCam.setTriggerMode(0,0);

	//set binning (downsampling)
	binning = 1;
	xiCam.setBinning(binning,binning);
	ini = false;

	//set AWB region
	roi = ofRectangle(0,0,xiCam.sensorWidth, xiCam.sensorHeight);
	xiCam.setAWBROI(roi); 
	xiCam.setFrameRate(30);

    
    // SQUASH
    auto port = 4444;
    string ipAddress = "127.0.0.1";
    
    auto result = ofSystemTextBoxDialog("Target IP Address (Default : " + ipAddress + ")");
    if (!result.empty()) {
        ipAddress = result;
    }
    
    this->sender.init(ipAddress, port);
    
    ofSetWindowTitle("Sending to : " + ipAddress + ":" + ofToString(port) + ", fps :" + ofToString(ofGetFrameRate()));
//    ofSetFrameRate(60);
}


//--------------------------------------------------------------
void testApp::update(){
	xiCam.update();
    
    if(xiCam.ofxcvcolor.bAllocated){
        this->sender.send(xiCam.ofxcvcolor.getPixels());
    }
    else if(xiCam.ofxcvgray.bAllocated){
        this->sender.send(xiCam.ofxcvgray.getPixels());
    }

    
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);

	xiCam.draw(0,0); //draw without scaling
	//xiCam.draw(0,0, ofGetWidth(), ofGetHeight()); //draw with scaling

	//draw ROI
	ofSetLineWidth(2);
	ofSetColor(0,0,255);
	ofNoFill();
	ofRect(roi);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch (key) 
    {   
		case '=':	//increase binning
		{
			switch (binning)
			{
			case 1:
				binning = 2;
				break;
			case 2: binning = 4;
				break;
			}

			xiCam.setBinning(binning, binning);
			break;
		}

		case '-':	//decrease binning
		{
			switch (binning)
			{
			case 2:
				binning = 1;
				break;
			case 4: binning = 2;
				break;
			}
			
			xiCam.setBinning(binning, binning);
			break;
		}
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	roi.setWidth(ofGetMouseX() - mX);
	roi.setHeight(ofGetMouseY() - mY);
	
	xiCam.setAWBROI(roi);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(!ini){
		xiCam.setAWB(1);
		roi.setWidth(1);
		roi.setHeight(1);
		mX = ofGetMouseX();
		mY = ofGetMouseY();
		roi.setPosition(mX,mY);
		ini = true;
	}	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	ini = false;
	xiCam.setAWB(0);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void testApp::exit(){
	xiCam.close();
}
