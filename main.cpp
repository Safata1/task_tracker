#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

#include "json.hpp"

using json = nlohmann::json;
using namespace std;

/* ===========================
   Task Data Model
   =========================== */
struct Task {
    int id;
    string description;
    string status;
    string createdAt;
    string updatedAt;
};

/* ===========================
   Utility Functions
   =========================== */
string getCurrentTime() {
    time_t now = time(nullptr);
    return string(ctime(&now));
}

bool isValidStatus(const string& status) {
    return status == "todo" ||
           status == "in-progress" ||
           status == "done";
}

/* ===========================
   JSON Serialization
   =========================== */
json taskToJson(const Task& task) {
    return json{
        {"id", task.id},
        {"description", task.description},
        {"status", task.status},
        {"createdAt", task.createdAt},
        {"updatedAt", task.updatedAt}
    };
}

Task jsonToTask(const json& j) {
    Task task;
    task.id = j.at("id").get<int>();
    task.description = j.at("description").get<string>();
    task.status = j.at("status").get<string>();
    task.createdAt = j.at("createdAt").get<string>();
    task.updatedAt = j.at("updatedAt").get<string>();
    return task;
}

/* ===========================
   Persistence Layer
   =========================== */
void saveTasks(const vector<Task>& tasks) {
    json j = json::array();
    for (const auto& task : tasks) {
        j.push_back(taskToJson(task));
    }

    ofstream file("tasks.json");
    file << j.dump(4);
}

void loadTasks(vector<Task>& tasks, int& nextId) {
    ifstream file("tasks.json");
    if (!file.is_open()) return;

    json j;
    file >> j;

    for (const auto& item : j) {
        Task task = jsonToTask(item);
        tasks.push_back(task);
        nextId = max(nextId, task.id + 1);
    }
}

/* ===========================
   Command Handlers
   =========================== */

/***** ADD TASK *****/
void addTask(vector<Task>& tasks, int& nextId, const string& description) {
    if (description.empty()) {
        cout << "Error: task description cannot be empty.\n";
        return;
    }

    Task task;
    task.id = nextId++;
    task.description = description;
    task.status = "todo";
    task.createdAt = getCurrentTime();
    task.updatedAt = task.createdAt;

    tasks.push_back(task);
    saveTasks(tasks);

    cout << "Task added (ID " << task.id << ")\n";
}

/***** LIST TASKS *****/
void listTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks found.\n";
        return;
    }

    for (const auto& task : tasks) {
        cout << "[" << task.id << "] "
             << task.description << " | "
             << task.status << "\n";
    }
}

/***** DELETE TASK *****/
void deleteTask(vector<Task>& tasks, int id) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            saveTasks(tasks);
            cout << "Task deleted.\n";
            return;
        }
    }
    cout << "Task not found.\n";
}

/***** UPDATE TASK *****/
void updateTask(vector<Task>& tasks, int id, const string& newStatus) {
    if (!isValidStatus(newStatus)) {
        cout << "Invalid status. Allowed values: todo, in-progress, done.\n";
        return;
    }

    for (auto& task : tasks) {
        if (task.id == id) {
            task.status = newStatus;
            task.updatedAt = getCurrentTime();
            saveTasks(tasks);
            cout << "Task updated.\n";
            return;
        }
    }

    cout << "Task not found.\n";
}


/* ===========================
   Main Application Loop
   =========================== */
int main() {
    string command;
    vector<Task> tasks;
    int nextId = 1;

    loadTasks(tasks, nextId);

    cout << "Welcome to Task CLI!\n";
    cout << "Type 'help' to see available commands.\n";

    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command == "exit") {
            cout << "Goodbye!\n";
            break;
        }

        else if (command == "help") {
            cout << "Available commands:\n";
            cout << "add <task>        - Add a new task\n";
            cout << "list              - List all tasks\n";
            cout << "delete <id>       - Delete a task\n";
            cout << "update <id> <status> - Update task status\n";
            cout << "exit              - Exit the application\n";
        }

        else if (command.rfind("add ", 0) == 0) {
            addTask(tasks, nextId, command.substr(4));
        }

        else if (command == "list") {
            listTasks(tasks);
        }

        else if (command.rfind("delete ", 0) == 0) {
            deleteTask(tasks, stoi(command.substr(7)));
        }

        else if (command.rfind("update ", 0) == 0) {
            string rest = command.substr(7);
            size_t pos = rest.find(' ');
            if (pos == string::npos) {
                cout << "Usage: update <id> <status>\n";
            } else {
                updateTask(tasks, stoi(rest.substr(0, pos)), rest.substr(pos + 1));
            }
        }

        else {
            cout << "Unknown command. Type 'help' for a list of commands.\n";
        }
    }

    return 0;
}
