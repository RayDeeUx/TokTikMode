#include <Geode/modify/PlayLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"
#include <random>
#define MAGIC_NUMBER (-2123456789)
#define OTHER_MAGIC_NUMBER (-MAGIC_NUMBER / 30000)

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("PlayLayer::postUpdate", MAGIC_NUMBER);
	}
	struct Fields {
		bool rotated = false;
		bool hasRotationOrScale = false;
		Manager* manager = Manager::getSharedInstance();
		std::vector<int> compatibilityMode {1346, 2067};
	};
	CCSprite* createFooter() {
		CCSprite* footer = CCSprite::create("footer.png"_spr);
		footer->setID("footer"_spr);
		footer->setPosition({
			m_fields->manager->winWidth / 2.f,
			(-m_fields->manager->winHeight) + (2.f * footer->getContentHeight())
		});
		footer->setScale(m_fields->manager->winWidth / footer->getContentWidth());
		footer->setZOrder(OTHER_MAGIC_NUMBER);
		return footer;
	}
	CCSprite* createActions() {
		CCSprite* actions = CCSprite::create("actions.png"_spr);
		actions->setID("actions"_spr);
		actions->setPosition({
			m_fields->manager->winWidth - (actions->getContentWidth() * 3.10f),
			0
		});
		actions->setScale((actions->getContentWidth() / m_fields->manager->winWidth) * 125.f);
		actions->setZOrder(OTHER_MAGIC_NUMBER);
		return actions;
	}
	CCSprite* createForYou() {
		CCSprite* forYou = CCSprite::create("followingAndFYP.png"_spr);
		forYou->setID("for-you"_spr);
		forYou->setPosition({
			m_fields->manager->winWidth / 2.f,
			m_fields->manager->winWidth + (forYou->getContentHeight())
		});
		forYou->setScale((forYou->getContentWidth() / m_fields->manager->winWidth) * 40.f);
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
			m_fields->manager->winWidth / 2.f,
			0
		});
		bottomBar->setScale(m_fields->manager->winWidth);
		bottomBar->setZOrder(OTHER_MAGIC_NUMBER - 1);
		bottomBar->setColor({0, 0, 0});
		return bottomBar;
	}
	CCSprite* createTopBar() {
		CCSprite* topBar = CCSprite::create("bar.png"_spr);
		topBar->setID("top-bar"_spr);
		topBar->setAnchorPoint({0.5f, 0.f});
		topBar->setPosition({
			m_fields->manager->winWidth / 2.f,
			m_fields->manager->winHeight
		});
		topBar->setScale(m_fields->manager->winWidth);
		topBar->setZOrder(OTHER_MAGIC_NUMBER - 1);
		topBar->setColor({0, 0, 0});
		return topBar;
	}
	CCLabelBMFont* createDescLabel() {
		std::string desc = "[This level's description does not follow TokTik's Community Guidelines, which help us foster an inclusive and authentic community and define the kind of content and behavior that's not allowed on our app.]";
		if (m_level && !m_level->getUnpackedLevelDescription().empty()) desc = m_level->getUnpackedLevelDescription();
		const auto descLabel = CCLabelBMFont::create(desc.c_str(), "tokTikFont.fnt"_spr, m_fields->manager->winWidth * 0.75f, kCCTextAlignmentLeft);
		descLabel->setScale(0.75f);
		descLabel->setZOrder(OTHER_MAGIC_NUMBER);
		descLabel->setAnchorPoint({0, 0});
		auto footer = CCScene::get()->getChildByID("footer"_spr);
		descLabel->setPosition({
			15.f,
			footer->getPositionY() + (footer->getContentHeight() * 3) + 20.f
		});
		descLabel->setID("desc"_spr);
		return descLabel;
	}
	CCLabelBMFont* createUsernameLabel() {
		std::string username = "{User expunged by TokTik}";
		if (m_level) {
			if (m_level->m_levelType == GJLevelType::Local) username = "@RobTop";
			else if (m_level->m_levelType == GJLevelType::Editor) username = fmt::format("@{}", GameManager::get()->m_playerName);
			else if (m_level->m_levelType == GJLevelType::Saved) {
				if (!m_level->m_creatorName.empty()) username = fmt::format("@{}", m_level->m_creatorName);
			}
		}
		const auto authorLabel = CCLabelBMFont::create(username.c_str(), "tokTikFontBold.fnt"_spr, m_fields->manager->winWidth * 0.75f, kCCTextAlignmentLeft);
		authorLabel->setScale(0.75f);
		authorLabel->setZOrder(OTHER_MAGIC_NUMBER);
		authorLabel->setAnchorPoint({0, 0});
		auto descLabel = CCScene::get()->getChildByID("desc"_spr);
		authorLabel->setPosition({
			15.f,
			descLabel->getPositionY() + descLabel->getContentHeight() - 10.f
		});
		authorLabel->setID("author"_spr);
		return authorLabel;
	}
	CCLabelBMFont* createLikesLabel() {
		std::string likes = "0";
		if (m_level && m_level->m_levelType == GJLevelType::Saved) likes = utils::numToAbbreviatedString(m_level->m_likes);
		const auto likesLabel = CCLabelBMFont::create(likes.c_str(), "tokTikFontBold.fnt"_spr);
		likesLabel->setScale(0.2f);
		likesLabel->setZOrder(OTHER_MAGIC_NUMBER);
		likesLabel->setID("likes"_spr);
		return likesLabel;
	}
	CCLabelBMFont* createCommentsLabel() {
		std::string comments = "0";
		if (m_level && m_level->m_levelType == GJLevelType::Saved) comments = utils::numToAbbreviatedString(abs(abs(m_level->m_downloads - m_level->m_likes) / 20) * 3);
		const auto commentsLabel = CCLabelBMFont::create(comments.c_str(), "tokTikFontBold.fnt"_spr);
		commentsLabel->setScale(0.2f);
		commentsLabel->setZOrder(OTHER_MAGIC_NUMBER);
		commentsLabel->setID("comments"_spr);
		return commentsLabel;
	}
	CCLabelBMFont* createDownloadsLabel() {
		int downloads = 0;
		if (m_level && m_level->m_levelType == GJLevelType::Saved) downloads = m_level->m_downloads;
		const auto shareLabel = CCLabelBMFont::create(utils::numToAbbreviatedString(downloads).c_str(), "tokTikFontBold.fnt"_spr);
		shareLabel->setScale(0.2f);
		shareLabel->setZOrder(OTHER_MAGIC_NUMBER);
		shareLabel->setID("downloads"_spr);
		return shareLabel;
	}
	void setupHasCompleted() {
		PlayLayer::setupHasCompleted();
		for (auto object : CCArrayExt<GameObject*>(m_objects)) {
			if (std::ranges::find(m_fields->compatibilityMode, object->m_objectID) != m_fields->compatibilityMode.end()) {
				m_fields->hasRotationOrScale = true;
				break;
			}
		}
	}
	void postUpdate(float p0) {
		PlayLayer::postUpdate(p0);
		auto degrees = static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0));
		auto scene = CCScene::get();
		if (m_fields->rotated && scene->getRotation() == degrees) return;
		if (degrees == 0) {
			m_fields->rotated = true;
			return;
		}
		if (!scene) return;
		if (const auto sprite = createBottomBar(); !scene->getChildByID("bottom-bar"_spr)) scene->addChild(sprite);
		if (const auto sprite = createTopBar(); !scene->getChildByID("top-bar"_spr)) scene->addChild(sprite);
		scene->setRotation(degrees);
		if (Utils::getBool("compatibilityMode") && m_fields->hasRotationOrScale) return;
		scene->setScale(m_fields->manager->winHeight / m_fields->manager->winWidth);
		if (Utils::getBool("tiktokUI")) {
			if (const auto footer = createFooter(); !scene->getChildByID("footer"_spr)) scene->addChild(footer);
			if (const auto actions = createActions(); !scene->getChildByID("actions"_spr)) scene->addChild(actions);
			if (const auto forYou = createForYou(); !scene->getChildByID("for-you"_spr)) scene->addChild(forYou);
			if (const auto search = createSearch(); !scene->getChildByID("search"_spr)) scene->addChild(search);
			if (const auto live = createLive(); !scene->getChildByID("live"_spr)) scene->addChild(live);
			if (const auto descLabel = createDescLabel(); !scene->getChildByID("desc"_spr)) scene->addChild(descLabel);
			if (const auto usernameLabel = createUsernameLabel(); !scene->getChildByID("author"_spr)) scene->addChild(usernameLabel);
			if (const auto actions = scene->getChildByID("actions"_spr)) {
				if (const auto likesLabel = createLikesLabel(); !actions->getChildByID("likes"_spr)) {
					actions->addChild(likesLabel);
					likesLabel->setPosition({13.5f, 63.f}); // it's being added as a child of an existing node (at this point in code execution); no need to clutch onto your mother pearls because of "hArDcOdEd PoSiTiOnS", people
				}
				if (const auto commentsLabel = createCommentsLabel(); !actions->getChildByID("downloads"_spr)) {
					actions->addChild(commentsLabel);
					commentsLabel->setPosition({actions->getChildByID("likes"_spr)->getPositionX(), actions->getChildByID("likes"_spr)->getPositionY() - 20.f}); // it's being added as a child of an existing node (at this point in code execution); no need to clutch onto your mother pearls because of "hArDcOdEd PoSiTiOnS", people
				}
				if (const auto shareLabel = createDownloadsLabel(); !actions->getChildByID("downloads"_spr)) {
					actions->addChild(shareLabel);
					shareLabel->setPosition({actions->getChildByID("comments"_spr)->getPositionX(), actions->getChildByID("comments"_spr)->getPositionY() - 20.f}); // it's being added as a child of an existing node (at this point in code execution); no need to clutch onto your mother pearls because of "hArDcOdEd PoSiTiOnS", people
				}
			}
		}
		m_fields->rotated = true;
	}
};
