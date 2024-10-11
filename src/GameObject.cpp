#include "Manager.hpp"
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
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		GameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/TriggerControlGameObject.hpp>
class $modify(MyTriggerControlGameObject, TriggerControlGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("TriggerControlGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		TriggerControlGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/TransformTriggerGameObject.hpp>
class $modify(MyTransformTriggerGameObject, TransformTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("TransformTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		TransformTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/TimerTriggerGameObject.hpp>
class $modify(MyTimerTriggerGameObject, TimerTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("TimerTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		TimerTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/SequenceTriggerGameObject.hpp>
class $modify(MySequenceTriggerGameObject, SequenceTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("SequenceTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		SequenceTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/RandTriggerGameObject.hpp>
class $modify(MyRandTriggerGameObject, RandTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("RandTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		RandTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/ItemTriggerGameObject.hpp>
class $modify(MyItemTriggerGameObject, ItemTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("ItemTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		ItemTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/EventLinkTrigger.hpp>
class $modify(MyEventLinkTrigger, EventLinkTrigger) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("EventLinkTrigger::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		EventLinkTrigger::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/EndTriggerGameObject.hpp>
class $modify(MyEndTriggerGameObject, EndTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("EndTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		EndTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/CountTriggerGameObject.hpp>
class $modify(MyCountTriggerGameObject, CountTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("CountTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		CountTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/CheckpointGameObject.hpp>
class $modify(MyCheckpointGameObject, CheckpointGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("CheckpointGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		CheckpointGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/ArtTriggerGameObject.hpp>
class $modify(MyArtTriggerGameObject, ArtTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("ArtTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		ArtTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#endif

#include <Geode/modify/EffectGameObject.hpp>
class $modify(MyEffectGameObject, EffectGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("EffectGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		EffectGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};
#include <Geode/modify/CameraTriggerGameObject.hpp>
class $modify(MyCameraTriggerGameObject, CameraTriggerGameObject) {
	static void onModify(auto &self) {
		(void) self.setHookPriority("CameraTriggerGameObject::triggerObject", MAGIC_NUMBER);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		float wasOriginally = 0.0f;
		if (Utils::modEnabled() && PlayLayer::get() && CCScene::get()->getRotation() == static_cast<float>(utils::numFromString<int>(Utils::getString("rotationDegrees")).unwrapOr(0))) {
			wasOriginally = CCScene::get()->getRotation();
			CCScene::get()->setRotation(0.0f);
			m_fields->manager->canRotate = false;
		}
		CameraTriggerGameObject::triggerObject(p0, p1, p2);
		if (Utils::modEnabled() && PlayLayer::get()) {
			CCScene::get()->setRotation(wasOriginally);
			m_fields->manager->canRotate = true;
		}
	}
};