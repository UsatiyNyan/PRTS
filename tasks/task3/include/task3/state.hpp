#pragma once

#include "mission.hpp"
#include "pose.hpp"
#include <memory>

namespace task3 {
class State {
public:
    State(Pose pose, std::shared_ptr<Mission> prev_mission);

    Pose prev_pose() const;
    Pose pose() const;
    std::shared_ptr<Mission> prev_mission() const;

private:
    Pose prev_pose_;
    Pose pose_;
    std::shared_ptr<Mission> prev_mission_;
};
}// namespace task3


template<>
struct fmt::formatter<task3::State> : formatter<std::string> {
    template<typename FormatContext>
    auto format(const task3::State& state, FormatContext& ctx) {
        std::string string;
        if (state.prev_mission()) {
            string = state.prev_mission()->prompt() + '\n';
        }
        string += fmt::format("Текущее положение: {}", state.pose());
        return formatter<std::string>::format(string, ctx);
    }
};
