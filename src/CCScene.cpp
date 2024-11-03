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

/* Source code contributed by Alphalaneous, and adapted to fit my codestyle. --Erymanthus */

#include <Geode/modify/CCScene.hpp>
#include "PlayLayer.hpp"

using namespace geode::prelude;

class $modify(MyCCScene, CCScene) {
	int getHighestChildZ() {
		PlayLayer* pl = PlayLayer::get();
		if (!pl) return CCScene::getHighestChildZ();
		if (pl->m_level->isPlatformer() && Utils::getBool("disableOnPlatformer")) return CCScene::getHighestChildZ();
		if (!pl->m_level->isPlatformer() && Utils::getBool("disableOnClassic")) return CCScene::getHighestChildZ();

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