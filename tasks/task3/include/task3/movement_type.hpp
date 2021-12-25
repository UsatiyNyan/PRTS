#pragma once

#include <fmt/format.h>
#include <nlohmann/json.hpp>

namespace task3 {
class MovementType {
public:
    enum class Enum { NONE,
                      SPIRAL,
                      VERTICAL };

public:
    explicit MovementType(Enum an_enum = Enum::NONE);
    explicit MovementType(const std::string& string);
    explicit MovementType(const nlohmann::json& json);

    nlohmann::json to_json() const;

    Enum operator*() const;

private:
    Enum enum_;
};
}// namespace task3

template<>
struct fmt::formatter<task3::MovementType> : formatter<string_view> {
    template<typename FormatContext>
    auto format(task3::MovementType movement_type, FormatContext& ctx) {
        string_view name;
        switch (*movement_type) {
            case task3::MovementType::Enum::NONE:
                name = "никак";
                break;
            case task3::MovementType::Enum::SPIRAL:
                name = "по спирали";
                break;
            case task3::MovementType::Enum::VERTICAL:
                name = "вертикально";
                break;
        }
        return formatter<string_view>::format(name, ctx);
    }
};
