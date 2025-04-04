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

/* Source code contributed by acaruso from many moons ago,
with extreme amounts of encouragement and explicit permission for re-use. --Erymanthus */

#pragma once

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:
	int senderTag = -1;

	bool hasCalledAlready = false;

	bool originalIsBlending = false;
	bool originalIsChroma = false;
	bool originalMaxAlpha = false;

	std::string presidentName = "Trump";

	static Manager* getSharedInstance() {
		if (!instance) {
			instance = new Manager();
		}
		return instance;
	}

};