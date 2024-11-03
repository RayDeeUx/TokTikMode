#pragma once

// Manager.hpp structure by acaruso
// reused with explicit permission and strong encouragement

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:
	int senderTag = -1;

	bool hasCalledAlready = false;

	bool originalIsBlending = false;
	bool originalIsChroma = false;
	bool originalMaxAlpha = false;

	static Manager* getSharedInstance() {
		if (!instance) {
			instance = new Manager();
		}
		return instance;
	}

};