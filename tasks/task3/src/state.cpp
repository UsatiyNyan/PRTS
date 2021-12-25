#include "task3/state.hpp"

namespace task3 {
State::State(Pose pose, std::shared_ptr<Mission> prev_mission)
    : prev_pose_{pose}, pose_{pose}, prev_mission_{std::move(prev_mission)} {
    //
    if (prev_mission_) {
        pose_ = prev_mission_->execute(pose_);
    }
}

Pose State::prev_pose() const { return prev_pose_; }

Pose State::pose() const { return pose_; }

std::shared_ptr<Mission> State::prev_mission() const { return prev_mission_; }
}// namespace task3
