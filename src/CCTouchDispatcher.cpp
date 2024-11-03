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

/* Source code contributed by Alphalaneous, and adapted to fit my codestyle as well as fixing any bugs. --Erymanthus */

#include <Geode/modify/CCTouchDispatcher.hpp>
#include "PlayLayer.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyCCTouchDispatcher, CCTouchDispatcher) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("cocos2d::CCTouchDispatcher::touches", MAGIC_NUMBER);
	}
	CCPoint scalePointAroundCenter(const CCPoint& point, const CCPoint& center, float scaleFactor) {
		CCPoint translatedPoint = point - center;
		translatedPoint.x *= scaleFactor;
		translatedPoint.y *= scaleFactor;
		CCPoint scaledPoint = translatedPoint + center;
		return scaledPoint;
	}
	void touches(CCSet* touches, CCEvent* event, unsigned int type) {
		auto* touch = static_cast<CCTouch*>(touches->anyObject());
		if (!touch) return;

		if (!Utils::modEnabled()) return CCTouchDispatcher::touches(touches, event, type);

		PlayLayer* pl = PlayLayer::get();
		if (!pl) return CCTouchDispatcher::touches(touches, event, type);
		if (pl->m_level->isPlatformer() && Utils::getBool("disableOnPlatformer")) return CCTouchDispatcher::touches(touches, event, type);
		if (!pl->m_level->isPlatformer() && Utils::getBool("disableOnClassic")) return CCTouchDispatcher::touches(touches, event, type);

		MyPlayLayer* mpl = static_cast<MyPlayLayer*>(pl);
		if (!mpl->m_fields->m_initialized) return CCTouchDispatcher::touches(touches, event, type);

		CCPoint pos = touch->getLocation();
		if (!mpl->m_fields->m_renderTo->boundingBox().containsPoint(pos) && mpl->m_fields->m_blackOverlay->boundingBox().containsPoint(pos)) {
			bool isPausedOrPauseLayer = pl->m_isPaused || getChildOfType<PauseLayer>(CCScene::get(), 0);
			if (Utils::getBool("ignoreOOBTouchesDuringGP") && !isPausedOrPauseLayer) return;
			if (isPausedOrPauseLayer) return;
		} else if (!mpl->m_fields->m_renderTo->boundingBox().containsPoint(pos)) return CCTouchDispatcher::touches(touches, event, type);

		mpl->setVisible(true);
		CCSize winSize = CCDirector::get()->getWinSize();
		CCPoint center = winSize / 2.f;

		float scale = mpl->m_fields->m_renderTo->getScale();

		pos.y = winSize.height - pos.y;
		pos = scalePointAroundCenter(pos, center, 1 / scale);

		CCPoint newPos = pos.rotateByAngle(center, CC_DEGREES_TO_RADIANS(mpl->m_fields->m_degrees));
		newPos.y = winSize.height - newPos.y;
		newPos.x = winSize.width - newPos.x;

		touch->setTouchInfo(touch->getID(), newPos.x, newPos.y);
		CCTouchDispatcher::touches(touches, event, type);

		mpl->setVisible(false);
	}
};