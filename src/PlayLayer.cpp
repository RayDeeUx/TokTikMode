#include <Geode/modify/PlayLayer.hpp>
#include "Utils.hpp"
#define MAGIC_NUMBER (-2123456789)
#define OTHER_MAGIC_NUMBER (-MAGIC_NUMBER / 30000)

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("PlayLayer::postUpdate", MAGIC_NUMBER);
	}
	struct Fields {
		CCSize winSize = PlayLayer::get()->getContentSize();
		float winWidth = winSize.width;
		float winHeight = winSize.height;
		bool rotated = false;
	};
	CCSprite* createFooter() {
		CCSprite* footer = CCSprite::create("footer.png"_spr);
		footer->setID("footer"_spr);
		footer->setPosition({
			m_fields->winWidth / 2.f,
			(-m_fields->winHeight) + (2.f * footer->getContentHeight())
		});
		footer->setScale(m_fields->winWidth / footer->getContentWidth());
		footer->setZOrder(OTHER_MAGIC_NUMBER);
		return footer;
	}
	CCSprite* createActions() {
		CCSprite* actions = CCSprite::create("actions.png"_spr);
		actions->setID("actions"_spr);
		actions->setPosition({
			m_fields->winWidth - (actions->getContentWidth() * 3.10f),
			0
		});
		actions->setScale((actions->getContentWidth() / m_fields->winWidth) * 125.f);
		actions->setZOrder(OTHER_MAGIC_NUMBER);
		return actions;
	}
	CCSprite* createForYou() {
		CCSprite* forYou = CCSprite::create("followingAndFYP.png"_spr);
		forYou->setID("for-you"_spr);
		forYou->setPosition({
			m_fields->winWidth / 2.f,
			m_fields->winWidth + (forYou->getContentHeight())
		});
		forYou->setScale((forYou->getContentWidth() / m_fields->winWidth) * 40.f);
		forYou->setZOrder(OTHER_MAGIC_NUMBER);
		return forYou;
	}
	CCSprite* createSearch() {
		CCSprite* search = CCSprite::create("search.png"_spr);
		auto scene = CCScene::get();
		search->setID("search"_spr);
		search->setPosition({
			scene->getChildByID("actions"_spr)->getPositionX() + 20.f,
			scene->getChildByID("for-you"_spr)->getPositionY() + 10.f,
		});
		search->setScale(scene->getChildByID("for-you"_spr)->getScale() * 0.85f);
		search->setZOrder(OTHER_MAGIC_NUMBER);
		return search;
	}
	CCSprite* createLive() {
		CCSprite* live = CCSprite::create("live.png"_spr);
		auto scene = CCScene::get();
		live->setID("live"_spr);
		live->setPosition({
			35.f,
			scene->getChildByID("for-you"_spr)->getPositionY() + 10.f,
		});
		live->setScale(scene->getChildByID("for-you"_spr)->getScale() * 0.85f);
		live->setZOrder(OTHER_MAGIC_NUMBER);
		return live;
	}
	CCSprite* createBottomBar() {
		CCSprite* bottomBar = CCSprite::create("bar.png"_spr);
		bottomBar->setID("bottom-bar"_spr);
		bottomBar->setAnchorPoint({0.5f, 1.f});
		bottomBar->setPosition({
			m_fields->winWidth / 2.f,
			0
		});
		bottomBar->setScale(m_fields->winWidth);
		bottomBar->setZOrder(OTHER_MAGIC_NUMBER - 1);
		bottomBar->setColor(ccColor3B(0,0,0));
		return bottomBar;
	}
	CCSprite* createTopBar() {
		CCSprite* topBar = CCSprite::create("bar.png"_spr);
		topBar->setID("top-bar"_spr);
		topBar->setAnchorPoint({0.5f, 0.f});
		topBar->setPosition({
			m_fields->winWidth / 2.f,
			m_fields->winHeight
		});
		topBar->setScale(m_fields->winWidth);
		topBar->setZOrder(OTHER_MAGIC_NUMBER - 1);
		topBar->setColor(ccColor3B(0,0,0));
		return topBar;
	}
	void postUpdate(float p0) {
		PlayLayer::postUpdate(p0);
		auto degrees = utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0);
		auto scene = CCScene::get();
		if (m_fields->rotated && scene->getRotation() == static_cast<float>(degrees)) return;
		if (degrees == 0) {
			m_fields->rotated = true;
			return;
		}
		if (!scene) return;
		if (const auto sprite = createBottomBar()) scene->addChild(sprite);
		if (const auto sprite = createTopBar()) scene->addChild(sprite);
		if (Utils::getBool("tiktokUI")) {
			if (const auto footer = createFooter()) scene->addChild(footer);
			if (const auto actions = createActions()) scene->addChild(actions);
			if (const auto forYou = createForYou()) scene->addChild(forYou);
			if (const auto search = createSearch()) scene->addChild(search);
			if (const auto live = createLive()) scene->addChild(live);
			std::string desc = "No";
			auto descLabel = CCLabelBMFont::create();
			// desc.c_str(), "tokTikFont.fnt"_spr, m_fields->winWidth * 0.35f, kCCTextAlignmentLeft
			descLabel->setString(desc.c_str());
			descLabel->setFntFile("tokTikFont.fnt");
			scene->addChild(descLabel);
		}
		scene->setRotation(static_cast<float>(degrees));
		scene->setScale(m_fields->winHeight / m_fields->winWidth);
		m_fields->rotated = true;
	}
};