/*
This file is part of TokTikMode.

TokTikMode is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with TokTikMode; if not, see
<https://www.gnu.org/licenses/>.
*/

/* Source code is self-authored, with help from
hiimjustin000 for re-creating vanilla GD behavior. --Erymanthus */

#include <Geode/modify/FriendsProfilePage.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define MAGIC_NUMBER (-4000)

class $modify(MyFriendsProfilePage, FriendsProfilePage) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("FriendsProfilePage::setupUsersBrowser", MAGIC_NUMBER);
		(void) self.setHookPriority("FriendsProfilePage::onClose", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void onClose(CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return FriendsProfilePage::onClose(sender);
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
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return;
		Utils::showFirstTimeAlert();
	}
};