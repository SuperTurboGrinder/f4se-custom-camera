#include "Utils/MCMSettingsUtil.h"

namespace STGUtils {
    const char* const SIErrProxy[] {
        "Inserted", //2
        "Updated",
        "Ok",
        "Fail",
        "NoMem",
        "FileErr" //-3
    };
    const char* const errname(SI_Error status) {
        return (status <= 2 && status >= -3)
        ? SIErrProxy[5 - (status+3)] : "Unknown";
    }

    MCMSettingsUtil::MCMSettingsUtil(std::string_view fileName) {
        filePath = std::format("Data/MCM/Settings/{}.ini", fileName);
        REX::INFO("Reading MCM settings from: {}", filePath.c_str());
        auto status = ini.LoadFile(filePath.c_str());
        initialized = status >= 0;
        if(initialized)  {
			REX::INFO("Succesfully read MCM config ini. Operation status {}", errname(status));
        } else {
			REX::ERROR("Could not read MCM ini. Operation status {}", errname(status));
            if(status == -3) {
			    REX::ERROR("File error type: {}", std::strerror(errno));
            }
        }
    }

    bool MCMSettingsUtil::SaveFile() {
        auto status = ini.SaveFile(filePath.c_str());
        bool success = status >= 0;
        if(success) {
			REX::INFO("Succesfully written to MCM config ini. Status {}", errname(status));
        } else {
			REX::ERROR("Error writing to MCM config ini. Status {}", errname(status));
            if(status == -3) {
			    REX::ERROR("File error: {}", std::strerror(errno));
            }
        }
        return success;
    }
    
    bool MCMSettingsUtil::IsInitializedSuccesfully() const {
        return initialized;
    }
    
    bool MCMSettingsUtil::FileDoesNotExist() const {
        return std::filesystem::exists(filePath);
    }

    bool MCMSettingsUtil::IsEmpty() const {
        return ini.IsEmpty();
    }

    void MCMSettingsUtil::MoveToSection(const char* const _sectionName) {
        sectionName = _sectionName;
    }

    float MCMSettingsUtil::GetFloatValue(const char* const key, float defaultValue) const {
        return (float)ini.GetDoubleValue(sectionName, key, defaultValue);
    }
    bool MCMSettingsUtil::GetBoolValue(const char* const key, bool defaultValue) const {
        return ini.GetBoolValue(sectionName, key, defaultValue);
    }

    void MCMSettingsUtil::SetFloatValue(const char* const key, float defaultValue) {
        ini.SetDoubleValue(sectionName, key, defaultValue);
    }
    void MCMSettingsUtil::SetBoolValue(const char* const key, bool defaultValue) {
        ini.SetBoolValue(sectionName, key, defaultValue);
    }
}