#pragma once

#include "MCM/Data.h"
#include "Utils/MCMSettingsUtil.h"
#include "MCM/MCM_INI_KeyMapping.h"

namespace CustomCamera::MCM {
	class MCMDataLoader :
		public REX::Singleton<MCMDataLoader>
	{
	public:
		void Load();

		Data& GetMCM() { return m_mcm; }
	private:
		Data m_mcm;

		void ReadMCMData(STGUtils::MCMSettingsUtil& ini);
		void WriteMCMData(STGUtils::MCMSettingsUtil& ini);

		void ReadCameraOffsetValues(
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
		);
		void WriteCameraOffsetValues(
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
		);
	};
}
