#pragma once

#include "MCM/CameraOffsetSettings.h"

namespace CustomCamera::MCM {
    struct Data {
        struct CameraOffsetsSettings {
            CameraOffsetSettings standing;
            CameraOffsetSettings sneaking;
        };

        struct CameraOffsetsSet {
            CameraOffsetsSettings normal;
            CameraOffsetsSettings melee;
            CameraOffsetsSettings ranged;
        };

        struct MiscCameraSettings {
            float cameraMinDist{ 50.0f };
            float cameraMaxDist{ 150.0f };

            float cameraZoomSpeed{ 3.0f };
            float cameraZoomInterpolationIncrement{ 0.075f };
        };
        
        //{horizontalLeft, horizontalRight, vertical, forward}
        //camera while zoomed out
        CameraOffsetsSet NoPowerArmor = {
            .normal = {
                .standing = {0.0f, 0.0f, 0.0f, 0.0f},
                .sneaking = {0.0f, 0.0f, 0.0f, 0.0f}
            },
            .melee = {
                .standing = {-80.0f, 80.0f, 0.0f, 0.0f},
                .sneaking = {-80.0f, 80.0f, 0.0f, 0.0f}
            },
            .ranged = {
                .standing = {-80.0f, 80.0f, 0.0f, 0.0f},
                .sneaking = {-80.0f, 80.0f, 0.0f, 0.0f}
            },
        };
        CameraOffsetsSet InPowerArmor = {
            .normal = {
                .standing = {0.0f, 0.0f, 0.0f, 0.0f},
                .sneaking = {0.0f, 0.0f, 0.0f, 0.0f}
            },
            .melee = {
                .standing = {-50.0f, 50.0f, 0.0f, 0.0f},
                .sneaking = {-50.0f, 50.0f, 0.0f, 0.0f}
            },
            .ranged = {
                .standing = {-50.0f, 50.0f, 0.0f, 0.0f},
                .sneaking = {-50.0f, 50.0f, 0.0f, 0.0f}
            },
        };

        
        //camera while zoomed in
        CameraOffsetsSet NoPowerArmorClose = {
            .normal = {
                .standing = {0.0f, 0.0f, 0.0f, 0.0f},
                .sneaking = {0.0f, 0.0f, 0.0f, 0.0f}
            },
            .melee = {
                .standing = {-10.0f, 10.0f, 0.0f, 0.0f},
                .sneaking = {-10.0f, 10.0f, 0.0f, 0.0f}
            },
            .ranged = {
                .standing = {-10.0f, 10.0f, 0.0f, 0.0f},
                .sneaking = {-10.0f, 10.0f, 0.0f, 0.0f}
            },
        };
        CameraOffsetsSet InPowerArmorClose = {
            .normal = {
                .standing = {0.0f, 0.0f, 0.0f, 0.0f},
                .sneaking = {0.0f, 0.0f, 0.0f, 0.0f}
            },
            .melee = {
                .standing = {-20.0f, 20.0f, 0.0f, 0.0f},
                .sneaking = {-20.0f, 20.0f, 0.0f, 0.0f}
            },
            .ranged = {
                .standing = {-20.0f, 20.0f, 0.0f, 0.0f},
                .sneaking = {-20.0f, 20.0f, 0.0f, 0.0f}
            },
        };


        bool vanityModeEnabled{ true };

        //{minDist, maxDist, speed, zoomIncrement}
        MiscCameraSettings miscNoPASettings = {
            50.0f, 150.0f, 3.0f, 0.075f
        };
        MiscCameraSettings miscInPASettings = {
            50.0f, 150.0f, 3.0f, 0.075f
        };



        float camera1stFOV{ 75.0f };
        float camera3rdFOV{ 75.0f };
        float camera3rdAimFOV{ 75.0f };

        float cameraChangeSpeed{ 3.0f };
        float cameraPitchZoom{ 0.0f };
    };
}