#pragma once

#include "mission_storage.hpp"
#include <filesystem>
#include <fstream>
#include <map>
#include <set>

namespace task3 {
class MissionCLI {
public:
    MissionCLI();

    int run();

private:
    bool init();
    void exec();

    void save();
    void print();

    void safe_handle(const std::function<void()>& handler);

    void extract_mission_from_cin(const std::string& prompt, std::shared_ptr<Mission>& item);

private:
    std::shared_ptr<MissionContext> context_;
    std::unique_ptr<MissionStorage> storage_;
    std::filesystem::path file_path_;

    std::map<std::string, std::function<void()>> init_tasks_;
    std::map<std::string, std::function<void()>> exec_tasks_;
};
}// namespace task3
