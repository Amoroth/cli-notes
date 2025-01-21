#ifndef CPTST_H
#define CPTST_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

class Task {
    std::string name;
    bool done;
public:
    Task() = default;
    Task(const std::string& name, const bool& done);
    void loadJson(const nlohmann::json& jsonInput);
    std::string getName() const;
    std::string dump() const;
    void markAsDone();
    bool isDone() const;
};

class TaskStore {
    std::vector<Task> tasks;
public:
    TaskStore() = default;
    std::vector<Task> readTasks();
    void printTasks(const bool& all);
    void addNewTask(std::vector<std::string>& args);
    void save();
    void markAsDone(const int& taskId);
    void remove(const int& taskId);
};
#endif
