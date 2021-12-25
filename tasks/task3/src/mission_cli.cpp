#include "task3/mission_cli.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

namespace task3 {
class EndSessionException : public std::runtime_error {
public:
    EndSessionException() : std::runtime_error{"Сессия закончена."} {}
};

namespace {
template<typename T>
void extract_from_cin(const std::string& prompt, T& item) {
    std::cout << prompt << ": ";
    if (!(std::cin >> item)) {
        throw EndSessionException{};
    }
}

template<>
void extract_from_cin<Pose>(const std::string& prompt, Pose& item) {
    std::cout << prompt << " (формат: x, y, depth): ";
    if (!(std::cin >> item.x >> item.y >> item.depth)) {
        throw EndSessionException{};
    }
}

template<>
void extract_from_cin<MovementType>(const std::string&, MovementType& item) {
    std::string item_str;
    extract_from_cin("Тип вертикального движения (SPIRAL|VERTICAL)", item_str);
    item = MovementType{item_str};
}

template<>
void extract_from_cin<DepthType>(const std::string&, DepthType& item) {
    std::string item_str;
    extract_from_cin("Тип отслеживания глубины (FLOOR_RELATIVE|SURFACE_RELATIVE)", item_str);
    item = DepthType{item_str};
}

void handle_impl(const std::map<std::string, std::function<void()>>& tasks) {
    std::vector<std::string> commands;
    commands.reserve(tasks.size());
    for (const auto& [command, _] : tasks) {
        commands.push_back(command);
    }
    std::string command;
    extract_from_cin(fmt::format("Введите команду ({})", fmt::join(commands, "|")), command);
    auto exec_it = tasks.find(command);
    if (exec_it != tasks.end()) {
        exec_it->second();
    } else {
        fmt::print("Не верная команда: \"{}\"\n", command);
    }
}
}// namespace

MissionCLI::MissionCLI()
    : file_path_{"mission.json"},
      init_tasks_{{"new", [this] {
                       extract_from_cin("Путь до нового файла миссий", file_path_);
                       if (file_path_.string().rfind(".json") == std::string::npos) {
                           file_path_ = std::filesystem::path{fmt::format("{}.json", file_path_.string())};
                       }
                       Pose initial_pose{};
                       Pose min_pose{};
                       Pose max_pose{};
                       extract_from_cin("Начальная точка", initial_pose);
                       extract_from_cin("Минимальная граница", min_pose);
                       extract_from_cin("Максимальная граница", max_pose);
                       context_ = std::make_shared<MissionContext>(initial_pose, min_pose, max_pose);
                       storage_ = std::make_unique<MissionStorage>(context_);
                   }},
                  {"load", [this] {
                       extract_from_cin("Путь до файла миссий", file_path_);
                       std::ifstream mission_file{file_path_};
                       nlohmann::json json = nlohmann::json::parse(mission_file);
                       context_ = std::make_shared<MissionContext>(json["context"]);
                       storage_ = std::make_unique<MissionStorage>(context_, json["missions"]);
                   }}},
      exec_tasks_{{"add", [this] {
                       safe_handle([this] {
                           std::shared_ptr<Mission> mission;
                           extract_mission_from_cin("Введите миссию", mission);
                           storage_->add(mission);
                       });
                   }},
                  {"insert", [this] {
                       safe_handle([this] {
                           size_t i = 0;
                           extract_from_cin("Введите id", i);
                           std::shared_ptr<Mission> mission;
                           extract_mission_from_cin("Введите миссию", mission);
                           storage_->insert(i, mission);
                       });
                   }},
                  {"delete", [this] {
                       safe_handle([this] {
                           size_t i = 0;
                           extract_from_cin("Введите id", i);
                           storage_->erase(i);
                       });
                   }},
                  {"replace", [this] {
                       safe_handle([this] {
                           size_t i = 0;
                           extract_from_cin("Введите id", i);
                           std::shared_ptr<Mission> mission;
                           extract_mission_from_cin("Введите миссию", mission);
                           storage_->replace(i, mission);
                       });
                   }},
                  {"swap", [this] {
                       safe_handle([this] {
                           size_t i = 0;
                           extract_from_cin("Введите первый id", i);
                           size_t j = 0;
                           extract_from_cin("Введите второй id", j);
                           storage_->iter_swap(i, j);
                       });
                   }},
                  {"save", [this] {
                       std::string new_file_path;
                       extract_from_cin(fmt::format("Путь к файлу(если \"-\", то {})", file_path_.string()), new_file_path);
                       if (new_file_path != "-") {
                           file_path_ = new_file_path;
                       }
                       save();
                   }},
                  {"print", [this] { print(); }},
                  {"end", [] { throw EndSessionException{}; }}} {}

int MissionCLI::run() {
    try {
        while (!init()) {}
        while (true) { exec(); }
    } catch (const EndSessionException& e) {
        std::cout << e.what() << std::endl;
    }

    save();

    return 0;
}

bool MissionCLI::init() {
    handle_impl(init_tasks_);
    return bool{storage_};
}

void MissionCLI::exec() {
    handle_impl(exec_tasks_);
}

void MissionCLI::save() {
    if (storage_) {
        nlohmann::json json;
        json["context"] = context_->to_json();
        json["missions"] = storage_->to_json();
        std::ofstream{file_path_} << json.dump(2) << std::endl;
    } else {
        std::cout << "Не инициализирована коллекция миссий" << std::endl;
    }
}

void MissionCLI::print() {
    fmt::print("Начальное положение: {}\n--------------------\n", context_->initial_pose());
    size_t id = 0;
    for (const auto& state : storage_->states()) {
        fmt::print("id: {}\n{}\n--------------------\n", id++, state);
    }
}

void MissionCLI::safe_handle(const std::function<void()>& handler) {
    auto storage_copy = std::make_unique<MissionStorage>(*storage_);
    try {
        handler();
    } catch (const MissionException& e) {
        fmt::print("Произошла ошибка при перестроении состояний после последней операции ({}), возвращаю как было.\n", e.what());
        storage_ = std::move(storage_copy);
    }
}

void MissionCLI::extract_mission_from_cin(const std::string& prompt, std::shared_ptr<Mission>& item) {
    std::string mission_type;
    extract_from_cin(fmt::format("{} (Dive|Lift|Move|Return)", prompt), mission_type);
    if (mission_type == "Dive") {
        int depth{};
        extract_from_cin("Глубина", depth);
        MovementType movement_type;
        extract_from_cin("", movement_type);
        DepthType depth_type;
        extract_from_cin("", depth_type);
        item = std::make_shared<Dive>(context_, depth, movement_type, depth_type);
    } else if (mission_type == "Lift") {
        int height{};
        extract_from_cin("Высота", height);
        MovementType movement_type;
        extract_from_cin("", movement_type);
        DepthType depth_type;
        extract_from_cin("", depth_type);
        item = std::make_shared<Lift>(context_, height, movement_type, depth_type);
    } else if (mission_type == "Move") {
        Pose pose{};
        extract_from_cin("Целевое положение", pose);
        Pose delta{};
        extract_from_cin("Погрешность", delta);
        item = std::make_shared<Move>(context_, pose, delta);
    } else if (mission_type == "Return") {
        item = std::make_shared<Return>(context_);
    } else {
        throw MissionException{fmt::format("wrong mission_type {}", mission_type)};
    }
}
}// namespace task3
