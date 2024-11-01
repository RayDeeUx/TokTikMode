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
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("footerMenu") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return MessagesProfilePage::onClose(sender);
		auto touchDispatcher = CCTouchDispatcher::get();
		if (m_listLayer) touchDispatcher->unregisterForcePrio(m_listLayer);
		touchDispatcher->unregisterForcePrio(this);
		untoggleAll();
		setKeypadEnabled(false);
		removeFromParentAndCleanup(true);
		m_fields->manager->senderTag = -1;
	}
	void setupCommentsBrowser(cocos2d::CCArray* p0) {
		MessagesProfilePage::setupCommentsBrowser(p0);
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("footerMenu") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return;
		if (!m_mainLayer) return log::info("node was not found: mainLayer");
		const auto &gjcll = getChildOfType<GJCommentListLayer>(m_mainLayer, 0);
		if (!gjcll) return log::info("node was not found: gjcll");
		const auto &cll = getChildOfType<CustomListView>(gjcll, 0);
		if (!cll || !cll->m_tableView) return log::info("node was not found: cll OR cll->m_tableView");
		const auto &cccl = cll->m_tableView->m_contentLayer;
		if (!cccl) return log::info("node was not found: cccl");
		gjcll->setColor(ccColor3B({0,0,0});
		gjcll->setOpacity(0);
		gjcll->setPositionX(480.f);
		for (const auto &node : CCArrayExt<CCNode*>(gjcll->getChildren())) {
			if (const auto &sprite = typeinfo_cast<CCSprite*>(node); cocos::isSpriteFrameName(sprite, "GJ_commentTop_001.png") || cocos::isSpriteFrameName(sprite, "GJ_commentSide_001.png")) {
				sprite->setVisible(false);
			}
		}
		cccl->setPositionX(cccl->getPositionX() - 360.f);
	}
};