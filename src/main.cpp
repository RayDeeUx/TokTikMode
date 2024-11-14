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

#include <Geode/loader/SettingV3.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define INFO_LABEL_TWEAKS "raydeeux.infolabeltweaks"

using namespace geode::prelude;

$on_mod(Loaded) {
	listenForSettingChanges<bool>("enabled", [](bool enabled) {
		if (!Utils::isModLoaded(INFO_LABEL_TWEAKS)) return;
		const auto &infoLabelTweaks = Utils::getMod(INFO_LABEL_TWEAKS);
		if (enabled) {
			infoLabelTweaks->setSettingValue<bool>("blendingDebugText", false);
			infoLabelTweaks->setSettingValue<bool>("maxAlphaDebugText", true);
			infoLabelTweaks->setSettingValue<bool>("chromaDebugText", true);
		} else {
			const auto &manager = Manager::getSharedInstance();
			infoLabelTweaks->setSettingValue<bool>("blendingDebugText", manager->originalIsBlending);
			infoLabelTweaks->setSettingValue<bool>("maxAlphaDebugText", manager->originalMaxAlpha);
			infoLabelTweaks->setSettingValue<bool>("chromaDebugText", manager->originalIsChroma);
		}
	});
}

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		const auto &manager = Manager::getSharedInstance();
		if (manager->hasCalledAlready) return true;
		manager->hasCalledAlready = true;

		if (!Utils::isModLoaded(INFO_LABEL_TWEAKS)) return true;

		const auto &infoLabelTweaks = Utils::getMod(INFO_LABEL_TWEAKS);

		manager->originalIsBlending = infoLabelTweaks->getSettingValue<bool>("blendingDebugText");
		manager->originalMaxAlpha = infoLabelTweaks->getSettingValue<bool>("maxAlphaDebugText");
		manager->originalIsChroma = infoLabelTweaks->getSettingValue<bool>("chromaDebugText");

		return true;
	}
};