#include "AdminGuide.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminGuide::GuideMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Guides ===\n";
    cout << "1. View Guides\n";
    cout << "2. Add Guide\n";
    cout << "3. Delete Guide\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewGuide(db);
        break;
    case 2:
        AddGuide(db);
        break;
    case 3:
        DeleteGuide(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminGuide::ViewGuide(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Guide");

        cout << "\nGuides:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Name")
                << ", Contact Info: " << res->getString("Contact_Info")
                << ", Experience in Years: " << res->getInt("Years_Experience") << " years" << endl;
            cout << ", Museum ID: " << res->getInt("Museum_ID") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminGuide::AddGuide(Database& db) {
    string name, contactInfo;
    int experience, museumId;

    cout << "\n=== Add New Guide ===\n";
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Contact Info: ";
    getline(cin, contactInfo);

    cout << "Enter Experience in Years: ";
    cin >> experience;

    cout << "Museum Id: ";
    cin >> museumId;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO guide (Name, Contact_Info, Years_Experience, Museum_ID) VALUES (?, ?, ?, ?)"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, contactInfo);
        pstmt->setInt(3, experience);
        pstmt->setInt(4, museumId);
        pstmt->executeUpdate();
        delete pstmt;

        cout << "Guide added successfully!\n";
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void AdminGuide::DeleteGuide(Database& db) {
    int id;
    cout << "Enter Guide ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Guide WHERE ID = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "Guide deleted successfully.\n";
        else
            cout << "No guide found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
