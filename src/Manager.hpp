#pragma once

// Manager.hpp structure by acaruso
// reused with explicit permission and strong encouragement

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:

	bool userAgentBareMinimumAcquired = false;
	bool requestFailed = true;

	double direction = -1.0f;

	std::string gameVer = "";
	std::string loaderVer = "";
	std::string modVer = "";
	std::string platformName = "";

	static Manager* getSharedInstance() {
		if (!instance) {
			instance = new Manager();
		}
		return instance;
	}

};