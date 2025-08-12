#pragma once

#include <Utils/EnumToStrKeyMapping.h>

namespace CustomCamera::MCM {

    #define SECTION_NAMES(map)\
        map(Main)\
        map(Camera)


    #define KEY_IDS_MAIN(map)\
        map(bIsVanityEnabled)


    #define KEY_IDS_OFFSETS(map)\
        map(fNoPA_BaseNormalHorizontalLeft)\
        map(fNoPA_BaseNormalHorizontalRight)\
        map(fNoPA_BaseNormalVertical)\
        map(fNoPA_BaseNormalForward)\
\
        map(fNoPA_BaseSneakHorizontalLeft)\
        map(fNoPA_BaseSneakHorizontalRight)\
        map(fNoPA_BaseSneakVertical)\
        map(fNoPA_BaseSneakForward)\
\
\
        map(fNoPA_MeleeNormalHorizontalLeft)\
        map(fNoPA_MeleeNormalHorizontalRight)\
        map(fNoPA_MeleeNormalVertical)\
        map(fNoPA_MeleeNormalForward)\
\
        map(fNoPA_MeleeSneakHorizontalLeft)\
        map(fNoPA_MeleeSneakHorizontalRight)\
        map(fNoPA_MeleeSneakVertical)\
        map(fNoPA_MeleeSneakForward)\
\
\
        map(fNoPA_RangedNormalHorizontalLeft)\
        map(fNoPA_RangedNormalHorizontalRight)\
        map(fNoPA_RangedNormalVertical)\
        map(fNoPA_RangedNormalForward)\
\
        map(fNoPA_RangedSneakHorizontalLeft)\
        map(fNoPA_RangedSneakHorizontalRight)\
        map(fNoPA_RangedSneakVertical)\
        map(fNoPA_RangedSneakForward)\
\
\
\
\
        map(fInPA_BaseNormalHorizontalLeft)\
        map(fInPA_BaseNormalHorizontalRight)\
        map(fInPA_BaseNormalVertical)\
        map(fInPA_BaseNormalForward)\
\
        map(fInPA_BaseSneakHorizontalLeft)\
        map(fInPA_BaseSneakHorizontalRight)\
        map(fInPA_BaseSneakVertical)\
        map(fInPA_BaseSneakForward)\
\
\
        map(fInPA_MeleeNormalHorizontalLeft)\
        map(fInPA_MeleeNormalHorizontalRight)\
        map(fInPA_MeleeNormalVertical)\
        map(fInPA_MeleeNormalForward)\
\
        map(fInPA_MeleeSneakHorizontalLeft)\
        map(fInPA_MeleeSneakHorizontalRight)\
        map(fInPA_MeleeSneakVertical)\
        map(fInPA_MeleeSneakForward)\
\
\
        map(fInPA_RangedNormalHorizontalLeft)\
        map(fInPA_RangedNormalHorizontalRight)\
        map(fInPA_RangedNormalVertical)\
        map(fInPA_RangedNormalForward)\
\
        map(fInPA_RangedSneakHorizontalLeft)\
        map(fInPA_RangedSneakHorizontalRight)\
        map(fInPA_RangedSneakVertical)\
        map(fInPA_RangedSneakForward)


    #define KEY_IDS_MISC(map)\
        map(fNoPA_CamMinDist)\
        map(fNoPA_CamMaxDist)\
        map(fNoPA_MouseWheelZoomSpeed)\
        map(fNoPA_MouseWheelIncrement)\
\
        map(fInPA_CamMinDist)\
        map(fInPA_CamMaxDist)\
        map(fInPA_MouseWheelZoomSpeed)\
        map(fInPA_MouseWheelIncrement)\
\
        map(fFOV3rdPerson)\
        map(fFOV3rdPersonAiming)


    #define KEY_IDS_GLOBAL(map)\
        map(fFOV1stPerson)\
        map(fCamStateChangeSpeed)\
        map(fCamPitchZoomValue)


    class MCMKeys {
        KEY_CONTAINER_AREA(SECTION_NAMES(MAP_ENUM), _SectionNames)

        KEY_CONTAINER_AREA(KEY_IDS_MAIN(MAP_ENUM), Main)

        KEY_CONTAINER_AREA_SECTION_START(MCMKeys, Camera)
            KEY_CONTAINER_AREA(KEY_IDS_OFFSETS(MAP_ENUM), Offsets)
            KEY_CONTAINER_AREA(KEY_IDS_MISC(MAP_ENUM), Misc)
            KEY_CONTAINER_AREA(KEY_IDS_GLOBAL(MAP_ENUM), Global)
        KEY_CONTAINER_AREA_SECTION_END


        KEY_ACCESSOR(_SectionNames)
        KEY_ACCESSOR(Main)
        KEY_ACCESSOR_FROM_SECTION(Camera, Offsets)
        KEY_ACCESSOR_FROM_SECTION(Camera, Misc)
        KEY_ACCESSOR_FROM_SECTION(Camera, Global)
    };

    template<typename Enum>
    const char* const INIKey(Enum key) {
        return MCMKeys::INIKey(key);
    }

}
