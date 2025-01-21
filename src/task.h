#ifndef CPTST_TASK_H
#define CPTST_TASK_H
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

class Task {
    std::string name;
    bool done;
public:
    Task() = default;
    Task(const std::string& name) : Task(name, false) {}
    Task(const std::string& name, const bool& done);
    void loadJson(const nlohmann::json& jsonInput);
    std::string getName() const;
    std::string dump() const;
    void markAsDone();
    bool isDone() const;
};
#endif
