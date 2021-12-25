#include "task3/depth_type.hpp"

namespace task3 {
DepthType::DepthType(DepthType::Enum an_enum) : enum_{an_enum} {}

DepthType::DepthType(const std::string& string) : enum_{Enum::NONE} {
    if (string == "SURFACE_RELATIVE") {
        enum_ = Enum::SURFACE_RELATIVE;
    } else if (string == "FLOOR_RELATIVE") {
        enum_ = Enum::FLOOR_RELATIVE;
    }
}

DepthType::DepthType(const nlohmann::json& json) : DepthType{json.get<std::string>()} {}

nlohmann::json DepthType::to_json() const {
    switch (enum_) {
        case Enum::FLOOR_RELATIVE:
            return std::string{"FLOOR_RELATIVE"};
        case Enum::SURFACE_RELATIVE:
            return std::string{"SURFACE_RELATIVE"};
        case Enum::NONE:
            break;
    }
    return std::string{"NONE"};
}

DepthType::Enum DepthType::operator*() const {
    return enum_;
}
}// namespace task3
