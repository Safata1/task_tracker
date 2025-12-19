#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std ;
struct Task {
    int id;
    string description;
    string status;
    string createdAt;
    string updatedAt;
};

string getCurrentTime() {
    time_t now = time(nullptr);
    return string(ctime(&now)); 
}

int main() {
    string command;
    vector<Task> tasks;
    int nextId = 1;


    cout << "Welcome to Task CLI!\n";
    cout << "Type 'help' to see available commands.\n";

    while (true) {
        cout << "> ";          // CLI prompt
        getline(cin, command);

        if (command == "exit") {
            cout << "Goodbye!\n";
            break;
        } else if (command == "help") {
            cout << "Available commands:\n";
            cout << "add <task>    - Add a new task\n";
            cout << "list          - List all tasks\n";
            cout << "delete <id>   - Delete a task by ID\n";
            cout << "exit          - Exit the application\n";
        }
         
        //add task
        else if (command.rfind("add ", 0) == 0) {
            // Extract task description
            std::string description = command.substr(4);

            if (description.empty()) {
                std::cout << "Error: task description cannot be empty.\n";
            } else {
                Task task;
                task.id = nextId++;
                task.description = description;
                task.status = "todo";
                task.createdAt = getCurrentTime();
                task.updatedAt = task.createdAt;

                tasks.push_back(task);

                cout << "Task added (ID " << task.id << ")\n";
            }

        } 

        //list task 
        else if (command == "list") {
            if (tasks.empty()) {
                cout << "No tasks found.\n";
            } else {
                for (const auto& task : tasks) {
                    cout << "[" << task.id << "] "
                        << task.description
                        << " | " << task.status << "\n";
                }
            }
        }

        //delete task 
        else if (command.rfind("delete ", 0) == 0) {
        int id = stoi(command.substr(7));

        bool found = false;
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->id == id) {
                tasks.erase(it);
                cout << "Task deleted.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Task not found.\n";
        }
        }

        //Update task
        else if (command.rfind("update ", 0) == 0) {
            string rest = command.substr(7);
            size_t spacePos = rest.find(' ');

            if (spacePos == string::npos) {
                cout << "Usage: update <id> <status>\n";
            } else {
                int id = stoi(rest.substr(0, spacePos));
                string newStatus = rest.substr(spacePos + 1);

                bool found = false;
                for (auto& task : tasks) {
                    if (task.id == id) {
                        task.status = newStatus;
                        task.updatedAt = getCurrentTime();
                        cout << "Task updated.\n";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Task not found.\n";
                }
            }
        }
        else {
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
        }
    }

    return 0;
}
