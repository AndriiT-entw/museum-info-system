#include "AdminUser.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminUser::UserMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Users ===\n";
    cout << "1. View Users\n";
    cout << "2. Add User\n";
    cout << "3. Delete User\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewUser(db);
        break;
    case 2:
        AddUser(db);
        break;
    case 3:
        DeleteUser(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminUser::ViewUser(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM User");

        cout << "\nUsers:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Username: " << res->getString("Username")
                << ", Password: " << res->getInt("Password")
                << ", Role: " << res->getString("Role") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
void AdminUser::AddUser(Database& db)
{
    std::string username, role, password;


    std::cout << "\n=== Add New User ===\n";
    std::cout << "Enter Username: ";
    std::cin.ignore(); // clear buffer
    std::getline(std::cin, username);

    std::cout << "Enter Role: ";
    std::getline(std::cin, role);

    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO User (Username, Role, Password) VALUES (?, ?, ?)"
        );
        pstmt->setString(1, username);
        pstmt->setString(2, role);
        pstmt->setString(3, password);

        pstmt->executeUpdate();
        delete pstmt;

        std::cout << "User added successfully!\n";
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << "\n";
    }
}

void AdminUser::DeleteUser(Database& db) {
    int id;
    cout << "Enter User ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM User WHERE id = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "User deleted successfully.\n";
        else
            cout << "No user found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}