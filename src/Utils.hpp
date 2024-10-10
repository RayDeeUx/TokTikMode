#pragma once

#include <Geode/utils/web.hpp>

#define PI 3.14159265
#define KABBA_LATITUDE 21.4225046
#define KABBA_LONGITUDE 39.8261148

using namespace geode::prelude;

namespace Utils {
	template<class T> T getSetting(const std::string_view setting);
	bool getBool(const std::string_view setting);
	int64_t getInt(const std::string_view setting);
	double getDouble(const std::string_view setting);
	std::string getString(const std::string_view setting);
	ccColor3B getColor(const std::string_view setting);
	ccColor4B getColorAlpha(const std::string_view setting);
	bool modEnabled();
	
	bool isModLoaded(const std::string &modID);
	Mod* getMod(const std::string &modID);
	std::string getModVersion(Mod* mod);

	double findBearing(double latitude = KABBA_LATITUDE * PI / 180, double longitude = KABBA_LONGITUDE * PI / 180);
	void findBearingWebAPI(double userLatitude, double userLongitude);
	void showBearing();
	int getRandInt(int min = 0, int max = 5);
}