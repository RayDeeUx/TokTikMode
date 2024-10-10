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

	double findBearing(double latitude, double longitude) {
		const auto userLatitude = static_cast<float>(Utils::getDouble("userLatitude")) * PI / 180;
		const auto userLongitude = static_cast<float>(Utils::getDouble("userLongitude")) * PI / 180;

		const auto crudeBearing = 180.0 * atan2(
			sin(longitude - userLongitude) * cos(latitude),
			cos(userLatitude) * sin(latitude) - sin(userLatitude) * cos(latitude) * cos(longitude - userLongitude)
		) / PI;

		int bearing = static_cast<int>(crudeBearing + 360.0);
		double bearingDecimal = 0.0;
		std::string crudeBearingAsString = fmt::format("{}", crudeBearing);
		std::string crudeBearingTrailingDecimal;

		// regex: ^-?[\d]+([\.\,]\d*)?$
		// url: https://regex101.com/r/uop2Q8/1

		std::smatch match;
		bool matches = std::regex_match(crudeBearingAsString, match, decimalPointsRegex);
		if (matches && !match.empty() && match.size() == 2) {
			log::info("\noriginal: {}\nmatch[1].str(): {}", crudeBearing, match[1].str());
			crudeBearingTrailingDecimal = match[1].str();
			auto crudeAsResult = utils::numFromString<double>(crudeBearingTrailingDecimal);
			bearingDecimal = crudeAsResult.unwrapOr(0.0);
		}

		bearing = bearing % 360;

		float result = -1.0;

		if (crudeBearing < 0) {
			result = bearing - bearingDecimal;
		} else if (crudeBearing > 0) {
			result = bearing + bearingDecimal;
		} else {
			result = bearing;
		}

		Manager::getSharedInstance()->direction = result;
		return result;
	}

	void findBearingWebAPI(double userLatitude = getDouble("userLatitude"), double userLongitude = getDouble("userLongitude")) {
		if (!Utils::modEnabled()) return;
		const auto manager = Manager::getSharedInstance();
		const auto gm = GameManager::get();
		std::string chosenUserAgent = fmt::format("GeometryDash/{}/Geode/{}/{}/QiblaFinder/{}/{}/{}", manager->gameVer, manager->platformName, manager->loaderVer, manager->modVer, gm->m_playerName, gm->m_bootups);
		const int randInt = getRandInt();
		// TODO: mimickery of Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:128.0) Gecko/20100101 Firefox/128.0
		if (randInt == 1) {
			chosenUserAgent = fmt::format("QiblaFinder/{} (Geode; {} {}; {}:{}) GeometryDash/{}", manager->modVer, manager->platformName, manager->loaderVer, gm->m_playerName, gm->m_bootups, manager->gameVer);
		} else if (randInt == 2) {
			chosenUserAgent = fmt::format("{} ({} bootup(s)) using QiblaFinder v{} on {}, Geode v{} and GeometryDash v{}", gm->m_playerName, gm->m_bootups, manager->modVer, manager->platformName, manager->loaderVer, manager->gameVer);
		} else if (randInt == 3) {
			chosenUserAgent = fmt::format("QiblaFinder v{}, Geode v{} ({}), GeometryDash v{}, {} v{}", manager->modVer, manager->loaderVer, manager->platformName, manager->gameVer, gm->m_playerName, gm->m_bootups);
		} else if (randInt == 4) {
			chosenUserAgent = fmt::format("{}/{} geode.loader/{} robtop.geometrydash/{}_{} {}/{}", Mod::get()->getID(), manager->modVer, manager->modVer, manager->platformName, manager->gameVer, gm->m_playerName, gm->m_bootups);
		} else if (randInt != 0) {
			chosenUserAgent = "";
		}
		log::info("=== user agent debug info ===\nchosen user agent string:\n\t{}\nrandInt:\t{}", chosenUserAgent, randInt);
		auto req = web::WebRequest();

		req.userAgent(chosenUserAgent);

		req.header("Content-Type", "application/json");
		req.timeout(std::chrono::seconds(5));

		std::string formattedURL = fmt::format("https://api.aladhan.com/v1/qibla/{}/{}", userLatitude, userLongitude);

		req.get(formattedURL).listen([] (web::WebResponse* res) {
			auto manager = Manager::getSharedInstance();
			manager->requestFailed = true;
			if (!res->ok() || res->code() != 200) {
				log::info("res->code(): {}", res->code());
				manager->direction = Utils::findBearing();
				return;
			}
			log::info("success?");
			auto str = res->string().value_or("");
			if (str.empty()) {
				log::info("tried parsing web response and got empty string instead.");
				manager->direction = Utils::findBearing();
				return;
			}
			std::string error;
			auto json = matjson::parse(str, error).value_or(matjson::Object());
			if (!json.contains("code") || json.try_get("code").value().get().as_int() != 200) {
				log::info("error parsing JSON. begin json below:\n====\n{}\n====", str);
				manager->direction = Utils::findBearing();
				return;
			}
			if (json.try_get("data").has_value()) {
				auto dataConfirmed = json.get<matjson::Object>("data");
				if (!dataConfirmed.contains("direction")) {
					log::info("json is valid and \"data\" key exists, however there is no \"direction\" key:\n====\n{}\n====", str);
					manager->direction = Utils::findBearing();
					return;
				}
				log::info("json is valid, \"data\" key exists, and \"direction\" key exists:\n====\n{}\n====", str);
				manager->direction = dataConfirmed.find("direction")->second.as_double();
				manager->requestFailed = false;
				return;
			}
			log::info("json is valid, however there is no \"data\" key::\n====\n{}\n====", str);
			manager->direction = Utils::findBearing();
		}, [](auto p) {
			log::info("web request in progress.");
		}, []() {
			log::info("web request cancelled.");
			Manager::getSharedInstance()->direction = Utils::findBearing();
		});

	}

	void showBearing() {
		if (!Utils::modEnabled()) return;
		const auto manager = Manager::getSharedInstance();
		const bool useAPI = Utils::getBool("useAPI");
		if (useAPI) Utils::findBearingWebAPI(Utils::getDouble("userLatitude"), Utils::getDouble("userLongitude"));
		float bearing = Utils::findBearing();
		if (useAPI) bearing = manager->direction;
		if (bearing == -1.0f) return;
		std::string result = fmt::format("The absolute bearing of The Kabba is <cj>{:.2f} degrees</c> from your coordinates <cl>({:.2f}, {:.2f})</c>.", bearing, Utils::getDouble("userLatitude"), Utils::getDouble("userLongitude"));
		if (!useAPI) result = result.append("\n<cy>This calculation was done locally, and may be inaccurate by roughly 1 degree.</c>\n<cy>AlAdhan API access is</c> <cr>not</c> <cy>enabled.</c>");
		else if (manager->requestFailed && useAPI) result = result.append("\n<cy>This calculation was done locally, and may be inaccurate by roughly 1 degree.</c>\n<cy>AlAdhan API access is currently</c> <cr>unavailable</c><cy>.</c>");
		FLAlertLayer::create("QiblaFinder", result, "OK")->show();
	}

	int getRandInt(int min, int max) {
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> uni(min,max);

		return uni(rng);
	}
}
