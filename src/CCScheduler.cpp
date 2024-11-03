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