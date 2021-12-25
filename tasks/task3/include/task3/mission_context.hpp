#pragma once

#include "pose.hpp"
#include <nlohmann/json.hpp>

namespace task3 {
class MissionException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class MissionContext {
public:
    MissionContext(Pose initial_pose, Pose min_pose, Pose max_pose) : initial_pose_{initial_pose}, min_pose_{min_pose}, max_pose_{max_pose} {}
    explicit MissionContext(const nlohmann::json& json) : initial_pose_{json["initial_pose"]}, min_pose_{json["min_pose"]}, max_pose_{json["max_pose"]} {}

    void validate(const Pose& new_pose) const;
    Pose initial_pose() const;
    nlohmann::json to_json() const {
        return nlohmann::json{
                {"initial_pose", initial_pose_.to_json()},
                {"min_pose", min_pose_.to_json()},
                {"max_pose", max_pose_.to_json()}
        };
    }

private:
    Pose initial_pose_;
    Pose min_pose_;
    Pose max_pose_;
};
}// namespace task3
