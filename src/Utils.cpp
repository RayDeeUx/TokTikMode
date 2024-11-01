#include "Utils.hpp"
#include <cmath>
#include <regex>
#include <random>

#include "Manager.hpp"

static const std::regex decimalPointsRegex(R"(^-?[\d]+([\.\,]\d*)?$)", std::regex::optimize | std::regex::icase);

namespace Utils {

	template<class T> T getSetting(const std::string_view setting) { return Mod::get()->getSettingValue<T>(setting); }

	bool getBool(const std::string_view setting) { return getSetting<bool>(setting); }
	
	int64_t getInt(const std::string_view setting) { return getSetting<int64_t>(setting); }
	
	double getDouble(const std::string_view setting) { return getSetting<double>(setting); }

	std::string getString(const std::string_view setting) { return getSetting<std::string>(setting); }

	ccColor3B getColor(const std::string_view setting) { return getSetting<ccColor3B>(setting); }

	ccColor4B getColorAlpha(const std::string_view setting) { return getSetting<ccColor4B>(setting); }

	bool modEnabled() { return getBool("enabled"); }
	
	bool isModLoaded(const std::string &modID) { return Loader::get()->isModLoaded(modID); }

	Mod* getMod(const std::string &modID) { return Loader::get()->getLoadedMod(modID); }

	std::string getModVersion(const Mod* mod) { return mod->getVersion().toNonVString(); }

	int getRandInt(int min, int max) {
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> uni(min,max);

		return uni(rng);
	}

	void showGuardrailAlert() {
		if (!PlayLayer::get()) return;
		FLAlertLayer::create(
			"Warning",
			"You must <cr>EXIT</c> the level to proceed.\n\n--<cj>Tok</c><cr>Tik</c>Mode",
			"Ok"
		)->show();
	}

	void showFirstTimeAlert() {
		if (!PlayLayer::get()) return;
		const auto &priorAlert = getChildOfType<FLAlertLayer>(CCScene::get(), -1);
		if (priorAlert && priorAlert->m_button1) {
			if (std::string(priorAlert->m_button1->m_label->getString()) == "Alright") return;
		}
		FLAlertLayer::create(
			"Warning",
			"Hey there! You're not really supposed to view this menu under these circumstances. The button was made interactive for fun, and nothing more.\n\n--<cj>Tok</c><cr>Tik</c>Mode",
			"Alright"
		)->show();
	}


}
