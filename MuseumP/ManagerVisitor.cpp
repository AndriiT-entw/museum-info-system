#include "ManagerVisitor.h"
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void ManagerVisitor::menu(Database& db) {
    int choice;
    cout << "\n=== Manager Menu Visitors ===\n";
    cout << "1. View Visitors\n";
    cout << "2. Delete Visitor\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        viewVisitors(db);
        break;
    case 2:
        deleteVisitor(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void ManagerVisitor::viewVisitors(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM visitor");

        cout << "\nVisitors:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Name")
                << ", Email: " << res->getString("Email") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void ManagerVisitor::deleteVisitor(Database& db) {
    int id;
    cout << "Enter Visitor ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM visitor WHERE id = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "Visitor deleted successfully.\n";
        else
            cout << "No visitor found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
