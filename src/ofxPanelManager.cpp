//
//  ofxPanelManager.cpp
//  desperados studio test
//
//  Created by Will Gallia on 11/02/2016.
//
//

#include "ofxPanelManager.h"

shared_ptr<ofxPanelManager> panelManager = nullptr;

ofxPanelManager& ofxPanelManager::get() {
    if (panelManager == nullptr) {
        panelManager = shared_ptr<ofxPanelManager>(new ofxPanelManager);
        panelManager->setup();
    }
    return *panelManager.get();
}

void ofxPanelManager::setup() {
    ofAddListener(ofxPanel::panelClosedEvent, this, &ofxPanelManager::panelClosed);
}

void ofxPanelManager::panelClosed(ofxPanelEventArgs &args) {
    cout << args.panel->getName() << " closed" << endl;
    
    panels.erase(args.panel->getName());
    
}

void ofxPanelManager::addPanel(std::shared_ptr<ofxPanel> panel) {
    panels[panel->getName()] = panel;
}

void ofxPanelManager::draw() {
    for (auto &pair : panels) {
        pair.second->draw();
    }
}

ofxBaseGui& ofxPanelManager::getGuiElem(string path) {
    
    auto steps = ofSplitString(path, "/");
    
    ofxBaseGui *elem = panels[steps[0]].get();
    
    for (int i = 1; i < steps.size(); i++) {
        if (ofxGuiGroup *group = dynamic_cast<ofxGuiGroup*>(elem)) {
            elem = group->getControl(steps[i]);
        }
    }
    
    cout << elem->getName() << endl;
    return *elem;
}