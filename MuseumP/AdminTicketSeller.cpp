#include "AdminTicketSeller.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminTicketSeller::TicketSellerMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Ticket Sellers ===\n";
    cout << "1. View Ticket Sellers\n";
    cout << "2. Add Ticket Seller\n";
    cout << "3. Delete Ticket Seller\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewTicketSeller(db);
        break;
    case 2:
        AddTicketSeller(db);
        break;
    case 3:
        DeleteTicketSeller(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminTicketSeller::ViewTicketSeller(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Ticket_Sale");

        cout << "\nTicket Sellers:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Seller Id: " << res->getString("Seller_ID")
                << ", Ticket Id: " << res->getString("Ticket_ID") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminTicketSeller::AddTicketSeller(Database& db) {
    int sellerId, ticketId;

    cout << "\n=== Add New Ticket Seller ===\n";
    cout << "Enter Seller Id: ";
    cin.ignore();
    cin >> sellerId;

    cout << "Enter Ticket Id: ";
    cin >> ticketId;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO Ticket_Sale (Seller_ID, Ticket_ID) VALUES (?, ?)"
        );
        pstmt->setInt(1, sellerId);
        pstmt->setInt(2, ticketId);

        pstmt->executeUpdate();
        delete pstmt;

        cout << "Ticket Seller added successfully!\n";
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void AdminTicketSeller::DeleteTicketSeller(Database& db) {
    int id;
    cout << "Enter Ticket Seller ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Ticket_Sale WHERE ID = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "Ticket Seller deleted successfully.\n";
        else
            cout << "No ticket seller found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
