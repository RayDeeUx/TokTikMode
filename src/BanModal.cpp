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

#include "PlayLayer.hpp"
#include "BanModal.hpp"

using namespace geode::prelude;

BanModal* BanModal::create() {
	auto *ret = new BanModal();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool BanModal::init() {
	FLAlertLayerProtocol* delegate = nullptr;
	if (const auto pl = PlayLayer::get()) delegate = static_cast<MyPlayLayer*>(pl)->m_fields.self();
	if (!FLAlertLayer::init(delegate, BAN_MODAL_TITLE, BAN_MODAL_TEXT, " Learn ", " Close ", 255.f, false, 50.f, .69f)) return false;
	this->setID("BanModal");
	CCNode* titleFake = this->m_mainLayer->getChildByID("title");
	if (!titleFake) return true;

	const auto title = static_cast<CCLabelBMFont*>(titleFake);
	title->setFntFile("tokTikFontBold.fnt"_spr);
	title->limitLabelWidth(200.f, 0.9f, 0.001f);
	title->setAlignment(kCCTextAlignmentCenter);
	static_cast<CCScale9Sprite*>(m_mainLayer->getChildByID("background"))->setContentWidth(200.f);

	m_buttonMenu->setScale(m_buttonMenu->getScale() * .6f);
	m_buttonMenu->setPosition({152.f, 0.f});

	m_button1->m_label->setFntFile("tokTikFont.fnt"_spr);
	m_button1->m_label->setString("Learn more");
	m_button2->m_label->setFntFile("tokTikFontBold.fnt"_spr);
	m_button2->m_label->setString("Close app");

	if (const auto textArea = m_mainLayer->getChildByType<TextArea>(0)) textArea->setPositionY(textArea->getPositionY() - 15.f);

	this->setTag(20250119);

	return true;
}