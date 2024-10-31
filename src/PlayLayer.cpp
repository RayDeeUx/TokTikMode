#include <Geode/modify/PlayLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

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
	};
	static int whichIcon(GameManager* gm = GameManager::get()) {
		int iconType = (int) gm->m_playerIconType;
		if (iconType == 1) return gm->m_playerShip.value();
		if (iconType == 2) return gm->m_playerBall.value();
		if (iconType == 3) return gm->m_playerBird.value();
		if (iconType == 4) return gm->m_playerDart.value();
		if (iconType == 5) return gm->m_playerRobot.value();
		if (iconType == 6) return gm->m_playerSpider.value();
		if (iconType == 7) return gm->m_playerSwing.value();
		if (iconType == 8) return gm->m_playerJetpack.value();
		return gm->m_playerFrame.value();
	}
	CCSprite* createFooter() {
		CCSprite* footer = CCSprite::create("footer.png"_spr);
		footer->setID("footer"_spr);
		footer->setPosition({
			m_fields->manager->winWidth / 2.f,
			(-m_fields->manager->winHeight) + (2.f * footer->getContentHeight()) + static_cast<float>(Utils::getInt("footerOffset"))
		});
		#ifdef GEODE_IS_MACOS
		footer->setPositionY(footer->getPositionY() + 83.f);
		#elif defined(GEODE_IS_ANDROID64)
		footer->setPositionY(footer->getPositionY() - 145.f);
		#elif defined(GEODE_IS_ANDROID32)
		footer->setPositionY(footer->getPositionY() - 67.5f);
		#endif
		footer->setScale(m_fields->manager->winWidth / footer->getContentWidth());
		footer->setZOrder(OTHER_MAGIC_NUMBER);
		return footer;
	}
	CCSprite* createActions() {
		CCSprite* actions = CCSprite::create("actions.png"_spr);
		actions->setID("actions"_spr);
		actions->setPosition({
			m_fields->manager->winWidth - (actions->getContentWidth() * 3.10f),
			0 + static_cast<float>(Utils::getInt("footerOffset"))
		});
		#ifdef GEODE_IS_MACOS
		actions->setPositionY(actions->getPositionY() + 83.f);
		#elif defined(GEODE_IS_ANDROID64)
		actions->setPositionY(actions->getPositionY() - 145.f);
		#elif defined(GEODE_IS_ANDROID32)
		actions->setPositionY(actions->getPositionY() - 67.5f);
		#endif
		actions->setScale((actions->getContentWidth() / m_fields->manager->winWidth) * 125.f);
		actions->setZOrder(OTHER_MAGIC_NUMBER + 1);
		return actions;
	}
	CCSprite* createForYou() {
		CCSprite* forYou = CCSprite::create("followingAndFYP.png"_spr);
		forYou->setID("for-you"_spr);
		forYou->setPosition({
			m_fields->manager->winWidth / 2.f,
			m_fields->manager->winWidth + (forYou->getContentHeight()) + static_cast<float>(Utils::getInt("headerOffset"))
		});
		#ifdef GEODE_IS_MACOS
		forYou->setPositionY(forYou->getPositionY() - 15.f);
		forYou->setScale(((forYou->getContentWidth() / m_fields->manager->winWidth) * 40.f) * 0.75f * static_cast<float>(Utils::getDouble("headerScale")));
		#elif defined(GEODE_IS_ANDROID64)
		forYou->setScale(((forYou->getContentWidth() / m_fields->manager->winWidth) * 40.f) * 1.449f * static_cast<float>(Utils::getDouble("headerScale")));
		forYou->setPositionY(forYou->getPositionY() + 120.f);
		#elif defined(GEODE_IS_ANDROID32)
		forYou->setScale(((forYou->getContentWidth() / m_fields->manager->winWidth) * 40.f) * 0.9f * static_cast<float>(Utils::getDouble("headerScale")));
		forYou->setPositionY(forYou->getPositionY() + 60.f);
		#else
		forYou->setScale((forYou->getContentWidth() / m_fields->manager->winWidth) * 40.f * static_cast<float>(Utils::getDouble("headerScale")));
		#endif
		forYou->setZOrder(OTHER_MAGIC_NUMBER);
		return forYou;
	}
	static CCSprite* createSearch() {
		CCSprite* search = CCSprite::create("search.png"_spr);
		const auto &scene = CCScene::get();
		search->setID("search"_spr);
		search->setPosition({
			scene->getChildByID("actions"_spr)->getPositionX() + 20.f,
			scene->getChildByID("for-you"_spr)->getPositionY() + 10.f,
		});
		search->setScale(scene->getChildByID("for-you"_spr)->getScale() * 0.85f);
		search->setZOrder(OTHER_MAGIC_NUMBER);
		return search;
	}
	static CCSprite* createLive() {
		CCSprite* live = CCSprite::create("live.png"_spr);
		const auto &scene = CCScene::get();
		live->setID("live"_spr);
		live->setPosition({
			35.f,
			scene->getChildByID("for-you"_spr)->getPositionY() + 10.f,
		});
		live->setScale(scene->getChildByID("for-you"_spr)->getScale() * 0.85f);
		live->setZOrder(OTHER_MAGIC_NUMBER);
		return live;
	}
	static CCSprite* createVibingCube() {
		CCSprite* vibingCube = CCSprite::create("vibingCube.png"_spr);
		vibingCube->setID("vibing-cube"_spr);
		vibingCube->setZOrder(OTHER_MAGIC_NUMBER + 1);
		return vibingCube;
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
		const auto &descLabel = CCLabelBMFont::create(desc.c_str(), "tokTikFont.fnt"_spr, m_fields->manager->winWidth * 0.75f, kCCTextAlignmentLeft);
		descLabel->setScale(0.75f);
		descLabel->setZOrder(OTHER_MAGIC_NUMBER);
		descLabel->setAnchorPoint({0, 0});
		const auto &footer = CCScene::get()->getChildByID("footer"_spr);
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
		const auto &authorLabel = CCLabelBMFont::create(username.c_str(), "tokTikFontBold.fnt"_spr, m_fields->manager->winWidth * 0.75f, kCCTextAlignmentLeft);
		authorLabel->setScale(0.75f);
		authorLabel->setZOrder(OTHER_MAGIC_NUMBER);
		authorLabel->setAnchorPoint({0, 0});
		const auto &descLabel = CCScene::get()->getChildByID("desc"_spr);
		authorLabel->setPosition({
			15.f,
			descLabel->getPositionY() + descLabel->getContentHeight() - 5.f
		});
		authorLabel->setID("author"_spr);
		return authorLabel;
	}
	CCLabelBMFont* createLikesLabel() {
		std::string likes = "0";
		if (m_level && m_level->m_levelType == GJLevelType::Saved) likes = utils::numToAbbreviatedString(m_level->m_likes);
		const auto &likesLabel = CCLabelBMFont::create(likes.c_str(), "tokTikFontBold.fnt"_spr);
		likesLabel->setScale(0.2f);
		likesLabel->setZOrder(OTHER_MAGIC_NUMBER);
		likesLabel->setID("likes"_spr);
		return likesLabel;
	}
	CCLabelBMFont* createCommentsLabel() {
		std::string comments = "0";
		if (m_level && m_level->m_levelType == GJLevelType::Saved) comments = utils::numToAbbreviatedString(abs((abs(m_level->m_downloads - m_level->m_likes) + 1) / 20) * 3);
		const auto &commentsLabel = CCLabelBMFont::create(comments.c_str(), "tokTikFontBold.fnt"_spr);
		commentsLabel->setScale(0.2f);
		commentsLabel->setZOrder(OTHER_MAGIC_NUMBER);
		commentsLabel->setID("comments"_spr);
		return commentsLabel;
	}
	CCLabelBMFont* createDownloadsLabel() {
		int downloads = 0;
		if (m_level && m_level->m_levelType == GJLevelType::Saved) downloads = m_level->m_downloads;
		const auto &shareLabel = CCLabelBMFont::create(utils::numToAbbreviatedString(downloads).c_str(), "tokTikFontBold.fnt"_spr);
		shareLabel->setScale(0.2f);
		shareLabel->setZOrder(OTHER_MAGIC_NUMBER);
		shareLabel->setID("downloads"_spr);
		return shareLabel;
	}
	static SimplePlayer* createSimplePlayer() {
		GameManager* gm = GameManager::get();
		SimplePlayer* player = SimplePlayer::create(0);
		player->updatePlayerFrame(whichIcon(), gm->m_playerIconType);
		player->setColor(gm->colorForIdx(gm->m_playerColor.value()));
		const auto &actions = CCScene::get()->getChildByID("actions"_spr);
		player->setSecondColor(gm->colorForIdx(gm->m_playerColor2.value()));
		player->enableCustomGlowColor(gm->colorForIdx(gm->m_playerGlowColor.value()));
		player->setGlowOutline(gm->colorForIdx(gm->m_playerGlowColor.value()));
		if (!gm->getPlayerGlow()) player->disableGlowOutline();
		player->setPositionY(actions->getPositionY() + 205.f);
		player->setPositionX(actions->getPositionX() + 22.f);
		#ifdef GEODE_IS_WINDOWS
		player->setPositionY(player->getPositionY() - 19.f);
		player->setPositionX(player->getPositionX() - 3.f);
		#elif defined(GEODE_IS_ANDROID)
		player->setPositionY(player->getPositionY() - 57.f);
		player->setPositionX(player->getPositionX() - 6.f);
		#endif
		player->setZOrder(OTHER_MAGIC_NUMBER);
		player->setID("player"_spr);
		player->setScale(1.1f);
		return player;
	}
	void setupHasCompleted() {
		PlayLayer::setupHasCompleted();
		if (!Utils::modEnabled()) return;
		std::array compatibilityMode {1346, 2067, 3007, 3008, 3012, 3013, 3032, 3033};
		for (const auto &object : CCArrayExt<GameObject*>(m_objects)) {
			if (std::ranges::find(compatibilityMode, object->m_objectID) != compatibilityMode.end()) {
				m_fields->hasRotationOrScale = true;
				break;
			}
		}
	}
	void postUpdate(float p0) {
		PlayLayer::postUpdate(p0);
		if (!Utils::modEnabled()) return;
		const auto &degrees = static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0));
		const auto &scene = CCScene::get();
		if (m_fields->rotated && scene->getRotation() == degrees) return;
		if (degrees == 0) {
			m_fields->rotated = true;
			return;
		}
		if (!scene) return;
		if (const auto &sprite = createBottomBar(); !scene->getChildByID("bottom-bar"_spr)) scene->addChild(sprite);
		if (const auto &sprite = createTopBar(); !scene->getChildByID("top-bar"_spr)) scene->addChild(sprite);
		if (Utils::getBool("compatibilityMode") && m_fields->hasRotationOrScale) return;
		scene->setRotation(degrees);
		scene->setScale(m_fields->manager->winHeight / m_fields->manager->winWidth);
		if (Utils::getBool("tokTikUI")) {
			if (const auto &footer = createFooter(); !scene->getChildByID("footer"_spr)) scene->addChild(footer);
			if (const auto &actions = createActions(); !scene->getChildByID("actions"_spr)) scene->addChild(actions);
			if (const auto &forYou = createForYou(); !scene->getChildByID("for-you"_spr)) scene->addChild(forYou);
			if (const auto &search = createSearch(); !scene->getChildByID("search"_spr)) scene->addChild(search);
			if (const auto &live = createLive(); !scene->getChildByID("live"_spr)) scene->addChild(live);
			if (const auto &descLabel = createDescLabel(); !scene->getChildByID("desc"_spr)) scene->addChild(descLabel);
			if (const auto &usernameLabel = createUsernameLabel(); !scene->getChildByID("author"_spr)) scene->addChild(usernameLabel);
			if (const auto &actions = scene->getChildByID("actions"_spr)) {
				if (const auto &likesLabel = createLikesLabel(); !actions->getChildByID("likes"_spr)) {
					actions->addChild(likesLabel);
					likesLabel->setPosition({13.5f, 63.f}); // it's being added as a child of an existing node (at this point in code execution); no need to clutch onto your mother pearls because of "hArDcOdEd PoSiTiOnS", people
				}
				if (const auto &commentsLabel = createCommentsLabel(); !actions->getChildByID("comments"_spr)) {
					actions->addChild(commentsLabel);
					commentsLabel->setPosition({actions->getChildByID("likes"_spr)->getPositionX(), actions->getChildByID("likes"_spr)->getPositionY() - 20.f});
				}
				if (const auto &shareLabel = createDownloadsLabel(); !actions->getChildByID("downloads"_spr)) {
					actions->addChild(shareLabel);
					shareLabel->setPosition({actions->getChildByID("comments"_spr)->getPositionX(), actions->getChildByID("comments"_spr)->getPositionY() - 20.f});
				}
				if (const auto &vibingCube = createVibingCube(); !actions->getChildByID("vibing-cube"_spr)) {
					actions->addChild(vibingCube);
					vibingCube->setScale(0.05f);
					vibingCube->setPosition({actions->getChildByID("downloads"_spr)->getPositionX(), actions->getChildByID("downloads"_spr)->getPositionY() - 12.f});
				}
				if (const auto &simplePlayer = createSimplePlayer(); !scene->getChildByID("player"_spr)) {
					scene->addChild(simplePlayer);
				}
			}
		}
		m_fields->rotated = true;
	}
};
