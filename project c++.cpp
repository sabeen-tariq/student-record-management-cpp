#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Student {
public:
    int rollNumber;
    string name;
    string department;
    float gpa;

    void inputDetails() {
        cout << "\nEnter Roll Number: ";
        cin >> rollNumber;
        cin.ignore(); // Clear buffer
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Department: ";
        getline(cin, department);
        cout << "Enter GPA: ";
        cin >> gpa;
    }
};

// Function to add student to file
void addStudent() {
    Student s;
    s.inputDetails();

    ofstream outFile("students.txt", ios::app);
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    outFile << s.rollNumber << "," << s.name << "," << s.department << "," << s.gpa << endl;
    outFile.close();

    cout << "\n[Success] Student record saved successfully!" << endl;
}

// Function to view all student records from file
void viewStudents() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "\nNo records found or file unable to open." << endl;
        return;
    }

    int roll;
    string name, dept;
    float gpa;
    string line;
    bool found = false;

    cout << "\n============== ALL STUDENT RECORDS ==============" << endl;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string rollStr, gpaStr;

        // Parse line split by commas
        if (getline(ss, rollStr, ',') &&
            getline(ss, name, ',') &&
            getline(ss, dept, ',') &&
            getline(ss, gpaStr, ',')) {

            stringstream convertRoll(rollStr);
            stringstream convertGpa(gpaStr);

            convertRoll >> roll;
            convertGpa >> gpa;

            cout << "\nRoll No   : " << roll << endl;
            cout << "Name      : " << name << endl;
            cout << "Department: " << dept << endl;
            cout << "GPA       : " << gpa << endl;
            cout << "-----------------------------------";
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo records to display." << endl;
    }

    inFile.close();
}

int main() {
    int choice;
    do {
        cout << "\n\n========================================" << endl;
        cout << "   STUDENT RECORD MANAGEMENT SYSTEM     " << endl;
        cout << "========================================" << endl;
        cout << "1. Add New Student Record" << endl;
        cout << "2. View All Student Records" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                cout << "\nThank you for using the system. Goodbye!" << endl;
                break;
            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
