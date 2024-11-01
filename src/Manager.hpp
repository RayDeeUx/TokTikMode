#pragma once

// Manager.hpp structure by acaruso
// reused with explicit permission and strong encouragement

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:
	CCSize winSize = CCDirector::get()->getWinSize();
	float winWidth = winSize.width;
	float winHeight = winSize.height;

	int senderTag = -1;

	static Manager* getSharedInstance() {
		if (!instance) {
			instance = new Manager();
		}
		return instance;
	}

};