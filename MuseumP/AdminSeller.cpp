#include "AdminSeller.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminSeller::SellerMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Sellers ===\n";
    cout << "1. View Sellers\n";
    cout << "2. Add Seller\n";
    cout << "3. Delete Seller\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewSeller(db);
        break;
    case 2:
        AddSeller(db);
        break;
    case 3:
        DeleteSeller(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminSeller::ViewSeller(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Seller");

        cout << "\nSellers:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Full_Name")
                << ", Email: " << res->getString("Contact_Info") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminSeller::AddSeller(Database& db) {
    string name, email;

    cout << "\n=== Add New Seller ===\n";
    cout << "Enter Seller Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Seller Email: ";
    getline(cin, email);

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO Seller (Full_Name, Contact_Info) VALUES (?, ?)"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, email);
        pstmt->executeUpdate();
        delete pstmt;

        cout << "Seller added successfully!\n";
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void AdminSeller::DeleteSeller(Database& db) {
    int id;
    cout << "Enter Seller ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Seller WHERE ID = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "Seller deleted successfully.\n";
        else
            cout << "No seller found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
