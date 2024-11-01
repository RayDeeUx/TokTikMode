#include <Geode/modify/FriendsProfilePage.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define MAGIC_NUMBER (-2123456789)

class $modify(MyFriendsProfilePage, FriendsProfilePage) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("FriendsProfilePage::setupUsersBrowser", MAGIC_NUMBER);
		(void) self.setHookPriority("FriendsProfilePage::onClose", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void onClose(CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooter") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return FriendsProfilePage::onClose(sender);
		// re-creation of original code -- see about.md for credits
		auto touchDispatcher = CCTouchDispatcher::get();
		if (m_listLayer) touchDispatcher->unregisterForcePrio(m_listLayer);
		touchDispatcher->unregisterForcePrio(this);
		setKeypadEnabled(false);
		removeFromParentAndCleanup(true);
		m_fields->manager->senderTag = -1;
	}
	void setupUsersBrowser(cocos2d::CCArray* users, UserListType type) {
		FriendsProfilePage::setupUsersBrowser(users, type);
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooter") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return;
		Utils::showFirstTimeAlert();
	}
};