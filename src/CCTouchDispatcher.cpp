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

		MyPlayLayer* mpl = static_cast<MyPlayLayer*>(pl);
		if (!mpl->m_fields->m_initialized) return CCTouchDispatcher::touches(touches, event, type);

		mpl->setVisible(true);
		CCSize winSize = CCDirector::get()->getWinSize();
		CCPoint center = winSize / 2.f;

		CCPoint pos = touch->getLocation();

		if (!mpl->m_fields->m_renderTo->boundingBox().containsPoint(pos)) return CCTouchDispatcher::touches(touches, event, type);

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