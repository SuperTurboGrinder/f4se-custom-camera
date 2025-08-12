#pragma once

#include "CameraStateProcessor.h"

namespace CustomCamera
{
	class Core :
		public REX::Singleton<Core>,
		public RE::BSTEventSink<RE::TESFurnitureEvent>,
		public RE::BSTEventSink<RE::ActorEquipManagerEvent::Event>
	{
	public:
		void Init();

		void OnSerialLoad(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_version, std::uint32_t& a_length);
		void OnSerialSave(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version);
		void OnSerialRevert();

		void ToggleShoulder();
		void SetSneakingAndApply(bool a_sneaking);
		void SetDistanceFromPlayerScaleAndApply(float scale);

        void UpdateAndApplySettings();
		
		void UpdateCameraWeaponState();

	public: // BSTEventSink
		virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESFurnitureEvent& a_event, RE::BSTEventSource<RE::TESFurnitureEvent>*) override;
		virtual RE::BSEventNotifyControl ProcessEvent(const RE::ActorEquipManagerEvent::Event& a_event, RE::BSTEventSource<RE::ActorEquipManagerEvent::Event>*) override;
	private:
		CameraStateProcessor stateProcessor;
	};
}
