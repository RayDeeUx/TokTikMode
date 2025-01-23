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

/* Source code is self-authored. --Erymanthus */

#include <Geode/modify/MenuLayer.hpp>
#include "Manager.hpp"

#define PREFERRED_HOOK_PRIO (-3999)

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		Manager* manager = Manager::getSharedInstance();
		if (manager->hasCalledAlready) return true;
		manager->hasCalledAlready = true;

		const int& userID = GameManager::get()->m_playerUserID.value();
		// uproxide wanted me to replace "trump" with "topala"
		// (understandably so, for reasons i wont explain here)
		// she requested this from me several times in #dev-chat
		// therefore this is not targeted harassment
		// the other userID is me btw
		// user IDs obtained from https://gdbrowser.com profiles
		// please have mercy
		manager->presidentName = userID != 227796112 && userID != 10709102 ? "Trump" : "Topala";
		
		return true;
	}
};