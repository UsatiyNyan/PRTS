#include "task3/mission_context.hpp"

namespace task3 {
void MissionContext::validate(const Pose& new_pose) const {
    if (new_pose < min_pose_ || max_pose_ < new_pose) {
        throw MissionException{"new pose is invalid"};
    }
}

Pose MissionContext::initial_pose() const {
    return initial_pose_;
}
}// namespace task3
