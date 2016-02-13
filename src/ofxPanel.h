#pragma once

#include "ofxGuiGroup.h"

class ofxGuiGroup;

class ofxPanelEventArgs;

class ofxPanel : public ofxGuiGroup {
public:
	ofxPanel();
	ofxPanel(const ofParameterGroup & parameters, const std::string& filename="settings.xml", float x = 10, float y = 10);
	~ofxPanel();

	ofxPanel * setup(const std::string& collectionName="", const std::string& filename="settings.xml", float x = 10, float y = 10);
	ofxPanel * setup(const ofParameterGroup & parameters, const std::string& filename="settings.xml", float x = 10, float y = 10);

	bool mouseReleased(ofMouseEventArgs & args);

	ofEvent<void> loadPressedE;
	ofEvent<void> savePressedE;
    
    static ofEvent<ofxPanelEventArgs> panelClosedEvent;
    
protected:
	void render();
	bool setValue(float mx, float my, bool bCheck);
	void generateDraw();
	void loadIcons();
        
private:
	ofRectangle loadBox, saveBox, closeBox;
	static ofImage loadIcon, saveIcon, closeIcon;
    
    ofPoint grabPt;
	bool bGrabbed;
};

struct ofxPanelEventArgs : public ofEventArgs {
    ofxPanel *panel;
};