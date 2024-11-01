#include <Geode/modify/MessagesProfilePage.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define MAGIC_NUMBER (-2123456789)

class $modify(MyMessagesProfilePage, MessagesProfilePage) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("MessagesProfilePage::onClose", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void onClose(CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("footerMenu") || !PlayLayer::get() || m_fields->manager->senderTag != 4) return MessagesProfilePage::onClose(sender);
		auto touchDispatcher = CCTouchDispatcher::get();
		if (m_listLayer) touchDispatcher->unregisterForcePrio(m_listLayer);
		touchDispatcher->unregisterForcePrio(this);
		setKeypadEnabled(false);
		removeFromParentAndCleanup(true);
	}
};