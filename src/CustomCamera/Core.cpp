#include "Core.h"
#include "MCM/MCMDataLoader.h"

namespace CustomCamera
{
	void Core::Init() {
		RE::TESFurnitureEvent::GetEventSource()->RegisterSink(this);
		RE::ActorEquipManager::GetSingleton()->RegisterSink(this);

		const auto ini = RE::INISettingCollection::GetSingleton();
		ini->GetSetting("bApplyCameraNodeAnimations:Camera")->SetBinary(false);

		UpdateAndApplySettings();
	}

	void Core::OnSerialLoad(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_version, std::uint32_t& a_length) {
		bool leftShoulderCamera = false;
		if (a_intfc->ReadRecordDataEx(a_length, leftShoulderCamera)) {
			stateProcessor.setIsLeftShoulder(leftShoulderCamera);
		} {
			REX::ERROR("failed to load leftShoulderCamera");
		}
	}

	void Core::OnSerialSave(const F4SE::SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version) {
		if (a_intfc->OpenRecord(a_type, a_version)) {
			a_intfc->WriteRecordData(stateProcessor.IsLeftShoulder());
		}
	}

	void Core::OnSerialRevert() {
		stateProcessor.ResetToRightShoulder();
	}

	void Core::ToggleShoulder() {
		stateProcessor.SwitchShoulder();
	}

	void Core::SetSneakingAndApply(bool a_sneaking) {
		stateProcessor.SetSneakingAndApply(a_sneaking);
	}

	void Core::SetDistanceFromPlayerScaleAndApply(float scale) {
		stateProcessor.InterpolateFarAndCloseSettingsAndApply(scale);
	}

	void Core::UpdateAndApplySettings() {
		stateProcessor.UpdateAndApply();
	}

	void Core::UpdateCameraWeaponState() {
		const auto camera = RE::PlayerCamera::GetSingleton();
		const auto player = RE::PlayerCharacter::GetSingleton();
		if (camera && player) {
			if (auto state = camera->GetState<RE::ThirdPersonState>())
				state->ProcessWeaponDrawnChange(player->GetWeaponMagicDrawn());
		}
	}

	RE::BSEventNotifyControl Core::ProcessEvent(const RE::TESFurnitureEvent& a_event, RE::BSTEventSource<RE::TESFurnitureEvent>*) {
		if (a_event.actor->IsPlayerRef())
			UpdateAndApplySettings();

		return RE::BSEventNotifyControl::kContinue;
	}

	RE::BSEventNotifyControl Core::ProcessEvent(const RE::ActorEquipManagerEvent::Event& a_event, RE::BSTEventSource<RE::ActorEquipManagerEvent::Event>*) {
		if (a_event.actorAffected->IsPlayerRef())
			UpdateAndApplySettings();

		return RE::BSEventNotifyControl::kContinue;
	}
}
