#pragma once

#include <fmt/format.h>
#include <nlohmann/json.hpp>

namespace task3 {
class DepthType {
public:
    enum class Enum { NONE,
                      FLOOR_RELATIVE,
                      SURFACE_RELATIVE };

public:
    explicit DepthType(Enum an_enum = Enum::NONE);
    explicit DepthType(const std::string& string);
    explicit DepthType(const nlohmann::json& json);

    nlohmann::json to_json() const;

    Enum operator*() const;

private:
    Enum enum_;
};
}// namespace task3

template<>
struct fmt::formatter<task3::DepthType> : formatter<string_view> {
    template<typename FormatContext>
    auto format(task3::DepthType depth_type, FormatContext& ctx) {
        string_view name;
        switch (*depth_type) {
            case task3::DepthType::Enum::NONE:
                name = "никак";
                break;
            case task3::DepthType::Enum::FLOOR_RELATIVE:
                name = "относительно дна";
                break;
            case task3::DepthType::Enum::SURFACE_RELATIVE:
                name = "по датчику глубины";
                break;
        }
        return formatter<string_view>::format(name, ctx);
    }
};
