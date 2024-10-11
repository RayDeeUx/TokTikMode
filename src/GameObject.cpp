#include "Utils.hpp"
#define MAGIC_NUMBER (-2123456789)
#define OTHER_MAGIC_NUMBER (-MAGIC_NUMBER / 30000)

using namespace geode::prelude;

#ifndef GEODE_IS_WINDOWS
#include <Geode/modify/GameObject.hpp>
class $modify(MyGameObject, GameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("GameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		GameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/TriggerControlGameObject.hpp>
class $modify(MyTriggerControlGameObject, TriggerControlGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("TriggerControlGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		TriggerControlGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/TransformTriggerGameObject.hpp>
class $modify(MyTransformTriggerGameObject, TransformTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("TransformTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		TransformTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/TimerTriggerGameObject.hpp>
class $modify(MyTimerTriggerGameObject, TimerTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("TimerTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		TimerTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/SequenceTriggerGameObject.hpp>
class $modify(MySequenceTriggerGameObject, SequenceTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("SequenceTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		SequenceTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/RandTriggerGameObject.hpp>
class $modify(MyRandTriggerGameObject, RandTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("RandTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		RandTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/ItemTriggerGameObject.hpp>
class $modify(MyItemTriggerGameObject, ItemTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("ItemTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		ItemTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/EventLinkTrigger.hpp>
class $modify(MyEventLinkTrigger, EventLinkTrigger) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("EventLinkTrigger::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		EventLinkTrigger::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/EndTriggerGameObject.hpp>
class $modify(MyEndTriggerGameObject, EndTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("EndTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		EndTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/CountTriggerGameObject.hpp>
class $modify(MyCountTriggerGameObject, CountTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("CountTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		CountTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/CheckpointGameObject.hpp>
class $modify(MyCheckpointGameObject, CheckpointGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("CheckpointGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		CheckpointGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/ArtTriggerGameObject.hpp>
class $modify(MyArtTriggerGameObject, ArtTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("ArtTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		ArtTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#endif

#include <Geode/modify/EffectGameObject.hpp>
class $modify(MyEffectGameObject, EffectGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("EffectGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		EffectGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};
#include <Geode/modify/CameraTriggerGameObject.hpp>
class $modify(MyCameraTriggerGameObject, CameraTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("CameraTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
		}
		CameraTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
		}
	}
};