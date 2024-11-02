#include "Settings.hpp"

SettingNode* MySettingValue::createNode(float width) {
	return MySettingNode::create(this, width);
}

// i had to include this cpp file because C++ is a legendary language!