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
#include "Manager.hpp"
#include "Utils.hpp"

#define INFO_LABEL_TWEAKS "raydeeux.infolabeltweaks"
#define HARD_MODE "realluke.hard_mode"

using namespace geode::prelude;

$on_mod(Loaded) {
	listenForSettingChanges<bool>("enabled", [](bool enabled) {
		if (!Utils::isModLoaded(INFO_LABEL_TWEAKS)) return;
		const auto &infoLabelTweaks = Utils::getMod(INFO_LABEL_TWEAKS);
		if (enabled) {
			infoLabelTweaks->setSettingValue<bool>("blendingDebugText", false);
			infoLabelTweaks->setSettingValue<bool>("maxAlphaDebugText", true);
			infoLabelTweaks->setSettingValue<bool>("chromaDebugText", true);
			if (Utils::isModLoaded(HARD_MODE)) FLAlertLayer::create("Heads up!", "<cl>Realluke's Hard Mode</c> is loaded. Things will get really messy, but remember that <cr>you</c> signed up for this.\n\n--<cr>Tok</c><cj>Tik</c>Mode", "Close")->show();
		} else {
			const auto &manager = Manager::getSharedInstance();
			infoLabelTweaks->setSettingValue<bool>("blendingDebugText", manager->originalIsBlending);
			infoLabelTweaks->setSettingValue<bool>("maxAlphaDebugText", manager->originalMaxAlpha);
			infoLabelTweaks->setSettingValue<bool>("chromaDebugText", manager->originalIsChroma);
		}
	});
	listenForSettingChanges<bool>("tokTikUI", [](bool tokTikUI) {
		if (Utils::modEnabled() && tokTikUI && Utils::isModLoaded("realluke.hard_mode")) FLAlertLayer::create("Heads up!", "<cl>Realluke's Hard Mode</c> is loaded. Things will get really messy, but remember that <cr>you</c> signed up for this.\n\n--<cr>Tok</c><cj>Tik</c>Mode", "Close")->show();
	});
}