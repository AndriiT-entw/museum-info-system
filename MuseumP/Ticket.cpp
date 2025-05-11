#include "Ticket.h"
#include "TicketSale.h"
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <iomanip>
using namespace std;

namespace TicketMenu {

    void displayTickets(Database& db) {
        try {
            sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
                "SELECT t.ID, t.Ticket_Type, t.Price, t.Visitor_Category, "
                "tour.Name AS Tour_Name, museum.Name AS Museum_Name "
                "FROM Ticket t "
                "LEFT JOIN Tour tour ON t.Tour_ID = tour.ID "
                "LEFT JOIN Museum museum ON t.Museum_ID = museum.ID"
            );

            sql::ResultSet* res = pstmt->executeQuery();

            cout << "\n=== Available Tickets ===\n";
            cout << left << setw(5) << "ID"
                << setw(15) << "Type"
                << setw(10) << "Price"
                << setw(20) << "Category"
                << setw(20) << "Tour"
                << setw(20) << "Museum" << endl;

            while (res->next()) {
                cout << left << setw(5) << res->getInt("ID")
                    << setw(15) << res->getString("Ticket_Type")
                    << setw(10) << res->getDouble("Price")
                    << setw(20) << res->getString("Visitor_Category")
                    << setw(20) << res->getString("Tour_Name")
                    << setw(20) << res->getString("Museum_Name") << endl;
            }

            delete res;
            delete pstmt;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error: " << e.what() << endl;
        }
    }

    void showTicketsMenu(Database& db) {
        int choice;
       // while (true) {
            displayTickets(db);

            cout << "\n1. Buy Ticket\n";
            cout << "2. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {
            case 1:
                TicketSale::buyTickets(db);
                break;
            case 2:
                return;
            default:
                cout << "Invalid option. Try again.\n";
            }
       // }
    }

}
