#include <iostream>
#include <string>
using namespace std;
const int MAX_BOOKS = 10;

struct Book {
    int bookID;
    string title;
    int count;
};

void addBook(Book inventory[], int& bookCount, int bookID, string title, int count) {
    if (bookCount < MAX_BOOKS) {
        inventory[bookCount].bookID = bookID;
        inventory[bookCount].title = title;
        inventory[bookCount].count = count;
        bookCount++;
        cout << "Book added to inventory." << endl;
    } else {
        cout << "Error: Maximum inventory size reached." << endl;
    }
}

void displayInventory(const Book inventory[], int bookCount) {
    cout << "Inventory:" << endl;
    for (int i = 0; i < bookCount; ++i) {
        cout << "Book ID: " << inventory[i].bookID << ", Title: " << inventory[i].title << ", Count: " << inventory[i].count << endl;
    }
}

int searchByID(const Book inventory[], int bookCount, int bookID, Book foundBooks[]) {
    int foundCount = 0;
    for (int i = 0; i < bookCount; ++i) {
        if (inventory[i].bookID == bookID) {
            foundBooks[foundCount++] = inventory[i];
        }
    }
    return foundCount;
}

void purchaseBook(Book inventory[], int bookCount, int bookID) {
    for (int i = 0; i < bookCount; ++i) {
        if (inventory[i].bookID == bookID && inventory[i].count > 0) {
            inventory[i].count--;
            cout << "Book '" << inventory[i].title << "' purchased. Remaining count: " << inventory[i].count << endl;
            return;
        }
    }
    cout << "Book with ID " << bookID << " not found or out of stock." << endl;
}

void removeBook(Book inventory[], int& bookCount, int bookID) {
    for (int i = 0; i < bookCount; ++i) {
        if (inventory[i].bookID == bookID) {
            // Remove the book by shifting elements
            for (int j = i; j < bookCount - 1; ++j) {
                inventory[j] = inventory[j + 1];
            }
            bookCount--;
            cout << "Book removed from inventory." << endl;
            return;
        }
    }
    cout << "Book with ID " << bookID << " not found." << endl;
}


int main() {
    Book inventory[MAX_BOOKS];
    int bookCount = 0;

    while (true) {
        cout << "\nMenu:\n1. Add Book\n2. Display Inventory\n3. Search by ID\n4. Purchase Book\n5. Remove Book\n6. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                int bookID, count;
                string title;
                cout << "Enter Book ID: ";
                cin >> bookID;
                cout << "Enter Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Count: ";
                cin >> count;
                addBook(inventory, bookCount, bookID, title, count);
                break;
            }
            case 2:
                displayInventory(inventory, bookCount);
                break;
            case 3: {
                int searchID;
                cout << "Enter Book ID to search: ";
                cin >> searchID;
                Book foundByID[MAX_BOOKS];
                int foundCount = searchByID(inventory, bookCount, searchID, foundByID);
                if (foundCount > 0) {
                    cout << "Books found with ID " << searchID << ":" << endl;
                    for (int i = 0; i < foundCount; ++i) {
                        cout << "Title: " << foundByID[i].title << ", Count: " << foundByID[i].count << endl;
                    }
                } else {
                    cout << "No books found with ID " << searchID << endl;
                }
                break;
            }
            case 4: {
                int purchaseID;
                cout << "Enter Book ID to purchase: ";
                cin >> purchaseID;
                purchaseBook(inventory, bookCount, purchaseID);
                break;
            }
            case 5: {
                int removeID;
                cout << "Enter Book ID to remove: ";
                cin >> removeID;
                removeBook(inventory, bookCount, removeID);
                break;
            }
            case 6:
                cout << "Exiting program. Thank you for using me..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}