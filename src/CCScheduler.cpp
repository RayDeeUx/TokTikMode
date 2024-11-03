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

/* Source code contributed by Alphalaneous, and adapted to fit my codestyle. --Erymanthus */

#include <Geode/modify/CCScheduler.hpp>
#include "PlayLayer.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyCCScheduler, CCScheduler) {
	void update(float dt) {
		if (!Utils::modEnabled()) return CCScheduler::update(dt);

		PlayLayer* pl = PlayLayer::get();
		if (!pl) return CCScheduler::update(dt);
		if (pl->m_level->isPlatformer() && Utils::getBool("disableOnPlatformer")) return CCScheduler::update(dt);
		if (!pl->m_level->isPlatformer() && Utils::getBool("disableOnClassic")) return CCScheduler::update(dt);

		MyPlayLayer* mpl = static_cast<MyPlayLayer*>(pl);

		mpl->applyWinSize();
		CCScheduler::update(dt);
		mpl->restoreWinSize();
	}
};