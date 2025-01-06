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

#include <Geode/modify/GameManager.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define INFO_LABEL_TWEAKS "raydeeux.infolabeltweaks"
#define PREFERRED_HOOK_PRIO (-4000)

using namespace geode::prelude;

class $modify(MyGameManager, GameManager) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("GameManager::encodeDataTo", PREFERRED_HOOK_PRIO);
	}
	void encodeDataTo(DS_Dictionary* dict) {
		if (!Utils::modEnabled() || !Utils::isModLoaded(INFO_LABEL_TWEAKS)) return GameManager::encodeDataTo(dict);
		const auto &manager = Manager::getSharedInstance();
		if (!manager->hasCalledAlready) return GameManager::encodeDataTo(dict);
		const auto &infoLabelTweaks = Utils::getMod(INFO_LABEL_TWEAKS);
		infoLabelTweaks->setSettingValue<bool>("blendingDebugText", manager->originalIsBlending);
		infoLabelTweaks->setSettingValue<bool>("maxAlphaDebugText", manager->originalMaxAlpha);
		infoLabelTweaks->setSettingValue<bool>("chromaDebugText", manager->originalIsChroma);
		GameManager::encodeDataTo(dict);
	}
};