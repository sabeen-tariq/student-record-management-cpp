#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Task {
    int id;
    string title;
    string subject;
    string deadline;
    bool completed;
};
void saveTasks(const vector<Task>&tasks);
void addTask(vector<Task>& tasks, int& nextId) {
    Task t;

    t.id = nextId++;

    cout << "Enter task title: ";
    getline(cin >> ws, t.title);

    cout << "Enter subject: ";
    getline(cin, t.subject);

    cout << "Enter deadline (DD-MM-YYYY): ";
    getline(cin, t.deadline);

    t.completed = false;

    tasks.push_back(t);
    saveTasks(tasks);

    cout << "\nTask added successfully!\n";
}
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\nNo tasks available.\n";
        return;
    }

    cout << "\n=== YOUR TASKS ===\n";

    for (const Task& t : tasks) {
        cout << "\nTask ID: " << t.id << endl;
        cout << "Title: " << t.title << endl;
        cout << "Subject: " << t.subject << endl;
        cout << "Deadline: " << t.deadline << endl;
        cout << "Status: "
             << (t.completed ? "Completed" : "Pending")
             << endl;
    }
}
void deleteTask(vector<Task>& tasks) {
    int id;

    cout << "Enter Task ID to delete: ";
    cin >> id;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].id == id) {
            tasks.erase(tasks.begin() + i);
            saveTasks(tasks);
            cout << "Task deleted successfully!\n";
            return;
        }
    }

    cout << "Task ID not found!\n";
}
void completeTask(vector<Task>& tasks) {
    int id;

    cout << "Enter Task ID to complete: ";
    cin >> id;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].id == id) {
            tasks[i].completed = true;
            saveTasks(tasks);
            cout << "Task marked as completed!\n";
            return;
        }
    }

    cout << "Task ID not found!\n";
}
void saveTasks(const vector<Task>& tasks) {
    ofstream file("tasks.txt");

    for (const Task& t : tasks) {
        file << t.id << '\n';
        file << t.title << '\n';
        file << t.subject << '\n';
        file << t.deadline << '\n';
        file << t.completed << '\n';
    }

    file.close();
}
void loadTasks(vector<Task>& tasks, int& nextId) {
    ifstream file("tasks.txt");

    if (!file.is_open()) {
        return;
    }

    Task t;

    while (file >> t.id) {
        file.ignore();

        getline(file, t.title);
        getline(file, t.subject);
        getline(file, t.deadline);

        file >> t.completed;
        file.ignore();

        tasks.push_back(t);

        if (t.id >= nextId) {
            nextId = t.id + 1;
        }
    }

    file.close();
}
void viewPendingTask(const vector<Task>& tasks) {
    bool found = false;

    cout << "\n=== PENDING TASKS ===\n";

    for (const Task& t : tasks) {
        if (!t.completed) {
            cout << "\nTask ID: " << t.id << endl;
            cout << "Title: " << t.title << endl;
            cout << "Subject: " << t.subject << endl;
            cout << "Deadline: " << t.deadline << endl;
            cout << "Status: Pending" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No pending tasks!\n";
    }
}

int main() {
    vector<Task> tasks;
    int nextId = 1;
    int choice;
    loadTasks(tasks,nextId);

    do {
        cout << "\n=== STUDENT TASK MANAGER ===\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete Task\n";
        cout << "4. Mark Task Completed\n";
        cout << "5. View Pending Tasks\n";
        cout << "6.  Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks, nextId);
                break;

            case 2:
                viewTasks(tasks);
                break;

            case 3:
                 deleteTask(tasks);
                 break;
            case 4:
                  completeTask(tasks);
                  break;
            case 5:
                  viewPendingTask(tasks);
                  break;
             case 6:
                  cout << "Goodbye!\n";
                  break;
                     
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
