#include <iostream>
#include <string>
#include <vector>

#include "src/task.h"
#include "src/task_store.h"

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
