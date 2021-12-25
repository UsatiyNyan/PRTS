#include "task3/mission_storage.hpp"
#include <iostream>
#include <utility>

namespace task3 {
MissionStorage::MissionStorage(std::shared_ptr<MissionContext> context)
    : context_{std::move(context)} {
}

MissionStorage::MissionStorage(std::shared_ptr<MissionContext> context, const nlohmann::json& json)
    : context_{std::move(context)} {
    //
    Pose last_pose = context_->initial_pose();
    for (const auto& mission : json) {
        State state{last_pose, mission_from_json(mission)};
        last_pose = state.pose();
        states_.push_back(std::move(state));
    }
}

nlohmann::json MissionStorage::to_json() const {
    auto json = nlohmann::json::array();
    for (const auto& state : states_) {
        auto mission = state.prev_mission();
        if (!mission) {
            continue;
        }
        nlohmann::json mission_json;
        mission_json["type"] = mission->type();
        mission_json["args"] = mission->to_json();
        json.push_back(std::move(mission_json));
    }
    return json;
}

void MissionStorage::add(std::shared_ptr<Mission> mission) {
    Pose pose{};
    if (states_.empty()) {
        pose = context_->initial_pose();
    } else {
        pose = states_.back().pose();
    }
    states_.emplace_back(pose, std::move(mission));
}

void MissionStorage::insert(size_t i, std::shared_ptr<Mission> mission) {
    auto it = states_.begin();
    std::advance(it, i);
    if (it == states_.begin()) {
        add(std::move(mission));
    } else {
        update(states_.insert(it, State{it->prev_pose(), std::move(mission)}));
    }
}

void MissionStorage::erase(size_t i) {
    auto it = states_.begin();
    std::advance(it, i);
    update(states_.erase(it));
}

void MissionStorage::iter_swap(size_t i, size_t j) {
    auto i_it = states_.begin();
    auto j_it = states_.begin();
    std::advance(i_it, i);
    std::advance(j_it, j);
    std::iter_swap(i_it, j_it);
    update(i < j ? i_it : j_it);
}

void MissionStorage::replace(size_t i, std::shared_ptr<Mission> mission) {
    auto it = states_.begin();
    std::advance(it, i);
    *it = State{it->prev_pose(), std::move(mission)};
    update(it);
}

std::shared_ptr<Mission> MissionStorage::mission_from_json(const nlohmann::json& json) {
    auto type = json["type"].get<std::string>();
    auto args = json["args"];
    if (type == "Dive") {
        return std::make_shared<Dive>(context_, args);
    } else if (type == "Lift") {
        return std::make_shared<Lift>(context_, args);
    } else if (type == "Move") {
        return std::make_shared<Move>(context_, args);
    } else if (type == "Return") {
        return std::make_shared<Return>(context_, args);
    }
    return nullptr;
}

void MissionStorage::update(std::list<State>::iterator begin) {
    if (begin == states_.end()) {
        return;
    }
    if (begin == states_.begin()) {
        *begin = State{context_->initial_pose(), begin->prev_mission()};
    }

    Pose pose{begin->prev_pose()};

    for (auto it = begin; it != states_.end(); ++it) {
        *it = State{pose, it->prev_mission()};
        pose = it->pose();
    }
}
}// namespace task3
