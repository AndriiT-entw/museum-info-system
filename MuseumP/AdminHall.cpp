#include "AdminHall.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminHall::HallMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Halls ===\n";
    cout << "1. View Halls\n";
    cout << "2. Add Hall\n";
    cout << "3. Delete Hall\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewHall(db);
        break;
    case 2:
        AddHall(db);
        break;
    case 3:
        DeleteHall(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminHall::ViewHall(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Hall");

        cout << "\nHalls:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Hall_Name")
                << ", Capacity: " << res->getInt("Capacity")
                << ", Museum ID: " << res->getInt("Museum_ID") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminHall::AddHall(Database& db) {
    string name;
    int museum_id, capacity;

    cout << "\n=== Add New Hall ===\n";
    cout << "Enter Hall Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Hall Capacity: ";
    cin >> capacity;

    cout << "Enter Museum ID: ";
    cin >> museum_id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO hall (Hall_Name, Capacity, Museum_ID) VALUES (?, ?, ?)"
        );
        pstmt->setString(1, name);
        pstmt->setInt(2, capacity);
        pstmt->setInt(3, museum_id);
        pstmt->executeUpdate();
        delete pstmt;

        cout << "Hall added successfully!\n";
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void AdminHall::DeleteHall(Database& db) {
    int id;
    cout << "Enter Hall ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Hall WHERE ID = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "Hall deleted successfully.\n";
        else
            cout << "No hall found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
