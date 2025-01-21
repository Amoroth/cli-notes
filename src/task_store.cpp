#include "task_store.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "task.h"

std::vector<Task> TaskStore::readTasks() {
    std::ifstream f("example.json");

    if (!f) {
        std::cerr << "Error: Could not open file." << std::endl;
        return {};
    }

    nlohmann::json data = nlohmann::json::parse(f);
    for (const auto& item : data) {
        Task newTask;
        newTask.loadJson(item);
        tasks.push_back(newTask);
        // better but harder:
        // tasks.emplace_back().loadJson(item);
    }

    return tasks;
}

void TaskStore::printTasks(const bool& all) {
    int index = 0;
    for (const auto& task : tasks) {
        index += 1;

        if (!all && task.isDone()) {
            continue;
        }
        std::cout << index << ": " << task.getName() << std::endl;
    }
}

void TaskStore::printTasks() {
    this->printTasks(false);
}

void TaskStore::addNewTask(std::vector<std::string>& args) {
    Task newTask(args[0]);
    std::string taskJson = newTask.dump();
    tasks.push_back(newTask);
    std::cout << taskJson << std::endl;
}

void TaskStore::save() {
    std::ofstream f("example.json");
    if (!f) {
        std::cerr << "Error: Could not open file." << std::endl;
        return;
    }

    std::vector<std::string> taskStrings;
    for (auto const& task : tasks) {
        taskStrings.push_back(task.dump());
    }
    std::string storeDump = std::accumulate(std::next(taskStrings.begin()), taskStrings.end(), taskStrings[0], [](std::string a, std::string b) {
        return std::move(a) + "," + b;
    });
    storeDump = "[" + storeDump + "]";

    std::cout << storeDump << std::endl;
    f << storeDump;
    f.close();
}

void TaskStore::markAsDone(const int& taskId) {
    if (taskId > tasks.size()) {
        std::cout << "Task at position does not exist!" << std::endl;
        return;
    }

    Task& task = tasks[taskId];
    task.markAsDone();
    std::cout << "Task '" << task.getName() << "' marked as done!" << std::endl;
}

void TaskStore::remove(const int& taskId) {
    if (taskId > tasks.size()) {
        std::cout << "Task at position does not exist!" << std::endl;
        return;
    }

    tasks.erase(tasks.begin() + taskId);
}

