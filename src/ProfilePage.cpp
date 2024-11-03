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

#include <Geode/modify/ProfilePage.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-2123456789)

using namespace geode::prelude;

class $modify(MyProfilePage, ProfilePage) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("ProfilePage::onMyLevels", PREFERRED_HOOK_PRIO);
		(void) self.setHookPriority("ProfilePage::onMyLists", PREFERRED_HOOK_PRIO);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void onMyLevels(cocos2d::CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return ProfilePage::onMyLevels(sender);
		Utils::showGuardrailAlert();
	}
	void onMyLists(cocos2d::CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return ProfilePage::onMyLists(sender);
		Utils::showGuardrailAlert();
	}
	void setupCommentsBrowser(cocos2d::CCArray* p0) {
		ProfilePage::setupCommentsBrowser(p0);
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return;
		Utils::showFirstTimeAlert();
	}
};