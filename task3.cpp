#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool userExists(const string& username) {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        if (line.substr(0, line.find(',')) == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void registerUser() {
    string username, password;
    
    cout << "Enter username: ";
    cin >> username;
    if (userExists(username)) {
        cout << "User already exists!" << endl;
        return;
    }

    cout << "Enter password: ";
    cin >> password;
    ofstream file("users.txt", ios::app);
    if (!file) {
        cerr << "Error: Cannot open file for writing!" << endl;
        exit(1);
    }
    
    file << username << "," << password << "\n";
    file.close();
    cout << "Registration successful!" << endl;
}

bool authenticateUser(string& username) {
    string password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    if (!file) {
        cerr << "Error: Cannot open file for reading!" << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        if (line.substr(0, line.find(',')) == username) {
            size_t pos = line.find(',');
            string storedPassword = line.substr(pos + 1);
            if (storedPassword == password) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

int main() {
    cout << "Welcome to User Registration and Login System" << endl;
    bool loggedIn = false;
    string username;

    while (!loggedIn) {
        cout << "\nMenu:\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nRegistration\n";
                registerUser();
                break;
            case 2:
                cout << "\nLogin\n";
                if (authenticateUser(username)) {
                    cout << "Login successful!" << endl;
                    loggedIn = true;
                } else {
                    cout << "Invalid username or password! Please try again." << endl;
                }
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }
        if (loggedIn) {
            cout << "\nWelcome, " << username << "!" << endl;
            break;
        }
    }
    return 0;
}