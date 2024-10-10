#pragma once

#include <Geode/loader/SettingNode.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

class MySettingValue : public

SettingValue

{
protected:
	std::string m_placeholder;
public:
	MySettingValue(std::string const& key, std::string const& modID, std::string const& placeholder)
	  : SettingValue(key, modID), m_placeholder(placeholder) {}
	bool load(matjson::Value const& json) override { return true; }
	bool save(matjson::Value& json) const override { return true; }
	SettingNode* createNode(float width) override;
};

class MySettingNode : public SettingNode {
private:
	std::string m_title = "";
	std::string m_desc = "";
protected:
	void onButton(CCObject*) {
		if (m_title != "Privacy Policy") {
			geode::createQuickPopup(
				m_title.c_str(),
				m_desc,
				"Cancel", "Open latlong.net",
				[this](FLAlertLayer* alert, bool openLatLong) {
					if (openLatLong) {
						geode::utils::web::openLinkInBrowser("https://latlong.net/countries");
					}
				}
			);
		} else {
			FLAlertLayer::create(
				nullptr,
				m_title.c_str(),
				m_desc,
				"Close",
				nullptr,
				420.f,
				true,
				320.f,
				1.0f
			)->show();

		}
	}
	bool init(MySettingValue* value, float width) {
		if (!SettingNode::init(value))
			return false;
		this->setContentSize({ width, 40.f });
		std::string name = Mod::get()->getSettingDefinition(value->getKey())->get<CustomSetting>()->json->get<std::string>("name");
		m_desc = Mod::get()->getSettingDefinition(value->getKey())->get<CustomSetting>()->json->get<std::string>("desc");
		m_title = "Open latlong.net?";
		if (name == "Privacy Policy") m_title = "Privacy Policy";

		auto theMenu = CCMenu::create();
		auto theLabel = CCLabelBMFont::create(name.c_str(), "bigFont.fnt");

		// copied a bit from viper
		theLabel->setScale(.35f);
		theLabel->limitLabelWidth(300.f, .35f, .25f); // added by Ery. max width is 346.f

		auto theLabelAsAButton = CCMenuItemSpriteExtra::create(theLabel, this, menu_selector(MySettingNode::onButton));

		theLabelAsAButton->setPositionX(0);

		theMenu->addChild(theLabelAsAButton);
		theMenu->setPosition(width / 2, 20.f);

		this->addChild(theMenu);

		return true;
	}

public:
	void commit() override {
		this->dispatchCommitted();
	}
	bool hasUncommittedChanges() override {
		return false;
	}
	bool hasNonDefaultValue() override {
		return true;
	}
	void resetToDefault() override {}

	static MySettingNode* create(MySettingValue* value, float width) {
		auto ret = new MySettingNode();
		if (ret && ret->init(value, width)) {
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
};