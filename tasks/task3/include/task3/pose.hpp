#pragma once

#include <fmt/format.h>
#include <nlohmann/json.hpp>

namespace task3 {
struct Pose {
    Pose() = default;
    Pose(int x, int y, int depth) : x{x}, y{y}, depth{depth} {}
    explicit Pose(const nlohmann::json& json) : x{json["x"].get<int>()}, y{json["y"].get<int>()}, depth{json["depth"].get<int>()} {}

    int x;
    int y;
    int depth;

    bool operator<(const Pose& other) const {
        return x < other.x || y < other.y || depth < other.depth;
    }

    Pose operator+(const Pose& pose) const {
        return Pose{x + pose.x, y + pose.y, depth + pose.depth};
    }

    nlohmann::json to_json() const {
        return nlohmann::json{{"x", x}, {"y", y}, {"depth", depth}};
    }
};
}// namespace task3


template<>
struct fmt::formatter<task3::Pose> : formatter<std::string> {
    template<typename FormatContext>
    auto format(task3::Pose pose, FormatContext& ctx) {
        return formatter<string_view>::format(fmt::format("x={} y={} глубина={}", pose.x, pose.y, pose.depth), ctx);
    }
};
