#include "GameINIValueUpdater.h"

namespace STGUtils {

    GameINIValueUpdater::GameINIValueUpdater() {
        ini = RE::INISettingCollection::GetSingleton();
    }

    void GameINIValueUpdater::UpdateValue(std::string_view key, bool value) {
        ini->GetSetting(key)->SetBinary(value);
    }

    void GameINIValueUpdater::UpdateValue(std::string_view key, char value) {
        ini->GetSetting(key)->SetChar(value);
    }

    void GameINIValueUpdater::UpdateValue(std::string_view key, float value) {
        ini->GetSetting(key)->SetFloat(value);
    }

    void GameINIValueUpdater::UpdateValue(std::string_view key, int value) {
        ini->GetSetting(key)->SetInt(value);
    }

    void GameINIValueUpdater::UpdateValue(std::string_view key, std::span<const std::uint8_t, 3> value) {
        ini->GetSetting(key)->SetRGB(value);
    }

    void GameINIValueUpdater::UpdateValue(std::string_view key, std::span<const std::uint8_t, 4> value) {
        ini->GetSetting(key)->SetRGBA(value);
    }

    void GameINIValueUpdater::UpdateValue(std::string_view key, std::uint8_t value) {
        ini->GetSetting(key)->SetUChar(value);
    }

    void GameINIValueUpdater::UpdateValue(std::string_view key, std::uint32_t value) {
        ini->GetSetting(key)->SetUInt(value);
    }

}