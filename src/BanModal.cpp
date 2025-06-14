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

#ifndef GEODE_IS_MOBILE
#include "PlayLayer.hpp"
#include "BanModal.hpp"

using namespace geode::prelude;

BanModal* BanModal::create(bool welcomeBack) {
	auto *ret = new BanModal();
	if (ret && ret->init(welcomeBack)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool BanModal::init(bool welcomeBack) {
	FLAlertLayerProtocol* protocol = nullptr;
	if (const auto pl = PlayLayer::get()) protocol = static_cast<MyPlayLayer*>(pl)->m_fields.self();

	if (welcomeBack) return BanModal::initWelcomeBackInstead(protocol);

	if (!FLAlertLayer::init(protocol, BAN_MODAL_TITLE, BAN_MODAL_TEXT, " Learn ", " Close ", 255.f, false, 50.f, .59f)) return false;
	this->setID("BanModal");
	CCNode* titleFake = this->m_mainLayer->getChildByID("title");
	if (!titleFake) return true;

	const auto title = static_cast<CCLabelBMFont*>(titleFake);
	title->setFntFile("tokTikFontBold.fnt"_spr);
	title->limitLabelWidth(200.f, 0.9f, 0.001f);
	title->setAlignment(kCCTextAlignmentCenter);
	title->setColor({246, 246, 246});
	CCScale9Sprite* background = static_cast<CCScale9Sprite*>(m_mainLayer->getChildByID("background"));
	background->initWithFile("darkSquare.png"_spr);
	background->setContentSize({200.f, 220.f});

	m_buttonMenu->setScale(m_buttonMenu->getScale() * .6f);
	m_buttonMenu->setPosition({155.f, 8.f}); // hardcoded position, but this is an inherited alert layer, so go take a hike

	m_button1->m_label->setFntFile("tokTikFont.fnt"_spr);
	m_button1->m_label->setString("Learn more");
	m_button1->m_label->setColor({206, 206, 206});
	m_button1->m_BGSprite->setVisible(false);
	m_button2->m_label->setFntFile("tokTikFontBold.fnt"_spr);
	m_button2->m_label->setString("Close app");
	m_button2->m_BGSprite->setVisible(false);
	m_button2->m_label->setColor({246, 246, 246});

	if (const auto textArea = m_mainLayer->getChildByType<TextArea>(0)) {
		textArea->setPositionY(textArea->getPositionY() - 15.f);
		textArea->setPositionX(TEXTAREA_X_POS);
		for (CCLabelBMFont* label : CCArrayExt<CCLabelBMFont*>(textArea->getChildByType<MultilineBitmapFont>(0)->m_lines)) {
			label->setFntFile("tokTikFont.fnt"_spr);
			label->setColor({206, 206, 206});
		}
	}

	this->setTag(20250119);
	this->m_noElasticity = true;

	return true;
}

bool BanModal::initWelcomeBackInstead(FLAlertLayerProtocol* protocol) {
	if (!FLAlertLayer::init(protocol, WELCOME_BACK_TITLE, WELCOME_BACK_TEXT, " Contu ", nullptr, 255.f, false, 50.f, .59f)) return false;

	this->setID("BanModal");
	CCNode* titleFake = this->m_mainLayer->getChildByID("title");
	if (!titleFake) return true;

	const auto title = static_cast<CCLabelBMFont*>(titleFake);
	title->setFntFile("tokTikFontBold.fnt"_spr);
	title->limitLabelWidth(200.f, 0.9f, 0.001f);
	title->setAlignment(kCCTextAlignmentCenter);
	title->setPositionY(192.3f);
	title->setColor({246, 246, 246});
	CCScale9Sprite* background = static_cast<CCScale9Sprite*>(m_mainLayer->getChildByID("background"));
	background->initWithFile("darkSquare.png"_spr);
	background->setContentSize({200.f, 300.f});

	m_buttonMenu->setScale(m_buttonMenu->getScale() * .6f);
	m_buttonMenu->setPosition({155.f, -30.f});

	m_button1->m_label->setFntFile("tokTikFont.fnt"_spr);
	m_button1->m_label->setString("Continue");
	m_button1->m_label->setColor({206, 206, 206});
	m_button1->m_BGSprite->setVisible(false);

	CCSprite* welcomeBackSprite = CCSprite::create("welcomeBack.png"_spr);
	welcomeBackSprite->setPosition({title->getPositionX(), 246.f});
	welcomeBackSprite->setScale(.65f);
	welcomeBackSprite->setID("welcome-back-sprite"_spr);
	welcomeBackSprite->setZOrder(title->getZOrder() + 1);
	m_mainLayer->addChild(welcomeBackSprite);

	if (const auto textArea = m_mainLayer->getChildByType<TextArea>(0)) {
		textArea->setPosition({TEXTAREA_X_POS, 106.f});
		for (CCLabelBMFont* label : CCArrayExt<CCLabelBMFont*>(textArea->getChildByType<MultilineBitmapFont>(0)->m_lines)) {
			label->setFntFile("tokTikFont.fnt"_spr);
			label->setColor({206, 206, 206});
		}
	}

	this->m_noElasticity = true;

	return true;
}


void BanModal::keyBackClicked() {
	this->removeMeAndCleanup();
}
#endif