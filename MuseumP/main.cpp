#include "Manager.h"
#include "Database.h"
#include "Ticket.h"
#include "Auth.h"
#include "TicketSale.h"
#include "Admin.h" // якщо є окрема логіка
#include "ViewTicketsVisitors.h"
#include <iostream>

using namespace std;

void showMainMenu(Database& db) {
    int choice;
    string role = "";

    while (true) {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Tickets\n";
        cout << "2. Login\n";
        cout << "3. View bought tickets\n";
        cout << "4. Exit\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            TicketMenu::showTicketsMenu(db);
            break;
        case 2:
            if (Auth::login(db, role)) {
                Auth::handleRoleMenu(db, role);
            }
            break;
        case 3:
            ViewTicketsVisitors::ViewTickets(db);
            break;
        case 4:
            cout << "Goodbye!\n";
            return;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }
}

int main() {
    try {
        Database db;
        db.connect();

        if (!db.isConnected()) {
            cout << "Database connection failed!" << endl;
            return 1;
        }

        showMainMenu(db);
    }
    catch (sql::SQLException& e) {
        cerr << "Database error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

