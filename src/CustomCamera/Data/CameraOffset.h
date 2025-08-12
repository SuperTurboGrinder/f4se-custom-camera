#pragma once 

namespace CustomCamera::Data {
    struct CameraOffset {
        float horizontal    {0};
        float vertical      {0};
        float forward       {0};
    };

    struct CameraOffsetsSet {
        CameraOffset normalOffsets;
        CameraOffset meleeOffsets;
        CameraOffset rangedOffsets;

        inline void SetFromLerp(const CameraOffsetsSet& from, const CameraOffsetsSet& to, float scale) {
            scale = std::clamp(scale, 0.0f, 1.0f);
            normalOffsets = LerpOffset(from.normalOffsets, to.normalOffsets, scale);
            meleeOffsets = LerpOffset(from.meleeOffsets, to.meleeOffsets, scale);
            rangedOffsets = LerpOffset(from.rangedOffsets, to.rangedOffsets, scale);
        }

        private:
            inline CameraOffset LerpOffset(const CameraOffset& from, const CameraOffset& to, float scale) const {
                float _1minus = 1-scale;
                return CameraOffset {
                    .horizontal = from.horizontal*_1minus + to.horizontal*scale,
                    .vertical = from.vertical*_1minus + to.vertical*scale,
                    .forward = from.forward*_1minus + to.forward*scale,
                };
            }
    };
}