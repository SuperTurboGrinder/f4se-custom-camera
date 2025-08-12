#include "MCM/MCMDataLoader.h"
#include "CameraStateProcessor.h"

namespace CustomCamera {
    void CameraStateProcessor::UpdateAndApply() {
        const auto& mcmSettings = MCM::MCMDataLoader::GetSingleton()->GetMCM();
        bool isInPowerArmor = RE::PowerArmor::PlayerInPowerArmor();
        UpdateIntermediateCameraOffsets(mcmSettings, isInPowerArmor);
		UpdateInterpolatedCameraOffsets();
        UpdateRangedAimZoom();
        UpdateFOV(mcmSettings);
        UpdateMiscCameraSettings(mcmSettings, isInPowerArmor);

        ApplyToGameSettings();
    }

    bool CameraStateProcessor::IsLeftShoulder() {
        return shoulder == ShoulderSwitch::Left;
    }

    void CameraStateProcessor::setIsLeftShoulder(bool isLeftShoulder) {
        shoulder = isLeftShoulder ? ShoulderSwitch::Left : ShoulderSwitch::Right;
    }

    void CameraStateProcessor::ResetToRightShoulder() {
        shoulder = ShoulderSwitch::Right;
    }
    
    void CameraStateProcessor::SwitchShoulder() {
        shoulder = (shoulder == ShoulderSwitch::Right) ? ShoulderSwitch::Left : ShoulderSwitch::Right;
    }
    
    void CameraStateProcessor::SetSneakingAndApply(bool _isSneaking) {
        isSneaking = _isSneaking ? SneakingSwitch::Sneaking : SneakingSwitch::Standing;
    }

	void CameraStateProcessor::InterpolateFarAndCloseSettingsAndApply(float scale) {
		gameCameraDistanceFromCharacterScale = std::clamp(scale, 0.0f, 1.0f);
		UpdateInterpolatedCameraOffsets();
		STGUtils::GameINIValueUpdater ini;
		ApplyOffsetsToGameSettings(ini);
	}

	
    Data::CameraOffset CameraStateProcessor::OffsetSettingsToOffset(const MCM::Data::CameraOffsetsSettings& settings) const {
        return Data::CameraOffset {
            .horizontal = isSneaking == SneakingSwitch::Sneaking
                ? shoulder == ShoulderSwitch::Left ? settings.standing.horizontalLeft : settings.standing.horizontalRight
                : shoulder == ShoulderSwitch::Left ? settings.sneaking.horizontalLeft : settings.sneaking.horizontalRight,
            .vertical = isSneaking ? settings.standing.vertical : settings.standing.vertical,
            .forward = isSneaking ? settings.sneaking.forward : settings.sneaking.forward
        };
    }

	Data::CameraOffsetsSet CameraStateProcessor::OffsetSettingsSetToOffsetSet(const MCM::Data::CameraOffsetsSet& settingsSet) const {
		return Data::CameraOffsetsSet {
			.normalOffsets = OffsetSettingsToOffset(settingsSet.normal),
			.meleeOffsets = OffsetSettingsToOffset(settingsSet.melee),
			.rangedOffsets = OffsetSettingsToOffset(settingsSet.ranged),
		};
	}
    

	void CameraStateProcessor::UpdateIntermediateCameraOffsets(const MCM::Data& mcmSettings, bool isInPowerArmor) {
		const auto& cameraStateFar = isInPowerArmor ? mcmSettings.InPowerArmor : mcmSettings.NoPowerArmor;
		const auto& cameraStateClose = isInPowerArmor ? mcmSettings.InPowerArmorClose : mcmSettings.NoPowerArmorClose;

		farBackward = OffsetSettingsSetToOffsetSet(cameraStateFar);
		closeForward = OffsetSettingsSetToOffsetSet(cameraStateClose);

		// HHS Compatibility
		if (const auto player = RE::PlayerCharacter::GetSingleton()) {
			if (const auto root = player->Get3D(false)) {
				if (const auto node = root->GetObjectByName("COM_Override")) {
					const auto nodeZ = node->local.translate.z;
					farBackward.normalOffsets.vertical += nodeZ;
					farBackward.meleeOffsets.vertical += nodeZ;
					farBackward.rangedOffsets.vertical += nodeZ;
					closeForward.normalOffsets.vertical += nodeZ;
					closeForward.meleeOffsets.vertical += nodeZ;
					closeForward.rangedOffsets.vertical += nodeZ;
				}
			}
		}
	}

	void CameraStateProcessor::UpdateInterpolatedCameraOffsets() {
		interpolatedOffsets.SetFromLerp(closeForward, farBackward, gameCameraDistanceFromCharacterScale);
		//ranged zoom
		float x = std::powf(std::fabsf(interpolatedOffsets.rangedOffsets.horizontal), 2.0f);
		float z = std::powf(interpolatedOffsets.rangedOffsets.vertical, 2.0f);
		m_camera3rdPersonAimDist = std::sqrtf(x + z);
	}

	void CameraStateProcessor::UpdateRangedAimZoom() {
	}

	void CameraStateProcessor::UpdateFOV(const MCM::Data& mcmSettings) {
		fieldOfViewSettings.cam1stPersonFOV = mcmSettings.camera1stFOV;
		fieldOfViewSettings.cam3rdPersonFOV = mcmSettings.camera3rdFOV;
		fieldOfViewSettings.cam3rdPersonAimFOV = mcmSettings.camera3rdAimFOV;
	}

	void CameraStateProcessor::UpdateMiscCameraSettings(const MCM::Data& mcmSettings, bool isInPowerArmor) {
		vanityModeSettings.isEnabled = mcmSettings.vanityModeEnabled;
		auto& miscSettings = isInPowerArmor ? mcmSettings.miscInPASettings : mcmSettings.miscNoPASettings;

		vanityModeSettings.distanceMin = miscSettings.cameraMinDist;
		vanityModeSettings.distanceMax = miscSettings.cameraMaxDist;
		
		mouseWheelZoomSettings.cameraZoomSpeed = miscSettings.cameraZoomSpeed;
		mouseWheelZoomSettings.interpolationIncrement = miscSettings.cameraZoomInterpolationIncrement;

		m_cameraChangeSpeed = mcmSettings.cameraChangeSpeed;
		m_cameraPitchZoom = mcmSettings.cameraPitchZoom;
	}

	void CameraStateProcessor::ApplyToGameSettings() {
		STGUtils::GameINIValueUpdater ini;
		ApplyOffsetsToGameSettings(ini);
		ApplyOtherGameSettings(ini);
	}

	void CameraStateProcessor::ApplyOffsetsToGameSettings(STGUtils::GameINIValueUpdater& gameSettings) {
		gameSettings.UpdateValue("fOverShoulderPosX:Camera", interpolatedOffsets.normalOffsets.horizontal);
		gameSettings.UpdateValue("fOverShoulderPosZ:Camera", interpolatedOffsets.normalOffsets.vertical);

		gameSettings.UpdateValue("fOverShoulderMeleeCombatPosX:Camera", interpolatedOffsets.meleeOffsets.horizontal);
		gameSettings.UpdateValue("fOverShoulderMeleeCombatPosZ:Camera", interpolatedOffsets.meleeOffsets.vertical);
		gameSettings.UpdateValue("fOverShoulderMeleeCombatAddY:Camera", interpolatedOffsets.meleeOffsets.forward);

		gameSettings.UpdateValue("fOverShoulderCombatPosX:Camera", interpolatedOffsets.rangedOffsets.horizontal);
		gameSettings.UpdateValue("fOverShoulderCombatPosZ:Camera", interpolatedOffsets.rangedOffsets.vertical);
		gameSettings.UpdateValue("fOverShoulderCombatAddY:Camera", interpolatedOffsets.rangedOffsets.forward);

		gameSettings.UpdateValue("f3rdPersonAimDist:Camera", m_camera3rdPersonAimDist);
	}

	void CameraStateProcessor::ApplyOtherGameSettings(STGUtils::GameINIValueUpdater& gameSettings) {
		gameSettings.UpdateValue("bDisableAutoVanityMode:Camera", !vanityModeSettings.isEnabled);
		gameSettings.UpdateValue("fVanityModeMinDist:Camera", vanityModeSettings.distanceMin);
		gameSettings.UpdateValue("fVanityModeMaxDist:Camera", vanityModeSettings.distanceMax);

		gameSettings.UpdateValue("fMouseWheelZoomSpeed:Camera", mouseWheelZoomSettings.cameraZoomSpeed);
		gameSettings.UpdateValue("fMouseWheelZoomIncrement:Camera", mouseWheelZoomSettings.interpolationIncrement);

		gameSettings.UpdateValue("fDefault1stPersonFOV:Display", fieldOfViewSettings.cam1stPersonFOV);
		gameSettings.UpdateValue("fDefaultWorldFOV:Display", fieldOfViewSettings.cam3rdPersonFOV);
		gameSettings.UpdateValue("f3rdPersonAimFOV:Camera", fieldOfViewSettings.cam3rdPersonAimFOV);

		gameSettings.UpdateValue("fShoulderDollySpeed:Camera", m_cameraChangeSpeed);
		gameSettings.UpdateValue("fPitchZoomOutMaxDist:Camera", m_cameraPitchZoom);
	}
}