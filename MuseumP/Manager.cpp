#include "Manager.h"
#include "ManagerTicket.h"
#include "ManagerVisitor.h"
#include "ManagerTicketSale.h"
#include "ManagerTour.h"
#include "ManagerExhibition.h"

#include <iostream>

using namespace std;

void Manager::ManagerMenu(Database& db) {
    int choice;

    while (true) {
        cout << "\n=== Manager Menu ===\n";
        cout << "1. Tickets\n";
        cout << "2. Visitors\n";
        cout << "3. Tours\n";
        cout << "4. Exhibitions\n";
        cout << "5. Logout\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            ManagerTicket::menu(db);
            break;
        case 2:
            ManagerVisitor::menu(db);
            break;
        case 3:
            ManagerTour::menu(db);
            break;
        case 4:
            ManagerExhibition::menu(db);
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

