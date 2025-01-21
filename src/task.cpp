#include "task.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

Task::Task(const std::string& name, const bool& done = false) {
    this->name = name;
    this->done = done;
}

void Task::loadJson(const nlohmann::json& jsonInput) {
    name = jsonInput["name"];
    done = jsonInput["done"].template get<bool>();
}

std::string Task::getName() const {
    return name;
}

std::string Task::dump() const {
    nlohmann::json j;
    j["name"] = name;
    j["done"] = done;
    return j.dump();
}

void Task::markAsDone() {
    done = true;
}

bool Task::isDone() const {
    return done;
}

