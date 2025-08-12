#pragma once

#include <Utils/GameINIValueUpdater.h>
#include "Data/CameraOffset.h"
#include "Data/CameraStateSwitches.h"
#include "MCM/MCMDataLoader.h"

namespace CustomCamera {
    using Data::SneakingSwitch;
    using Data::ShoulderSwitch;

    class CameraStateProcessor {
        public:
            void UpdateAndApply();

            bool IsLeftShoulder();
            void setIsLeftShoulder(bool _isLeftShoulder);
            void ResetToRightShoulder();
            void SwitchShoulder();
            void SetSneakingAndApply(bool _isSneaking);
            void InterpolateFarAndCloseSettingsAndApply(float value);

        private:
            void UpdateIntermediateCameraOffsets(const MCM::Data& mcm, bool isInPowerArmor);
            void UpdateInterpolatedCameraOffsets();
            void UpdateRangedAimZoom();
            void UpdateFOV(const MCM::Data& mcm);
            void UpdateMiscCameraSettings(const MCM::Data& mcm, bool isInPowerArmor);
            
            Data::CameraOffset OffsetSettingsToOffset(const MCM::Data::CameraOffsetsSettings& settings) const;
            Data::CameraOffsetsSet OffsetSettingsSetToOffsetSet(const MCM::Data::CameraOffsetsSet& settingsSet) const;

            void ApplyToGameSettings();
            void ApplyOffsetsToGameSettings(STGUtils::GameINIValueUpdater& gameSettings);
            void ApplyOtherGameSettings(STGUtils::GameINIValueUpdater& gameSettings);

            struct VanityModeSettings {
                bool isEnabled;
                float distanceMin;
                float distanceMax;
            };
            struct MouseWheelZoomSettings {
                float cameraZoomSpeed;
                float interpolationIncrement;
            };
            struct FOVSettings {
                float cam3rdPersonFOV;
                float cam3rdPersonAimFOV;
                float cam1stPersonFOV;
            };


        private:
            ShoulderSwitch shoulder { ShoulderSwitch::Right };
            SneakingSwitch isSneaking { SneakingSwitch::Standing };

            float gameCameraDistanceFromCharacterScale {0};

            VanityModeSettings vanityModeSettings;
            MouseWheelZoomSettings mouseWheelZoomSettings;
            FOVSettings fieldOfViewSettings;

            Data::CameraOffsetsSet farBackward;
            Data::CameraOffsetsSet closeForward;
            Data::CameraOffsetsSet interpolatedOffsets;

            float m_cameraChangeSpeed;
            float m_cameraPitchZoom;

            float m_camera3rdPersonAimDist;
    };
}