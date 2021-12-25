#include "task3/mission.hpp"

namespace task3 {
Pose Dive::execute(const Pose& pose) {
    Pose new_pose{pose.x, pose.y, pose.depth + depth_};
    context_->validate(new_pose);
    return new_pose;
}

std::string Dive::prompt() const {
    return fmt::format("Погружение на глубину {} {}, выдерживая глубину {}.", depth_, movement_type_, depth_type_);
}

nlohmann::json Dive::to_json() const {
    return nlohmann::json{
            {"depth", depth_},
            {"movement_type", movement_type_.to_json()},
            {"depth_type", depth_type_.to_json()},
    };
}

std::string Dive::type() const {
    return "Dive";
}

Pose Lift::execute(const Pose& pose) {
    Pose new_pose{pose.x, pose.y, pose.depth - height_};
    context_->validate(new_pose);
    return new_pose;
}

std::string Lift::prompt() const {
    return fmt::format("Подъем на высоту {} {}, выдерживая глубину {}.", height_, movement_type_, depth_type_);
}

nlohmann::json Lift::to_json() const {
    return nlohmann::json{
            {"height", height_},
            {"movement_type", movement_type_.to_json()},
            {"depth_type", depth_type_.to_json()},
    };
}

std::string Lift::type() const {
    return "Lift";
}

Pose Move::execute(const Pose&) {
    context_->validate(new_pose_);
    return new_pose_;
}

std::string Move::prompt() const {
    return fmt::format("Движение в точку ({}) c точностью +-({}).", new_pose_, delta_);
}

nlohmann::json Move::to_json() const {
    return nlohmann::json{
            {"new_pose", new_pose_.to_json()},
            {"delta", delta_.to_json()},
    };
}

std::string Move::type() const {
    return "Move";
}

Pose Return::execute(const Pose&) {
    return context_->initial_pose();
}

std::string Return::prompt() const {
    return fmt::format("Движение в начальную точку ({}).", context_->initial_pose());
}

nlohmann::json Return::to_json() const {
    return {};
}
std::string Return::type() const {
    return "Return";
}
}// namespace task3
