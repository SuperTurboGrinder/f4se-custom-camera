#include "MCM/MCMDataLoader.h"

namespace CustomCamera::MCM {

	void MCMDataLoader::ReadCameraOffsetValues(
		const STGUtils::MCMSettingsUtil& ini,
		Data::CameraOffsetsSettings& offsets,

		const MCMKeys::Camera::Offsets keyHorizontalLeft,
		const MCMKeys::Camera::Offsets keyHorizontalRight,
		const MCMKeys::Camera::Offsets keyVertical,
		const MCMKeys::Camera::Offsets keyForward,

		const MCMKeys::Camera::Offsets keySneakHorizontalLeft,
		const MCMKeys::Camera::Offsets keySneakHorizontalRight,
		const MCMKeys::Camera::Offsets keySneakVertical,
		const MCMKeys::Camera::Offsets keySneakForward
	) {
		offsets = {
			.standing = {
				ini.GetFloatValue(INIKey(keyHorizontalLeft), offsets.standing.horizontalLeft),
				ini.GetFloatValue(INIKey(keyHorizontalRight), offsets.standing.horizontalRight),
				ini.GetFloatValue(INIKey(keyVertical), offsets.standing.vertical),
				ini.GetFloatValue(INIKey(keyForward), offsets.standing.forward),
			},
			.sneaking = {
				ini.GetFloatValue(INIKey(keySneakHorizontalLeft), offsets.sneaking.horizontalLeft),
				ini.GetFloatValue(INIKey(keySneakHorizontalRight), offsets.sneaking.horizontalRight),
				ini.GetFloatValue(INIKey(keySneakVertical), offsets.sneaking.vertical),
				ini.GetFloatValue(INIKey(keySneakForward), offsets.sneaking.forward),
			}
		};
	}

	
	void MCMDataLoader::WriteCameraOffsetValues(
		STGUtils::MCMSettingsUtil& ini,
		const Data::CameraOffsetsSettings& offsets,

		const MCMKeys::Camera::Offsets keyHorizontalLeft,
		const MCMKeys::Camera::Offsets keyHorizontalRight,
		const MCMKeys::Camera::Offsets keyVertical,
		const MCMKeys::Camera::Offsets keyForward,

		const MCMKeys::Camera::Offsets keySneakHorizontalLeft,
		const MCMKeys::Camera::Offsets keySneakHorizontalRight,
		const MCMKeys::Camera::Offsets keySneakVertical,
		const MCMKeys::Camera::Offsets keySneakForward
	) {
		ini.SetFloatValue(INIKey(keyHorizontalLeft), offsets.standing.horizontalLeft);
		ini.SetFloatValue(INIKey(keyHorizontalRight), offsets.standing.horizontalRight);
		ini.SetFloatValue(INIKey(keyVertical), offsets.standing.vertical);
		ini.SetFloatValue(INIKey(keyForward), offsets.standing.forward);
		ini.SetFloatValue(INIKey(keySneakHorizontalLeft), offsets.sneaking.horizontalLeft);
		ini.SetFloatValue(INIKey(keySneakHorizontalRight), offsets.sneaking.horizontalRight);
		ini.SetFloatValue(INIKey(keySneakVertical), offsets.sneaking.vertical);
		ini.SetFloatValue(INIKey(keySneakForward), offsets.sneaking.forward);
	}

	void MCMDataLoader::Load() {
		STGUtils::MCMSettingsUtil ini("CustomCamera");
		bool doesNotExist = !ini.IsInitializedSuccesfully() && ini.FileDoesNotExist();
		if(doesNotExist || ini.IsEmpty()) {
			//default values from one single source (Data.h)
			WriteMCMData(ini);
			ini.SaveFile();
		} else {
			if(ini.IsInitializedSuccesfully()) {
				ReadMCMData(ini);
			}
		}
	}

	
	void MCMDataLoader::ReadMCMData(STGUtils::MCMSettingsUtil& ini) {
		ini.MoveToSection(INIKey(MCMKeys::_SectionNames::Main));
		m_mcm.vanityModeEnabled = ini.GetBoolValue(INIKey(MCMKeys::Main::bIsVanityEnabled), m_mcm.vanityModeEnabled);

		
		ini.MoveToSection(INIKey(MCMKeys::_SectionNames::Camera));

		ReadCameraOffsetValues(
			ini,
			m_mcm.NoPowerArmor.normal,

			MCMKeys::Camera::Offsets::fNoPA_BaseNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_BaseNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_BaseNormalVertical,
			MCMKeys::Camera::Offsets::fNoPA_BaseNormalForward,

			MCMKeys::Camera::Offsets::fNoPA_BaseSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_BaseSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_BaseSneakVertical,
			MCMKeys::Camera::Offsets::fNoPA_BaseSneakForward
		);

		ReadCameraOffsetValues(
			ini,
			m_mcm.NoPowerArmor.melee,

			MCMKeys::Camera::Offsets::fNoPA_MeleeNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_MeleeNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_MeleeNormalVertical,
			MCMKeys::Camera::Offsets::fNoPA_MeleeNormalForward,

			MCMKeys::Camera::Offsets::fNoPA_MeleeSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_MeleeSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_MeleeSneakVertical,
			MCMKeys::Camera::Offsets::fNoPA_MeleeSneakForward
		);

		ReadCameraOffsetValues(
			ini,
			m_mcm.NoPowerArmor.ranged,

			MCMKeys::Camera::Offsets::fNoPA_RangedNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_RangedNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_RangedNormalVertical,
			MCMKeys::Camera::Offsets::fNoPA_RangedNormalForward,

			MCMKeys::Camera::Offsets::fNoPA_RangedSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_RangedSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_RangedSneakVertical,
			MCMKeys::Camera::Offsets::fNoPA_RangedSneakForward
		);

		m_mcm.miscNoPASettings.cameraMinDist = ini.GetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_CamMinDist), m_mcm.miscNoPASettings.cameraMinDist);
		m_mcm.miscNoPASettings.cameraMaxDist = ini.GetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_CamMaxDist), m_mcm.miscNoPASettings.cameraMaxDist);

		m_mcm.miscNoPASettings.cameraZoomSpeed = ini.GetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_MouseWheelZoomSpeed), m_mcm.miscNoPASettings.cameraZoomSpeed);
		m_mcm.miscNoPASettings.cameraZoomInterpolationIncrement = ini.GetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_MouseWheelIncrement), m_mcm.miscNoPASettings.cameraZoomInterpolationIncrement);


		ReadCameraOffsetValues(
			ini,
			m_mcm.InPowerArmor.normal,

			MCMKeys::Camera::Offsets::fInPA_BaseNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_BaseNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_BaseNormalVertical,
			MCMKeys::Camera::Offsets::fInPA_BaseNormalForward,

			MCMKeys::Camera::Offsets::fInPA_BaseSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_BaseSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_BaseSneakVertical,
			MCMKeys::Camera::Offsets::fInPA_BaseSneakForward
		);

		ReadCameraOffsetValues(
			ini,
			m_mcm.InPowerArmor.melee,

			MCMKeys::Camera::Offsets::fInPA_MeleeNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_MeleeNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_MeleeNormalVertical,
			MCMKeys::Camera::Offsets::fInPA_MeleeNormalForward,

			MCMKeys::Camera::Offsets::fInPA_MeleeSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_MeleeSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_MeleeSneakVertical,
			MCMKeys::Camera::Offsets::fInPA_MeleeSneakForward
		);

		ReadCameraOffsetValues(
			ini,
			m_mcm.InPowerArmor.ranged,

			MCMKeys::Camera::Offsets::fInPA_RangedNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_RangedNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_RangedNormalVertical,
			MCMKeys::Camera::Offsets::fInPA_RangedNormalForward,

			MCMKeys::Camera::Offsets::fInPA_RangedSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_RangedSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_RangedSneakVertical,
			MCMKeys::Camera::Offsets::fInPA_RangedSneakForward
		);

		m_mcm.miscInPASettings.cameraMinDist = ini.GetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_CamMinDist), m_mcm.miscInPASettings.cameraMinDist);
		m_mcm.miscInPASettings.cameraMaxDist = ini.GetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_CamMaxDist), m_mcm.miscInPASettings.cameraMaxDist);

		m_mcm.miscInPASettings.cameraZoomSpeed = ini.GetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_MouseWheelZoomSpeed), m_mcm.miscInPASettings.cameraZoomSpeed);
		m_mcm.miscInPASettings.cameraZoomInterpolationIncrement = ini.GetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_MouseWheelIncrement), m_mcm.miscInPASettings.cameraZoomInterpolationIncrement);


		m_mcm.camera3rdFOV = ini.GetFloatValue(INIKey(MCMKeys::Camera::Misc::fFOV3rdPerson), m_mcm.camera3rdFOV);
		m_mcm.camera3rdAimFOV = ini.GetFloatValue(INIKey(MCMKeys::Camera::Misc::fFOV3rdPersonAiming), m_mcm.camera3rdAimFOV);



		m_mcm.camera1stFOV = ini.GetFloatValue(INIKey(MCMKeys::Camera::Global::fFOV1stPerson), m_mcm.camera1stFOV);
		m_mcm.cameraChangeSpeed = ini.GetFloatValue(INIKey(MCMKeys::Camera::Global::fCamStateChangeSpeed), m_mcm.cameraChangeSpeed);
		m_mcm.cameraPitchZoom = ini.GetFloatValue(INIKey(MCMKeys::Camera::Global::fCamPitchZoomValue), m_mcm.cameraPitchZoom);
	}



	void MCMDataLoader::WriteMCMData(STGUtils::MCMSettingsUtil& ini) {
		ini.MoveToSection(INIKey(MCMKeys::_SectionNames::Main));
		ini.SetBoolValue(INIKey(MCMKeys::Main::bIsVanityEnabled), m_mcm.vanityModeEnabled);

		
		ini.MoveToSection(INIKey(MCMKeys::_SectionNames::Camera));

		WriteCameraOffsetValues(
			ini,
			m_mcm.NoPowerArmor.normal,

			MCMKeys::Camera::Offsets::fNoPA_BaseNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_BaseNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_BaseNormalVertical,
			MCMKeys::Camera::Offsets::fNoPA_BaseNormalForward,

			MCMKeys::Camera::Offsets::fNoPA_BaseSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_BaseSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_BaseSneakVertical,
			MCMKeys::Camera::Offsets::fNoPA_BaseSneakForward
		);

		WriteCameraOffsetValues(
			ini,
			m_mcm.NoPowerArmor.melee,

			MCMKeys::Camera::Offsets::fNoPA_MeleeNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_MeleeNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_MeleeNormalVertical,
			MCMKeys::Camera::Offsets::fNoPA_MeleeNormalForward,

			MCMKeys::Camera::Offsets::fNoPA_MeleeSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_MeleeSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_MeleeSneakVertical,
			MCMKeys::Camera::Offsets::fNoPA_MeleeSneakForward
		);

		WriteCameraOffsetValues(
			ini,
			m_mcm.NoPowerArmor.ranged,

			MCMKeys::Camera::Offsets::fNoPA_RangedNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_RangedNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_RangedNormalVertical,
			MCMKeys::Camera::Offsets::fNoPA_RangedNormalForward,

			MCMKeys::Camera::Offsets::fNoPA_RangedSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fNoPA_RangedSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fNoPA_RangedSneakVertical,
			MCMKeys::Camera::Offsets::fNoPA_RangedSneakForward
		);

		ini.SetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_CamMinDist), m_mcm.miscNoPASettings.cameraMinDist);
		ini.SetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_CamMaxDist), m_mcm.miscNoPASettings.cameraMaxDist);

		ini.SetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_MouseWheelZoomSpeed), m_mcm.miscNoPASettings.cameraZoomSpeed);
		ini.SetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_MouseWheelIncrement), m_mcm.miscNoPASettings.cameraZoomInterpolationIncrement);


		WriteCameraOffsetValues(
			ini,
			m_mcm.InPowerArmor.normal,

			MCMKeys::Camera::Offsets::fInPA_BaseNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_BaseNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_BaseNormalVertical,
			MCMKeys::Camera::Offsets::fInPA_BaseNormalForward,

			MCMKeys::Camera::Offsets::fInPA_BaseSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_BaseSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_BaseSneakVertical,
			MCMKeys::Camera::Offsets::fInPA_BaseSneakForward
		);

		WriteCameraOffsetValues(
			ini,
			m_mcm.InPowerArmor.melee,

			MCMKeys::Camera::Offsets::fInPA_MeleeNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_MeleeNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_MeleeNormalVertical,
			MCMKeys::Camera::Offsets::fInPA_MeleeNormalForward,

			MCMKeys::Camera::Offsets::fInPA_MeleeSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_MeleeSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_MeleeSneakVertical,
			MCMKeys::Camera::Offsets::fInPA_MeleeSneakForward
		);

		WriteCameraOffsetValues(
			ini,
			m_mcm.InPowerArmor.ranged,

			MCMKeys::Camera::Offsets::fInPA_RangedNormalHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_RangedNormalHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_RangedNormalVertical,
			MCMKeys::Camera::Offsets::fInPA_RangedNormalForward,

			MCMKeys::Camera::Offsets::fInPA_RangedSneakHorizontalLeft,
			MCMKeys::Camera::Offsets::fInPA_RangedSneakHorizontalRight,
			MCMKeys::Camera::Offsets::fInPA_RangedSneakVertical,
			MCMKeys::Camera::Offsets::fInPA_RangedSneakForward
		);

		ini.SetFloatValue(INIKey(MCMKeys::Camera::Misc::fInPA_CamMinDist), m_mcm.miscInPASettings.cameraMinDist);
		ini.SetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_CamMaxDist), m_mcm.miscInPASettings.cameraMaxDist);

		ini.SetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_MouseWheelZoomSpeed), m_mcm.miscInPASettings.cameraZoomSpeed);
		ini.SetFloatValue(INIKey(MCMKeys::Camera::Misc::fNoPA_MouseWheelIncrement), m_mcm.miscInPASettings.cameraZoomInterpolationIncrement);


		ini.SetFloatValue(INIKey(MCMKeys::Camera::Misc::fFOV3rdPerson), m_mcm.camera3rdFOV);
		ini.SetFloatValue(INIKey(MCMKeys::Camera::Misc::fFOV3rdPersonAiming), m_mcm.camera3rdAimFOV);



		ini.SetFloatValue(INIKey(MCMKeys::Camera::Global::fFOV1stPerson), m_mcm.camera1stFOV);
		ini.SetFloatValue(INIKey(MCMKeys::Camera::Global::fCamStateChangeSpeed), m_mcm.cameraChangeSpeed);
		ini.SetFloatValue(INIKey(MCMKeys::Camera::Global::fCamPitchZoomValue), m_mcm.cameraPitchZoom);
	}
}
