#include "AdminSponsor.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminSponsor::SponsorMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Sponsors ===\n";
    cout << "1. View Sponsors\n";
    cout << "2. Add Sponsor\n";
    cout << "3. Delete Sponsor\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewSponsor(db);
        break;
    case 2:
        AddSponsor(db);
        break;
    case 3:
        DeleteSponsor(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminSponsor::ViewSponsor(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Sponsor");

        cout << "\nSponsors:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Sponsor_Name")
                << ", Contact Info: " << res->getString("Contact_Info")
                << ", Amount: " << res->getDouble("Contribution_Amount")
                << ", Contribution Date: " << res->getString("Contribution_Date") 
                << ", Museum ID: " << res->getString("Museum_ID") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminSponsor::AddSponsor(Database& db) {
    string name, contactInfo, contributionDate;
    double amount;
    int museumId;

    cout << "\n=== Add New Sponsor ===\n";
    cout << "Enter Sponsor Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Contact Info: ";
    getline(cin, contactInfo);

    cout << "Enter Sponsorship Amount: ";
    cin >> amount;

    cin.ignore();
    cout << "Enter Contributuion Date (YYYY-MM-DD): ";
    getline(cin, contributionDate);

    cout << "Enter Museum ID: ";
    cin >> museumId;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO Sponsor (Sponsor_Name, Contact_Info, Contribution_Amount, Contribution_Date, Museum_ID) VALUES (?, ?, ?, ?, ?)"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, contactInfo);
        pstmt->setDouble(3, amount);
        pstmt->setString(4, contributionDate);
        pstmt->setInt(5, museumId);
        pstmt->executeUpdate();
        delete pstmt;

        cout << "Sponsor added successfully!\n";
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void AdminSponsor::DeleteSponsor(Database& db) {
    int id;
    cout << "Enter Sponsor ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Sponsor WHERE ID = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "Sponsor deleted successfully.\n";
        else
            cout << "No sponsor found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
