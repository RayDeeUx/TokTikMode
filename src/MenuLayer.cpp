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
#include "Utils.hpp"

#define INFO_LABEL_TWEAKS "raydeeux.infolabeltweaks"
#define PREFERRED_HOOK_PRIO (-2123456789)

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		Manager* manager = Manager::getSharedInstance();
		
		if (manager->hasCalledAlready) return true;
		manager->hasCalledAlready = true;

		const auto &infoLabelTweaks = Utils::getMod(INFO_LABEL_TWEAKS);
		manager->originalIsBlending = infoLabelTweaks->getSettingValue<bool>("blendingDebugText");
		manager->originalMaxAlpha = infoLabelTweaks->getSettingValue<bool>("maxAlphaDebugText");
		manager->originalIsChroma = infoLabelTweaks->getSettingValue<bool>("chromaDebugText");
		
		return true;
	}
};