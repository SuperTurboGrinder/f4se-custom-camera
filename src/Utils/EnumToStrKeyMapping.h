#pragma once

////
////                    (ノ_<。)
////

#define MAP_ENUM(val) val,
#define MAP_STRS(str) #str,

#define KEY_CONTAINER_AREA_SECTION_START(className, sectionName) \
        public: struct sectionName {\
            friend class className;

#define KEY_CONTAINER_AREA_SECTION_END };\

#define KEY_CONTAINER_AREA(mapping, name)\
        private:\
            static const char* const Str ##name[];\
        public:\
            enum class name{\
                mapping\
            };\

#define KEY_ACCESSOR(name)\
        public:\
            static constexpr const char* const INIKey(name id) { return Str ##name[std::to_underlying(id)]; }

#define KEY_ACCESSOR_FROM_SECTION(section, name)\
        public:\
            static constexpr const char* const INIKey(section##::##name id) { return section##::Str ##name[std::to_underlying(id)]; }

#define STR_KEY_ARRAY_INITIALIZER(className, name, mapping)\
    const char* const className##::Str##name[] {\
        mapping\
    };

#define STR_KEY_ARRAY_INITIALIZER_FROM_SECTION(className, SectionName, name, mapping)\
    const char* const className##::##SectionName##::Str##name[] {\
        mapping\
    };