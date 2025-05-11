#include "AdminAuthor.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminAuthor::AuthorMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Authors ===\n";
    cout << "1. View Authors\n";
    cout << "2. Add Author\n";
    cout << "3. Delete Author\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewAuthor(db);
        break;
    case 2:
        AddAuthor(db);
        break;
    case 3:
        DeleteAuthor(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminAuthor::ViewAuthor(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Author");

        cout << "\nAuthors:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Name")
                << ", Email: " << res->getString("Email")
                << ", Contract: " << res->getString("Agreement") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminAuthor::AddAuthor(Database& db) {
    string name, email, contract;
    cout << "\n=== Add New Author ===\n";
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Contract: ";
    getline(cin, contract);

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO Author (Name, Email, Agreement) VALUES (?, ?, ?)"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, email);
        pstmt->setString(3, contract);

        pstmt->executeUpdate();
        delete pstmt;

        cout << "Author added successfully!\n";
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminAuthor::DeleteAuthor(Database& db) {
    int id;
    cout << "Enter Author ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Author WHERE ID = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "Author deleted successfully.\n";
        else
            cout << "No author found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
