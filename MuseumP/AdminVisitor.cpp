#include "AdminVisitor.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminVisitor::VisitorMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Visitors ===\n";
    cout << "1. View Visitors\n";
    cout << "2. Add Visitor\n";
    cout << "3. Delete Visitor\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewVisitor(db);
        break;
    case 2:
        AddVisitor(db);
        break;
    case 3:
        DeleteVisitor(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminVisitor::ViewVisitor(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM visitor");

        cout << "\nVisitors:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Name")
                << ", Ticket ID: " << res->getInt("Ticket_ID")
                << ", Email: " << res->getString("Email") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
void AdminVisitor::AddVisitor(Database& db)
{
    std::string name, email;
    int ticket_id;

    std::cout << "\n=== Add New Visitor ===\n";
    std::cout << "Enter Name: ";
    std::cin.ignore(); // clear buffer
    std::getline(std::cin, name);

    std::cout << "Enter Email: ";
    std::getline(std::cin, email);

    std::cout << "Enter Ticket ID: ";
    std::cin >> ticket_id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO Visitor (Name, Email, Ticket_ID) VALUES (?, ?, ?)"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, email);
        pstmt->setInt(3, ticket_id);

        pstmt->executeUpdate();
        delete pstmt;

        std::cout << "Visitor added successfully!\n";
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << "\n";
    }
}

void AdminVisitor::DeleteVisitor(Database& db) {
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
