#pragma once

#include "ofxPanel.h"

class ofxPanelManager {
    
public:

    static ofxPanelManager& get();
    
    void panelClosed(ofxPanelEventArgs &args);
    void addPanel(std::shared_ptr<ofxPanel> panel);
    
    ofxBaseGui& getGuiElem(string path);
    
    void draw();
    
    map<string, std::shared_ptr<ofxPanel>> panels;
    
private:
    void setup();
    ofxPanelManager() {}
};

/// make a path to @param gui
/// separated by / with the top parent first
inline string getGuiPath(ofxBaseGui *gui) {
    
    deque<string> parents = { gui->getName() };
    ofxBaseGui *current = gui;
    
    while (true) {
        ofxBaseGui *parent = current->getParent();
        if (parent == nullptr) {
            break;
        }
        parents.push_front(parent->getName());
        current = parent;
    }
    
    return ofJoinString(vector<string>(parents.begin(), parents.end()), "/");
}