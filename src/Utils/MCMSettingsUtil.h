#pragma once

namespace STGUtils {

    //requires SimpleIni.h
    class MCMSettingsUtil {
		CSimpleIniA ini;
        std::string filePath;
        bool initialized = false;
        const char* sectionName = "";
        
        public:
            MCMSettingsUtil(std::string_view fileName);

            bool SaveFile();
            
            bool IsInitializedSuccesfully() const;
            bool FileDoesNotExist() const;
            bool IsEmpty() const;

            void MoveToSection(const char* const _sectionName);

            float GetFloatValue(const char* const key, float defaultValue) const;
            bool GetBoolValue(const char* const key, bool defaultValue) const;

            void SetFloatValue(const char* const key, float defaultValue);
            void SetBoolValue(const char* const key, bool defaultValue);
    };
}