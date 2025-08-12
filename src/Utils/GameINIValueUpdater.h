#pragma once

namespace STGUtils {

    class GameINIValueUpdater {
        
        RE::INISettingCollection * ini;

        public:

            GameINIValueUpdater();

            void UpdateValue(std::string_view key, bool value);
            void UpdateValue(std::string_view key, char value);
            void UpdateValue(std::string_view key, float value);
            void UpdateValue(std::string_view key, int value);
            void UpdateValue(std::string_view key, std::span<const std::uint8_t, 3> value);
            void UpdateValue(std::string_view key, std::span<const std::uint8_t, 4> value);
            void UpdateValue(std::string_view key, std::uint8_t value);
            void UpdateValue(std::string_view key, std::uint32_t value);
    };

}
