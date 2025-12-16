#include <iostream>
#include <string>

int main() {
    std::string command;

    std::cout << "Welcome to Taskly CLI!\n";
    std::cout << "Type 'help' to see available commands.\n";

    while (true) {
        std::cout << "> ";          // CLI prompt
        std::getline(std::cin, command);

        if (command == "exit") {
            std::cout << "Goodbye!\n";
            break;
        } else if (command == "help") {
            std::cout << "Available commands:\n";
            std::cout << "add <task>    - Add a new task\n";
            std::cout << "list          - List all tasks\n";
            std::cout << "delete <id>   - Delete a task by ID\n";
            std::cout << "exit          - Exit the application\n";
        } else {
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
        }
    }

    return 0;
}
