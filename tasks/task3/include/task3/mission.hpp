#include "depth_type.hpp"
#include "movement_type.hpp"
#include "pose.hpp"

#include "mission_context.hpp"
#include <fmt/format.h>
#include <memory>
#include <nlohmann/json.hpp>

namespace task3 {
class Mission {
public:
    explicit Mission(std::shared_ptr<MissionContext> context) : context_{std::move(context)} {}
    virtual ~Mission() = default;

    virtual Pose execute(const Pose& pose) = 0;

    virtual std::string prompt() const = 0;
    virtual nlohmann::json to_json() const = 0;
    virtual std::string type() const = 0;

protected:
    std::shared_ptr<MissionContext> context_;
};

class Dive : public Mission {
public:
    Dive(std::shared_ptr<MissionContext> context, int depth, MovementType movement_type, DepthType depth_type)
        : Mission{std::move(context)}, depth_{depth}, movement_type_{movement_type}, depth_type_{depth_type} {}
    Dive(std::shared_ptr<MissionContext> context, const nlohmann::json& json)
        : Mission{std::move(context)}, depth_{json["depth"].get<int>()},
          movement_type_{json["movement_type"]}, depth_type_{json["depth_type"]} {}

    Pose execute(const Pose& pose) override;

    std::string prompt() const override;
    nlohmann::json to_json() const override;
    std::string type() const override;

private:
    int depth_;
    MovementType movement_type_;
    DepthType depth_type_;
};

class Lift : public Mission {
public:
    Lift(std::shared_ptr<MissionContext> context, int height, MovementType movement_type, DepthType depth_type)
        : Mission{std::move(context)}, height_{height}, movement_type_{movement_type}, depth_type_{depth_type} {}
    Lift(std::shared_ptr<MissionContext> context, const nlohmann::json& json)
        : Mission{std::move(context)}, height_{json["height"].get<int>()},
          movement_type_{json["movement_type"]}, depth_type_{json["depth_type"]} {}

    Pose execute(const Pose& pose) override;

    std::string prompt() const override;
    nlohmann::json to_json() const override;
    std::string type() const override;

private:
    int height_;
    MovementType movement_type_;
    DepthType depth_type_;
};

class Move : public Mission {
public:
    Move(std::shared_ptr<MissionContext> context, Pose new_pose, Pose delta) : Mission{std::move(context)}, new_pose_{new_pose}, delta_{delta} {}
    Move(std::shared_ptr<MissionContext> context, const nlohmann::json& json)
        : Mission{std::move(context)}, new_pose_{json["new_pose"]}, delta_{json["delta"]} {}

    Pose execute(const Pose&) override;

    std::string prompt() const override;
    nlohmann::json to_json() const override;
    std::string type() const override;

private:
    Pose new_pose_;
    Pose delta_;
};

class Return : public Mission {
public:
    explicit Return(std::shared_ptr<MissionContext> context) : Mission{std::move(context)} {}
    Return(std::shared_ptr<MissionContext> context, const nlohmann::json&) : Mission{std::move(context)} {}

    Pose execute(const Pose&) override;

    std::string prompt() const override;
    nlohmann::json to_json() const override;
    std::string type() const override;
};
}// namespace task3
