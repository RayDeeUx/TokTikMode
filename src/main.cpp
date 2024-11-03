#include <Geode/loader/SettingEvent.hpp>
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