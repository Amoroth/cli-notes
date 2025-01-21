#ifndef CPTST_TASK_STORE_H
#define CPTST_TASK_STORE_H
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "task.h"

class TaskStore {
    std::vector<Task> tasks;
public:
    TaskStore() = default;
    std::vector<Task> readTasks();
    void printTasks();
    void printTasks(const bool& all);
    void addNewTask(std::vector<std::string>& args);
    void save();
    void markAsDone(const int& taskId);
    void remove(const int& taskId);
};
#endif
