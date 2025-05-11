#include "AdminTicket.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminTicket::TicketMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Tickets ===\n";
    cout << "1. View Tickets\n";
    cout << "2. Add Ticket\n";
    cout << "3. Delete Ticket\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewTicket(db);
        break;
    case 2:
        AddTicket(db);
        break;
    case 3:
        DeleteTicket(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminTicket::ViewTicket(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM ticket");

        cout << "\nTickets:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Type: " << res->getString("Ticket_Type")
                << ", Price: " << res->getDouble("Price")
                << ", Visitor Category: " << res->getString("Visitor_Category")
                << ", Tour ID: " << res->getInt("Tour_ID")
                << ", Museum ID: " << res->getInt("Museum_ID") 
                << ", Sale Start Date: " << res->getString("Sale_Date") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminTicket::AddTicket(Database& db) {
    string type, category, saleDate;
    double price;
    int tour_id, museum_id;

    cout << "\n=== Add New Ticket ===\n";
    cout << "Enter Ticket Type: ";
    cin.ignore();
    getline(cin, type);

    cout << "Enter Visitor Category: ";
    getline(cin, category);

    cout << "Enter Price: ";
    cin >> price;

    cout << "Enter Tour ID (or 0 if none): ";
    cin >> tour_id;

    cout << "Enter Museum ID: ";
    cin >> museum_id;

    cin.ignore();
    cout << "Enter Start Sale Date (or 0 if none): ";
    getline(cin, saleDate);

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO ticket (Ticket_Type, Price, Visitor_Category, Tour_ID, Museum_ID, Sale_Date) VALUES (?, ?, ?, ?, ?, ?)"
        );
        pstmt->setString(1, type);
        pstmt->setDouble(2, price);
        pstmt->setString(3, category);

        if (tour_id == 0)
            pstmt->setNull(4, sql::DataType::INTEGER);
        else
            pstmt->setInt(4, tour_id);

        pstmt->setInt(5, museum_id);
       
        if (saleDate == "0")
            pstmt->setNull(6, sql::DataType::DATE);
        else
            pstmt->setString(6, saleDate);

        pstmt->executeUpdate();
        delete pstmt;

        cout << "Ticket added successfully!\n";
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void AdminTicket::DeleteTicket(Database& db) {
    int id;
    cout << "Enter Ticket ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Ticket WHERE ID = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "Ticket deleted successfully.\n";
        else
            cout << "No ticket found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
