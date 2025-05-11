#include "AdminMuseum.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminMuseum::MuseumMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Museums ===\n";
    cout << "1. View Museums\n";
    cout << "2. Add Museum\n";
    cout << "3. Delete Museum\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewMuseum(db);
        break;
    case 2:
        AddMuseum(db);
        break;
    case 3:
        DeleteMuseum(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminMuseum::ViewMuseum(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM museum");

        cout << "\nMuseums:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Name")
                << ", Address: " << res->getString("Address") 
                << ", Contact Info: " << res->getString("Contact_Info") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminMuseum::AddMuseum(Database& db) {
    string name, address, contactInfo;

    cout << "\n=== Add New Museum ===\n";
    cout << "Enter Museum Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Museum Address: ";
    getline(cin, address);

    cout << "Enter Contact Info: ";
    cin >> contactInfo;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO museum (Name, Address, Contact_Info) VALUES (?, ?, ?)"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, address);
        pstmt->setString(3, contactInfo);
        pstmt->executeUpdate();
        delete pstmt;

        cout << "Museum added successfully!\n";
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void AdminMuseum::DeleteMuseum(Database& db) {
    int id;
    cout << "Enter Museum ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Museum WHERE ID = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "Museum deleted successfully.\n";
        else
            cout << "No museum found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
