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
License along with this library; if not, see
<https://www.gnu.org/licenses/>.
*/

/* Source code is self-authored. --Erymanthus */

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
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get() || m_fields->manager->senderTag == -1) return CommentCell::onGoToLevel(sender);
		Utils::showGuardrailAlert();
	}
};