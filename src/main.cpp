#include "CustomCamera/Core.h"
#include "CustomCamera/Papyrus/Papyrus.h"

struct Hook_PlayerCharacter {
	static bool SetSneaking(RE::PlayerCharacter* a_this, bool a_sneaking) {
		bool result = _SetSneaking(a_this, a_sneaking);

		auto core = CustomCamera::Core::GetSingleton();
		core->SetSneakingAndApply(a_sneaking);
		core->UpdateCameraWeaponState();

		return result;
	}

	inline static REL::Relocation<decltype(SetSneaking)> _SetSneaking;

	static void Install() {
		static REL::Relocation vtbl{ RE::PlayerCharacter::VTABLE[0] };
		_SetSneaking = vtbl.write_vfunc(0x120, SetSneaking);
	}
};

struct Hook_ThirdPersonState {
	static void UpdateCameraAnimation(RE::ThirdPersonState* a_this) {
		auto core = CustomCamera::Core::GetSingleton();
		if(a_this->STATE == RE::CameraStates::k3rdPerson) {
			core->SetDistanceFromPlayerScaleAndApply(a_this->currentZoomOffset); // add to this camspeed*delta and clamp?
		core->UpdateCameraWeaponState();
			REX::INFO("Current zoom scale factor: {}", a_this->currentZoomOffset);
		}
		_UpdateCameraAnimation(a_this);
	}
	
	inline static REL::Relocation<decltype(UpdateCameraAnimation)> _UpdateCameraAnimation;

	static void Install() {
		static REL::Relocation vtbl{ RE::ThirdPersonState::VTABLE[0] };
		_UpdateCameraAnimation = vtbl.write_vfunc(0x14, UpdateCameraAnimation);
		//REX::INFO("Function address: {:p}", (void*)(_UpdateCameraAnimation.offset()));
	}
};

void OnMessage(F4SE::MessagingInterface::Message* a_msg) {
    switch (a_msg->type) {
		case F4SE::MessagingInterface::kPostLoad: {
			Hook_PlayerCharacter::Install();
			Hook_ThirdPersonState::Install();
		} break;
        case F4SE::MessagingInterface::kGameDataReady: {
			CustomCamera::MCM::MCMDataLoader::GetSingleton()->Load();
            CustomCamera::Core::GetSingleton()->Init();
        } break;
		case F4SE::MessagingInterface::kPostLoadGame: {
			CustomCamera::Core::GetSingleton()->UpdateAndApplySettings();
		}
    }
}

void OnSerialLoad(const F4SE::SerializationInterface* a_intfc) {
	std::uint32_t type;
	std::uint32_t version;
	std::uint32_t length;

	while (a_intfc->GetNextRecordInfo(type, version, length)) {
		switch (type) {
			case 'CORE': {
				const auto core = CustomCamera::Core::GetSingleton();
				core->OnSerialLoad(a_intfc, version, length);
			} break;
			default: {
				REX::ERROR("unrecognized signature type!");
			} break;
		}
	}
}

void OnSerialSave(const F4SE::SerializationInterface* a_intfc) {
	const auto core = CustomCamera::Core::GetSingleton();
	core->OnSerialSave(a_intfc, 'CORE', 1);
}

void OnSerialRevert(const F4SE::SerializationInterface*) {
	const auto core = CustomCamera::Core::GetSingleton();
	core->OnSerialRevert();
}

F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se) {
	F4SE::Init(a_f4se);

    if (const auto intfc = F4SE::GetMessagingInterface())
        intfc->RegisterListener(OnMessage);

	if (const auto intfc = F4SE::GetPapyrusInterface())
        intfc->Register(CustomCamera::Papyrus::Bind);

    if (const auto intfc = F4SE::GetSerializationInterface()) {
        intfc->SetUniqueID('CCAM');
        intfc->SetLoadCallback(OnSerialLoad);
		intfc->SetSaveCallback(OnSerialSave);
		intfc->SetRevertCallback(OnSerialRevert);
    }

	return true;
}
