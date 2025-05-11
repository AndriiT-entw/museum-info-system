#include "ManagerTicketSale.h"
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void ManagerTicketSale::menu(Database& db) {
    int choice;
    cout << "\n=== Manager Menu Ticket Sales ===\n";
    cout << "1. View Ticket Sales\n";
    cout << "2. Edit Sales Date\n";
    cout << "3. Edit Number of Tickets\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        viewTicketSales(db);
        break;
    case 2:
        editSalesDate(db);
        break;
    case 3:
        editNumberOfTickets(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void ManagerTicketSale::viewTicketSales(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM ticket_sale");

        cout << "\nTicket Sales:\n";
        while (res->next()) {
            cout << "Seller ID: " << res->getInt("ID")
                << ", Ticket ID: " << res->getInt("Ticket_ID") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void ManagerTicketSale::editSalesDate(Database& db) {
    int id;
    string new_date;
    cout << "Enter Sale ID: ";
    cin >> id;
    cout << "Enter New Sale Date (YYYY-MM-DD): ";
    cin >> new_date;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "UPDATE ticket_sale SET sale_date = ? WHERE id = ?"
        );
        pstmt->setString(1, new_date);
        pstmt->setInt(2, id);
        pstmt->executeUpdate();

        cout << "Sale date updated.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void ManagerTicketSale::editNumberOfTickets(Database& db) {
    int id, quantity;
    cout << "Enter Sale ID: ";
    cin >> id;
    cout << "Enter New Quantity: ";
    cin >> quantity;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "UPDATE ticket_sale SET quantity = ? WHERE id = ?"
        );
        pstmt->setInt(1, quantity);
        pstmt->setInt(2, id);
        pstmt->executeUpdate();

        cout << "Quantity updated.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
