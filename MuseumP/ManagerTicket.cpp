#include "ManagerTicket.h"
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void ManagerTicket::menu(Database& db) {
    int choice;
    cout << "\n=== Manager Menu Tickets ===\n";
    cout << "1. View Tickets\n";
    cout << "2. Edit Ticket Price\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        viewTickets(db);
        break;
    case 2:
        editTicketPrice(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void ManagerTicket::viewTickets(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT ID, Ticket_Type, Price FROM ticket");

        cout << "\nTickets:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Type: " << res->getString("Ticket_Type")
                << ", Price: " << res->getDouble("Price") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void ManagerTicket::editTicketPrice(Database& db) {
    int ticket_id;
    double new_price;
    cout << "Enter Ticket ID: ";
    cin >> ticket_id;
    cout << "Enter New Price: ";
    cin >> new_price;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "UPDATE ticket SET price = ? WHERE id = ?"
        );
        pstmt->setDouble(1, new_price);
        pstmt->setInt(2, ticket_id);
        pstmt->executeUpdate();

        cout << "Price updated successfully.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

