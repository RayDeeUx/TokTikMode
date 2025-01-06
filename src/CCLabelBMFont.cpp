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
#include <Geode/modify/CCLabelBMFont.hpp>
#include "Utils.hpp"

#define MAGIC_NUMBER (-4000)

using namespace geode::prelude;

class $modify(MyCCLabelBMFont, CCLabelBMFont) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("CCLabelBMFont::setBlendFunc", MAGIC_NUMBER);
	}
	void setBlendFunc(ccBlendFunc blendFunc) {
		if (!Utils::modEnabled() || !PlayLayer::get()) return CCLabelBMFont::setBlendFunc(blendFunc);
		if (this->getID().empty() || !utils::string::startsWith(this->getID(), "raydeeux")) return CCLabelBMFont::setBlendFunc(blendFunc);
		if (blendFunc.src == GL_ONE_MINUS_DST_COLOR && blendFunc.dst == GL_ONE_MINUS_SRC_ALPHA) return CCLabelBMFont::setBlendFunc({});
		return CCLabelBMFont::setBlendFunc(blendFunc);
	}
};