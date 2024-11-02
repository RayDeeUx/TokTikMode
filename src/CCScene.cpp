#include <Geode/modify/CCScene.hpp>
#include "PlayLayer.hpp"

using namespace geode::prelude;

class $modify(MyCCScene, CCScene) {
	int getHighestChildZ() {
		PlayLayer* pl = PlayLayer::get();
		if (!pl) return CCScene::getHighestChildZ();

		MyPlayLayer* mpl = static_cast<MyPlayLayer*>(pl);
		if (!mpl->m_fields->m_skipZOrder) return CCScene::getHighestChildZ();

		CCNode* container = mpl->m_fields->m_container;
		if (!container) return CCScene::getHighestChildZ();

		int origZ = container->getZOrder();
		container->setZOrder(-1);
		int ret = CCScene::getHighestChildZ();
		container->setZOrder(origZ);
		return ret;
	}
};