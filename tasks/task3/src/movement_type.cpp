#include "task3/movement_type.hpp"

namespace task3 {
MovementType::MovementType(MovementType::Enum an_enum) : enum_{an_enum} {}

MovementType::MovementType(const std::string& string) : enum_{Enum::NONE} {
    if (string == "SPIRAL") {
        enum_ = Enum::SPIRAL;
    } else if (string == "VERTICAL") {
        enum_ = Enum::VERTICAL;
    }
}

MovementType::MovementType(const nlohmann::json& json) : MovementType{json.get<std::string>()} {}

nlohmann::json MovementType::to_json() const {
    switch (enum_) {
        case Enum::SPIRAL:
            return std::string{"SPIRAL"};
        case Enum::VERTICAL:
            return std::string{"VERTICAL"};
        case Enum::NONE:
            break;
    }
    return std::string{"NONE"};
}

MovementType::Enum MovementType::operator*() const {
    return enum_;
}
}// namespace task3
