#pragma once

#include "state.hpp"
#include <list>

namespace task3 {
class MissionStorage {
public:
    explicit MissionStorage(std::shared_ptr<MissionContext> context);

    MissionStorage(std::shared_ptr<MissionContext> context, const nlohmann::json& json);
    nlohmann::json to_json() const;

    const std::list<State>& states() const { return states_; }

    void add(std::shared_ptr<Mission> mission);
    void insert(size_t i, std::shared_ptr<Mission> mission);
    void erase(size_t i);
    void iter_swap(size_t i, size_t j);
    void replace(size_t i, std::shared_ptr<Mission> mission);

private:
    void update(std::list<State>::iterator begin);

    std::shared_ptr<Mission> mission_from_json(const nlohmann::json& json);

private:
    std::shared_ptr<MissionContext> context_;
    std::list<State> states_;
};
}// namespace task3
