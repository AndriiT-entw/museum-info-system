
#include "TicketSale.h"
#include "Ticket.h"
#include "Database.h"
#include <iomanip>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>

using namespace std;

void TicketSale::buyTickets(Database& db) {
    int quantity = 0;
    cout << "Enter ticket quantity: ";
    cin >> quantity;

    double totalPrice = 0.0;

    for (int i = 0; i < quantity; ++i) {
        int ticket_id;
        string visitor_name;
        string visitor_email;

        cout << "\nEnter Ticket ID: ";
        cin >> ticket_id;
        cout << "Enter your name: ";
        cin.ignore(); // To ignore leftover newline
        getline(cin, visitor_name);
        cout << "Enter your Email: ";
        cin >> visitor_email;

        try {
            sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
                "SELECT Price FROM Ticket WHERE ID = ?");
            pstmt->setInt(1, ticket_id);
            sql::ResultSet* res = pstmt->executeQuery();

            if (res->next()) {
                double price = res->getDouble("Price");
                totalPrice += price;
            }
            else {
                cout << "Ticket ID not found! Price will not be added." << endl;
            }

            delete res;
            delete pstmt;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error: " << e.what() << endl;
        }

        // Insert visitor data
        try {
            sql::PreparedStatement* insertStmt = db.getConnection()->prepareStatement(
                "INSERT INTO Visitor (Ticket_ID, Name, Email) VALUES (?, ?, ?)");
            insertStmt->setInt(1, ticket_id);
            insertStmt->setString(2, visitor_name);
            insertStmt->setString(3, visitor_email);

            insertStmt->execute();
            delete insertStmt;

            cout << "Visitor information saved successfully!" << endl;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error (insert): " << e.what() << endl;
        }
    }

    cout << fixed << setprecision(2); // Always show 2 decimals
    cout << "\nTotal price for " << quantity << " tickets: " << totalPrice << " EUR" << endl;
}

