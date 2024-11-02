#include <Geode/modify/CommentCell.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-2123456789)

using namespace geode::prelude;

class $modify(MyCommentCell, CommentCell) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("CommentCell::onGoToLevel", PREFERRED_HOOK_PRIO);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void onGoToLevel(cocos2d::CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooter") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return CommentCell::onGoToLevel(sender);
		Utils::showGuardrailAlert();
	}
};