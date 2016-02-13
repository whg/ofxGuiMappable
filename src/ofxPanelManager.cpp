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
    ids = 0;
}

void ofxPanelManager::panelClosed(ofxPanelEventArgs &args) {
    panels.erase(args.panel->getId());
    
}

void ofxPanelManager::addPanel(std::shared_ptr<ofxPanel> panel) {
    panels[ids] = panel;
    panel->setId(ids);
    ids++;

}

void ofxPanelManager::draw() {
    for (auto &pair : panels) {
        pair.second->draw();
    }
}

ofxBaseGui& ofxPanelManager::getGuiElem(string path) {
    
    auto steps = ofSplitString(path, PATH_DELIMITER);
    
    
    
    ofxBaseGui *elem = nullptr;
    for (auto &pair : panels) {
        if (pair.second->getName() == steps[0]) {
            elem = pair.second.get();
            break;
        }
    }
    
    
    for (int i = 1; i < steps.size(); i++) {
        if (ofxGuiGroup *group = dynamic_cast<ofxGuiGroup*>(elem)) {
            elem = group->getControl(steps[i]);
        }
    }
    
    return *elem;
}