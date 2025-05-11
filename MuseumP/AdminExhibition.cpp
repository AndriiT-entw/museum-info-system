#include "AdminExhibition.h"
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminExhibition::ExhibitionMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Exhibitions ===\n";
    cout << "1. View Exhibitions\n";
    cout << "2. Add Exhibition\n";
    cout << "3. Delete Exhibition\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1: ViewExhibition(db); break;
    case 2: AddExhibition(db); break;
    case 3: DeleteExhibition(db); break;
    default: cout << "Invalid choice.\n";
    }
}

void AdminExhibition::ViewExhibition(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Exhibition");

        cout << "\nExhibitions:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Name")
                << ", Start: " << res->getString("Start_Date")
                << ", End: " << res->getString("End_Date")
                << ", Cost: " << res->getDouble("Cost")
                << ", Museum ID: " << res->getInt("Museum_ID") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminExhibition::AddExhibition(Database& db) {
    string name, start, end;
    double cost;
    int museum_id;

    cout << "\n=== Add New Exhibition ===\n";
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Start Date (YYYY-MM-DD): ";
    getline(cin, start);
    cout << "Enter End Date (YYYY-MM-DD): ";
    getline(cin, end);
    cout << "Enter Cost: ";
    cin >> cost;
    cout << "Enter Museum ID: ";
    cin >> museum_id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO Exhibition (Name, Start_Date, End_Date, Cost, Museum_ID) VALUES (?, ?, ?, ?, ?)"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, start);
        pstmt->setString(3, end);
        pstmt->setDouble(4, cost);
        pstmt->setInt(5, museum_id);
        pstmt->executeUpdate();
        delete pstmt;

        cout << "Exhibition added successfully!\n";
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << "\n";
    }
}

void AdminExhibition::DeleteExhibition(Database& db) {
    int id;
    cout << "Enter Exhibition ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Exhibition WHERE ID = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();
        delete pstmt;

        if (affected > 0)
            cout << "Exhibition deleted successfully.\n";
        else
            cout << "No exhibition found with that ID.\n";
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << "\n";
    }
}
