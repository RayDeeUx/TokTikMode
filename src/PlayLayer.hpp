#pragma once
#include <Geode/modify/PlayLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define MAGIC_NUMBER (-2123456789)

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
	struct Fields {
		CCNode* m_uiNode;
		CCNode* m_rotatedMenuContainer;
		CCNode* m_container;
		CCRenderTexture* m_renderTexture;
		CCSprite* m_renderTo;
		CCLayerColor* m_blackOverlay;
		CCSize m_oldDesignResolution;
		CCSize m_newDesignResolution;
		CCSize m_originalScreenScale;
		CCSize m_newScreenScale;
		Manager* manager = Manager::getSharedInstance();
		float m_scaleFactor = 1.f;
		float m_degrees = 90.f;
		bool m_initialized = false;
		bool m_skipZOrder = true;
		~Fields() {
			if (m_renderTexture) m_renderTexture->release();
		}
	};
	static void onModify(auto& self) {
		(void) self.setHookPriority("PlayLayer::onEnterTransitionDidFinish", MAGIC_NUMBER);
	}
	void applyWinSize() {
		if (m_fields->m_newDesignResolution.width == 0 && m_fields->m_newDesignResolution.height == 0) return;
		const auto view = cocos2d::CCEGLView::get();

		const auto director = CCDirector::get();

		director->m_obWinSizeInPoints = m_fields->m_newDesignResolution;
		view->setDesignResolutionSize(m_fields->m_newDesignResolution.width, m_fields->m_newDesignResolution.height, ResolutionPolicy::kResolutionExactFit);

		float scaleFactor = director->getContentScaleFactor();
		#ifdef __APPLE__
		scaleFactor /= 2.f;
		#endif

		view->m_fScaleX = scaleFactor * m_fields->m_newScreenScale.width;
		view->m_fScaleY = scaleFactor * m_fields->m_newScreenScale.height;
	}

	void restoreWinSize() {
		if (m_fields->m_oldDesignResolution.width == 0 && m_fields->m_oldDesignResolution.height == 0) return;
		auto view = cocos2d::CCEGLView::get();

		cocos2d::CCDirector::get()->m_obWinSizeInPoints = m_fields->m_oldDesignResolution;
		view->setDesignResolutionSize(m_fields->m_oldDesignResolution.width, m_fields->m_oldDesignResolution.height, ResolutionPolicy::kResolutionExactFit);
		view->m_fScaleX = m_fields->m_originalScreenScale.width;
		view->m_fScaleY = m_fields->m_originalScreenScale.height;
	}

	void onEnterTransitionDidFinish() {
		PlayLayer::onEnterTransitionDidFinish();

		if (!Utils::modEnabled()) return;
		if (m_level->isPlatformer() && Utils::getBool("disableOnPlatformer")) return;
		if (!m_level->isPlatformer() && Utils::getBool("disableOnClassic")) return;

		CCSize winSize = CCDirector::get()->getWinSize();
		m_fields->m_container = CCNode::create();
		m_fields->m_container->setZOrder(100000);
		m_fields->m_container->setAnchorPoint({0.5f, 0.5f});
		m_fields->m_container->setContentSize(winSize);
		m_fields->m_container->setPosition(winSize / 2.f);
		m_fields->m_container->setID("container"_spr);

		m_fields->m_rotatedMenuContainer = CCNode::create();
		m_fields->m_rotatedMenuContainer->setAnchorPoint({0.5f, 0.5f});
		m_fields->m_rotatedMenuContainer->setContentSize({winSize.height, winSize.width});
		m_fields->m_rotatedMenuContainer->setPosition(winSize / 2.f);
		m_fields->m_rotatedMenuContainer->setID("rotated-menu-container"_spr);

		m_fields->m_blackOverlay = CCLayerColor::create({0, 0, 0, 255});
		m_fields->m_blackOverlay->setZOrder(0);
		m_fields->m_blackOverlay->setContentSize(winSize);
		m_fields->m_blackOverlay->setID("black-overlay"_spr);

		m_fields->m_renderTexture = CCRenderTexture::create(static_cast<int>(winSize.width), static_cast<int>(winSize.height));
		m_fields->m_renderTexture->retain();
		m_fields->m_renderTo = CCSprite::createWithTexture(m_fields->m_renderTexture->getSprite()->getTexture());
		m_fields->m_renderTo->setFlipY(true);
		m_fields->m_renderTo->setZOrder(1);
		m_fields->m_renderTo->setID("render-texture-if-youre-another-mod-developer-who-wants-to-modify-this-node-then-please-dont-unless-if-your-goal-is-to-break-the-entire-game-for-other-geode-users-i-really-hope-the-extreme-length-of-this-node-id-is-enough-of-a-hint-and-that-youre-not-just-copypasting-this-into-your-source-code-to-suppress-your-guilt"_spr);

		if (Utils::getBool("flipOrientation")) {
			m_fields->m_degrees = 270.f;
			m_fields->m_container->setRotation(180.f);
		}

		m_fields->m_renderTo->setRotation(90);
		m_fields->m_renderTo->setPosition(winSize / 2.f);
		float scale = winSize.height / m_fields->m_renderTo->getContentWidth();
		m_fields->m_renderTo->setScale(scale);

		m_fields->m_uiNode = CCNode::create();
		m_fields->m_uiNode->setContentSize(winSize);
		m_fields->m_uiNode->setPosition(winSize / 2.f);
		m_fields->m_uiNode->setAnchorPoint({0.5f, 0.5f});
		m_fields->m_uiNode->setZOrder(2);
		m_fields->m_uiNode->setID("ui-container"_spr);

		if (Utils::getBool("tokTikUI")) {
			CCNode* footer = createFooter();
			CCNode* actions = createActions(footer);
			CCNode* description = createDescLabel(footer);
			CCNode* username = createUsernameLabel(description);
			CCNode* icon = createSimplePlayer(actions);
			CCNode* forYou = createForYou();
			CCNode* search = createSearch(forYou);
			CCNode* live = createLive(forYou);
			CCNode* vibingCube = createVibingCube(actions);

			m_fields->m_uiNode->addChild(footer);
			m_fields->m_uiNode->addChild(actions);
			m_fields->m_uiNode->addChild(description);
			m_fields->m_uiNode->addChild(username);
			m_fields->m_uiNode->addChild(icon);
			m_fields->m_uiNode->addChild(forYou);
			m_fields->m_uiNode->addChild(search);
			m_fields->m_uiNode->addChild(live);
			m_fields->m_uiNode->addChild(vibingCube);

			if (Utils::getBool("interactiveFooterButtons")) {
				createinteractiveFooterButtons(footer);
			}
		}

		m_fields->m_container->addChild(m_fields->m_uiNode);
		m_fields->m_container->addChild(m_fields->m_renderTo);
		m_fields->m_container->addChild(m_fields->m_blackOverlay);
		m_fields->m_container->addChild(m_fields->m_rotatedMenuContainer);

		CCScene* currentScene = CCDirector::get()->m_pNextScene;
		currentScene->addChild(m_fields->m_container);

		auto view = cocos2d::CCEGLView::get();

		m_fields->m_oldDesignResolution = view->getDesignResolutionSize();
		float aspectRatio = winSize.width / winSize.height;
		m_fields->m_newDesignResolution = cocos2d::CCSize(roundf(320.f * aspectRatio), 320.f);

		m_fields->m_originalScreenScale = cocos2d::CCSize(view->m_fScaleX, view->m_fScaleY);
		m_fields->m_newScreenScale = cocos2d::CCSize(winSize.width / m_fields->m_newDesignResolution.width, winSize.height / m_fields->m_newDesignResolution.height);

		if (m_fields->m_oldDesignResolution != m_fields->m_newDesignResolution) applyWinSize();

		m_fields->m_renderTo->scheduleUpdate();
		m_fields->m_renderTo->schedule(schedule_selector(MyPlayLayer::updateRender));

		setVisible(false);

		m_fields->m_initialized = true;
	}

	void updateRender(float p0) {

		MyPlayLayer* mpl = static_cast<MyPlayLayer*>(PlayLayer::get());

		if (!mpl->m_fields->m_renderTexture) return;
		if (!mpl->m_fields->m_renderTo) return;
		
		mpl->m_fields->m_renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 1.0f);
		
		mpl->m_fields->m_container->setVisible(false);

		CCScene* currentScene = CCDirector::get()->m_pRunningScene;
		mpl->setVisible(true);
		currentScene->visit();
		mpl->setVisible(false);

		mpl->m_fields->m_container->setVisible(true);
		mpl->m_fields->m_renderTexture->end();
		mpl->m_fields->m_renderTo->setTexture(mpl->m_fields->m_renderTexture->getSprite()->getTexture());
	}

	void createinteractiveFooterButtons(CCNode* footer) {
		CCMenu* interactiveFooterButtons = CCMenu::create();

		RowLayout* rowLayout = RowLayout::create();
		rowLayout->setAutoScale(true);
		rowLayout->setAxisAlignment(AxisAlignment::Center);
		rowLayout->setGap(5.0f);

		interactiveFooterButtons->setLayout(rowLayout);
		
		CCSprite* homeTabButton = CCSprite::create("square.png"_spr);
		CCMenuItemSpriteExtra* homeTab = CCMenuItemSpriteExtra::create(homeTabButton, footer, menu_selector(MyPlayLayer::exitPlayLayer));
		homeTab->setID("home-tab"_spr);
		homeTab->setOpacity(0);
		homeTab->setTag(1);

		interactiveFooterButtons->addChild(homeTab);

		CCSprite* friendsTabButton = CCSprite::create("square.png"_spr);
		CCMenuItemSpriteExtra* friendsTab = CCMenuItemSpriteExtra::create(friendsTabButton, footer, menu_selector(MyPlayLayer::openFriends));
		friendsTab->setID("friends-tab"_spr);
		friendsTab->setOpacity(0);
		friendsTab->setTag(2);

		interactiveFooterButtons->addChild(friendsTab);

		CCSprite* myLevelsTabButton = CCSprite::create("square.png"_spr);
		CCMenuItemSpriteExtra* myLevelsTab = CCMenuItemSpriteExtra::create(myLevelsTabButton, footer, menu_selector(MyPlayLayer::openMyLevels));
		myLevelsTab->setOpacity(0);
		myLevelsTab->setTag(3);
		myLevelsTab->setID("my-levels-tab"_spr);

		interactiveFooterButtons->addChild(myLevelsTab);

		CCSprite* inboxTabButton = CCSprite::create("square.png"_spr);
		CCMenuItemSpriteExtra* inboxTab = CCMenuItemSpriteExtra::create(inboxTabButton, footer, menu_selector(MyPlayLayer::openMessages));
		inboxTab->setID("inbox-tab"_spr);
		inboxTab->setOpacity(0);
		inboxTab->setTag(4);

		interactiveFooterButtons->addChild(inboxTab);
		interactiveFooterButtons->updateLayout();

		CCSprite* profileTabButton = CCSprite::create("square.png"_spr);
		CCMenuItemSpriteExtra* profileTab = CCMenuItemSpriteExtra::create(profileTabButton, footer, menu_selector(MyPlayLayer::openProfile));
		profileTab->setID("profile-tab"_spr);
		profileTab->setOpacity(0);
		profileTab->setTag(5);
		interactiveFooterButtons->addChild(profileTab);
		interactiveFooterButtons->updateLayout();

		footer->addChild(interactiveFooterButtons);
		interactiveFooterButtons->setPosition({47.f, 15.f}); // these hardcoded values are fine because they are for a child of an existing node
		interactiveFooterButtons->setScale(1.425f); // these hardcoded values are fine because they are for a child of an existing node
		interactiveFooterButtons->setID("footer-menu"_spr);
	}

	CCSprite* createFooter() {
		CCSprite* footer = CCSprite::create("footer.png"_spr);
		CCSize winSize = CCDirector::get()->getWinSize();
		footer->setID("footer"_spr);
		footer->setRotation(90.f);
		footer->setAnchorPoint({0.5f, 0.f});
		footer->setPosition({0, winSize.height/2});

		m_fields->m_scaleFactor = winSize.height / footer->getContentWidth();
		footer->setScale(m_fields->m_scaleFactor);

		return footer;
	}

	CCSprite* createActions(CCNode* footer) {
		CCSprite* actions = CCSprite::create("actions.png"_spr);
		CCSize winSize = CCDirector::get()->getWinSize();
		actions->setID("actions"_spr);
		actions->setRotation(90.f);
		actions->setAnchorPoint({1.f, 0.f});
		float offset = 20.f;
		actions->setPosition({footer->getScaledContentHeight() + offset, offset});

		actions->setScale(m_fields->m_scaleFactor * 0.75);

		createLikesLabel(actions);
		createDownloadsLabel(actions);
		createCommentsLabel(actions);

		return actions;
	}

	CCLabelBMFont* createDescLabel(CCNode* footer) {
		std::string desc = "[This level's description does not follow TokTik's Community Guidelines, which help us foster an inclusive and authentic community and define the kind of content and behavior that's not allowed on our app.]";
		CCSize winSize = CCDirector::get()->getWinSize();
		
		if (m_level && !m_level->getUnpackedLevelDescription().empty()) desc = m_level->getUnpackedLevelDescription();

		float scaleMultiplier = 0.75f;

		CCLabelBMFont* descLabel = CCLabelBMFont::create(desc.c_str(), "tokTikFont.fnt"_spr, winSize.height * scaleMultiplier, kCCTextAlignmentLeft);
		descLabel->setID("desc"_spr);
		descLabel->setRotation(90.f);
		descLabel->setScale(scaleMultiplier/2);
		descLabel->setAnchorPoint({0, 0});

		float offset = 10.f;
		descLabel->setPosition({footer->getScaledContentHeight() + offset, winSize.height - offset});
		
		return descLabel;
	}

	CCLabelBMFont* createUsernameLabel(CCNode* description) {
		std::string username = "{User expunged by TokTik}";
		CCSize winSize = CCDirector::get()->getWinSize();

		if (m_level) {
			switch (m_level->m_levelType) {
				case GJLevelType::Local:
					username = "@RobTop";
					break;
				case GJLevelType::Editor:
					username = fmt::format("@{}", GameManager::get()->m_playerName);
					break;
				case GJLevelType::Saved:
					if (!m_level->m_creatorName.empty()) username = fmt::format("@{}", m_level->m_creatorName);
					break;
				default:
					break;
			}
		}

		float scaleMultiplier = 0.75f;

		CCLabelBMFont* authorLabel = CCLabelBMFont::create(username.c_str(), "tokTikFontBold.fnt"_spr, winSize.height * scaleMultiplier, kCCTextAlignmentLeft);
		authorLabel->setID("author"_spr);
		authorLabel->setScale(scaleMultiplier/2);
		authorLabel->setRotation(90.f);
		authorLabel->setAnchorPoint({0, 0});

		float offset = 10.f;

		authorLabel->setPosition({description->getScaledContentHeight() + description->getPosition().x + 5, winSize.height - offset});
		return authorLabel;
	}

	int whichIcon(GameManager* gm = GameManager::get()) {
		switch (gm->m_playerIconType) {
			case IconType::Ship:
				return gm->m_playerShip.value();
			case IconType::Ball:
				return gm->m_playerBall.value();
			case IconType::Ufo:
				return gm->m_playerBird.value();
			case IconType::Wave:
				return gm->m_playerDart.value();
			case IconType::Robot:
				return gm->m_playerRobot.value();
			case IconType::Spider:
				return gm->m_playerSpider.value();
			case IconType::Swing:
				return gm->m_playerSwing.value();
			case IconType::Jetpack:
				return gm->m_playerJetpack.value();
			default:
				return gm->m_playerFrame.value();
		}
	}

	SimplePlayer* createSimplePlayer(CCNode* actions) {
		GameManager* gm = GameManager::get();
		SimplePlayer* player = SimplePlayer::create(0);
		player->setID("player"_spr);

		player->updatePlayerFrame(whichIcon(), gm->m_playerIconType);
		player->setColor(gm->colorForIdx(gm->m_playerColor.value()));
		player->setSecondColor(gm->colorForIdx(gm->m_playerColor2.value()));
		player->enableCustomGlowColor(gm->colorForIdx(gm->m_playerGlowColor.value()));
		player->setGlowOutline(gm->colorForIdx(gm->m_playerGlowColor.value()));
		if (!gm->getPlayerGlow()) player->disableGlowOutline();

		player->setRotation(90.f);
		player->setContentSize(player->m_firstLayer->getContentSize());
		player->m_firstLayer->setPosition(player->m_firstLayer->getContentSize()/2);
		
		float scaleFactor = CCDirector::get()->getContentScaleFactor() / 4.f;
		
		player->setPosition({actions->getPositionX() + actions->getScaledContentHeight() - 3, actions->getPositionY()});
		player->setScale(actions->getScale() * (0.285 / scaleFactor));
		player->setAnchorPoint({1.f, 0.f});
		player->setZOrder(-1);
		return player;
	}

	CCSprite* createForYou() {
		CCSprite* forYou = CCSprite::create("followingAndFYP.png"_spr);
		CCSize winSize = CCDirector::get()->getWinSize();

		forYou->setID("for-you"_spr);
		forYou->setRotation(90.f);
		forYou->setAnchorPoint({0.5f, 1.f});

		float offset = 25.f;

		forYou->setPosition({winSize.width - offset, winSize.height/2});
		forYou->setScale(m_fields->m_scaleFactor * 0.8);

		return forYou;
	}

	CCSprite* createSearch(CCNode* forYou) {
		CCSprite* search = CCSprite::create("search.png"_spr);
		CCSize winSize = CCDirector::get()->getWinSize();

		search->setID("search"_spr);
		search->setRotation(90.f);
		search->setAnchorPoint({1.f, 1.f});

		float offset = 20.f;
		float heightOffset = 5.f;

		search->setPosition({forYou->getPositionX() + heightOffset, offset});
		search->setScale(forYou->getScale());
		return search;
	}

	CCSprite* createLive(CCNode* forYou) {
		CCSprite* live = CCSprite::create("live.png"_spr);
		CCSize winSize = CCDirector::get()->getWinSize();

		live->setID("live"_spr);
		live->setRotation(90.f);
		live->setAnchorPoint({0.f, 1.f});

		float offset = 20.f;
		float heightOffset = 5.f;

		live->setPosition({forYou->getPositionX() + heightOffset, winSize.height - offset});
		live->setScale(forYou->getScale());
		return live;
	}
	
	CCSprite* createVibingCube(CCNode* actions) {
		CCSprite* vibingCube = CCSprite::create("vibingCube.png"_spr);
		vibingCube->setID("vibing-cube"_spr);
		vibingCube->setRotation(90.f);
		vibingCube->setScale(actions->getScale() / 19);

		float offset = 6;

		vibingCube->setPosition({actions->getPositionX() + 5 + offset, actions->getPositionY() - offset});
		vibingCube->setAnchorPoint({1.f, 0.f});
		return vibingCube;
	}

	void createLikesLabel(CCNode* actions) {
		std::string likes = "0";
		if (m_level && m_level->m_levelType == GJLevelType::Saved) likes = utils::numToAbbreviatedString(m_level->m_likes);
		CCLabelBMFont* likesLabel = CCLabelBMFont::create(likes.c_str(), "tokTikFontBold.fnt"_spr);
		likesLabel->setScale(0.2f);
		likesLabel->setID("likes"_spr);
		likesLabel->setPosition({13.75, 63});

		actions->addChild(likesLabel);
	}
	void createCommentsLabel(CCNode* actions) {
		std::string comments = "0";
		if (m_level && m_level->m_levelType == GJLevelType::Saved) comments = utils::numToAbbreviatedString(abs((abs(m_level->m_downloads - m_level->m_likes) + 1) / 20) * 3);
		CCLabelBMFont* commentsLabel = CCLabelBMFont::create(comments.c_str(), "tokTikFontBold.fnt"_spr);
		commentsLabel->setScale(0.2f);
		commentsLabel->setID("comments"_spr);
		commentsLabel->setPosition({13.75, 44});

		actions->addChild(commentsLabel);
	}
	void createDownloadsLabel(CCNode* actions) {
		int downloads = 0;
		if (m_level && m_level->m_levelType == GJLevelType::Saved) downloads = m_level->m_downloads;
		CCLabelBMFont* shareLabel = CCLabelBMFont::create(utils::numToAbbreviatedString(downloads).c_str(), "tokTikFontBold.fnt"_spr);
		shareLabel->setScale(0.2f);
		shareLabel->setID("downloads"_spr);
		shareLabel->setPosition({13.75, 23});

		actions->addChild(shareLabel);
	}

	void onQuit() {
		m_fields->manager->senderTag = -1;
		PlayLayer::onQuit();
	}

	/*
		I don't think it is worth making the buttons work, as there are too many issues to count on 5 hands
		I have removed the setting, if you would like to look into resolving in the future, go for it :3
		I tried, I failed, is it worth it, probably not.
		-- Alphalaneous
	*/
	/*
		@everyone: If you really want the interactiveFooterButtons, edit settings.json.
		no warranty for you if anything breaks on your end and interactiveFooterButtons is enabled.
		-- RayDeeUx
	*/

	void exitPlayLayer(CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get()) return;
		PauseLayer::create(false)->onQuit(nullptr);
		m_fields->manager->senderTag = -1;
	}

	void openFriends(CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get()) return;
		m_fields->m_skipZOrder = false;
		FriendsProfilePage::create(UserListType::Friends)->show();
		m_fields->m_skipZOrder = true;
		m_fields->manager->senderTag = sender->getTag();
	}

	void openMyLevels(CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get()) return;
		GameManager::get()->playMenuMusic();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, LevelBrowserLayer::scene(GJSearchObject::create(SearchType::MyLevels))));
		m_fields->manager->senderTag = -1;
	}

	void openMessages(CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get()) return;
		m_fields->m_skipZOrder = false;
		MessagesProfilePage::create(false)->show();
		m_fields->m_skipZOrder = true;
		m_fields->manager->senderTag = sender->getTag();
	}

	void openProfile(CCObject* sender) {
		if (!Utils::modEnabled() || !Utils::getBool("tokTikUI") || !Utils::getBool("interactiveFooterButtons") || !PlayLayer::get()) return;
		m_fields->m_skipZOrder = false;
		GameManager::get()->m_menuLayer->onMyProfile(nullptr);
		m_fields->m_skipZOrder = true;
		m_fields->manager->senderTag = sender->getTag();
	}
};