#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

struct Task {
    int id;
    std::string description;
    bool completed;
};

// Function to display the menu
void showMenu() {
    std::cout << "\n--- To-Do List Manager ---\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. View Tasks\n";
    std::cout << "3. Mark Task as Completed\n";
    std::cout << "4. Save and Exit\n";
    std::cout << "Choose an option: ";
}

// Function to display all tasks
void displayTasks(const std::vector<Task>& tasks) {
    std::cout << "\n--- To-Do List ---\n";
    if (tasks.empty()) {
        std::cout << "No tasks available.\n";
        return;
    }
    std::cout << std::setw(5) << "ID" << std::setw(30) << "Description" << std::setw(15) << "Completed\n";
    for (const auto& task : tasks) {
        std::cout << std::setw(5) << task.id
                  << std::setw(30) << task.description
                  << std::setw(15) << (task.completed ? "Yes" : "No") << '\n';
    }
}

// Function to add a new task
void addTask(std::vector<Task>& tasks, int& nextId) {
    Task newTask;
    newTask.id = nextId++;
    std::cout << "Enter task description: ";
    std::cin.ignore();
    std::getline(std::cin, newTask.description);
    newTask.completed = false;
    tasks.push_back(newTask);
    std::cout << "Task added successfully.\n";
}

// Function to mark a task as completed
void markTaskCompleted(std::vector<Task>& tasks) {
    int taskId;
    std::cout << "Enter the task ID to mark as completed: ";
    std::cin >> taskId;

    for (auto& task : tasks) {
        if (task.id == taskId) {
            task.completed = true;
            std::cout << "Task marked as completed.\n";
            return;
        }
    }
    std::cout << "Task not found.\n";
}

// Function to save tasks to a file
void saveTasks(const std::vector<Task>& tasks) {
    std::ofstream outFile("tasks.txt");
    if (!outFile) {
        std::cerr << "Error saving tasks to file.\n";
        return;
    }

    for (const auto& task : tasks) {
        outFile << task.id << '\n'
                << task.description << '\n'
                << task.completed << '\n';
    }

    std::cout << "Tasks saved to file successfully.\n";
}

// Function to load tasks from a file
void loadTasks(std::vector<Task>& tasks, int& nextId) {
    std::ifstream inFile("tasks.txt");
    if (!inFile) return;

    Task task;
    while (inFile >> task.id) {
        inFile.ignore();
        std::getline(inFile, task.description);
        inFile >> task.completed;
        tasks.push_back(task);
        if (task.id >= nextId) {
            nextId = task.id + 1;
        }
    }
}

// Function to validate menu input
int getValidatedMenuOption() {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid option. Try again: ";
        } else {
            break;
        }
    }
    return choice;
}

int main() {
    std::vector<Task> tasks;
    int nextId = 1;

    // Load tasks from file
    loadTasks(tasks, nextId);

    int choice;
    do {
        showMenu();
        choice = getValidatedMenuOption();

        switch (choice) {
            case 1:
                addTask(tasks, nextId);
                break;
            case 2:
                displayTasks(tasks);
                break;
            case 3:
                markTaskCompleted(tasks);
                break;
            case 4:
                saveTasks(tasks);
                std::cout << "Exiting program.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
