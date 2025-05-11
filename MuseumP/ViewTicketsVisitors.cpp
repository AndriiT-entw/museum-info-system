#include "ViewTicketsVisitors.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void ViewTicketsVisitors::ViewTickets(Database& db)
{
	string name, email;

	cout << "Enter name: ";
    cin.ignore();
	getline(cin, name);

	cout << "Enter email: ";
	getline(cin, email);

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "SELECT v.Name, v.Email, t.Ticket_Type, t.Visitor_Category, t.Price, t.Sale_Date, "
            "tour.Name AS Tour_Name, mu.Name AS Museum_Name "
            "FROM visitor v "
            "JOIN ticket t ON v.Ticket_ID = t.ID "
            "LEFT JOIN Tour tour ON t.Tour_ID = tour.ID "
            "LEFT JOIN Museum mu ON t.Museum_ID = mu.ID "
            "WHERE v.Name = ? AND v.Email = ?"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, email);

        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            cout << "\n=== Visitor and Ticket Info ===\n";
            cout << "Name: " << res->getString("Name") << endl;
            cout << "Email: " << res->getString("Email") << endl;
            cout << "Ticket Type: " << res->getString("Ticket_Type") << endl;
            cout << "Category: " << res->getString("Visitor_Category") << endl;
            cout << "Price: " << res->getDouble("Price") << endl;
            cout << "Sale Date: " << res->getString("Sale_Date") << endl;
            cout << "Museum Name: " << res->getString("Museum_Name") << endl;
            cout << "Tour Name: " << res->getString("Tour_Name") << endl;
        }
        else {
            cout << "No visitor found with that name and email.\n";
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}
