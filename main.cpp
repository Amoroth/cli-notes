#include "main.h"
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

void TaskStore::printTasks(const bool& all = false) {
    int index = 0;
    for (const auto& task : tasks) {
        index += 1;

        if (!all && task.isDone()) {
            continue;
        }
        std::cout << index << ": " << task.getName() << std::endl;
    }
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

int main(int argc, char* argv[]) {
    TaskStore store;
    std::vector<Task> tasks = store.readTasks();

    if (argc > 1) {
        std::vector<std::string> args;
        for (int i = 2; i < argc; i++) {
            args.push_back(argv[i]);
        }

        if (std::strcmp(argv[1], "add") == 0 || std::strcmp(argv[1], "new") == 0) {
            store.addNewTask(args);
            store.save();
        } else if (std::strcmp(argv[1], "done") == 0) {
            if (!args.size()) {
                std::cout << "Provide index of the task you want to mark a done" << std::endl;
            }
            store.markAsDone(stoi(args[0]) - 1);
            store.save();
        } else if (std::strcmp(argv[1], "list") == 0) {
            bool showAll = false;
            for (auto const& arg : args){
                if (arg == "--all") {
                    showAll = true;
                }
            }
            store.printTasks(showAll);
        } else if (std::strcmp(argv[1], "remove") == 0 || std::strcmp(argv[1], "rm") == 0) {
            if (!args.size()) {
                std::cout << "Provide index of the task you want to remove" << std::endl;
            }

            store.remove(stoi(args[0]) - 1);
            store.save();
        } else {
            std::cout << "Not recognizable command." << std::endl;
            return 1;
        }

        return 0;
    }

    if (argc == 1) {
        store.printTasks();
    }

    return 0;
}
