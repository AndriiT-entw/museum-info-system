#include "AdminTour.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminTour::TourMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu Tour ===\n";
    cout << "1. View Tours\n";
    cout << "2. Add Tour\n";
    cout << "3. Delete Tour\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewTour(db);
        break;
    case 2:
        AddTour(db);
        break;
    case 3:
        DeleteTour(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminTour::ViewTour(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Tour");

        cout << "\nTours:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Name")
                << ", Guide id: " << res->getInt("Guide_ID")
                << ", Date: " << res->getString("Date") 
                << ", Museum id: " << res->getInt("Museum_ID") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
void AdminTour::AddTour(Database& db)
{
    std::string name, date;
    int guideId, museumId;

    std::cout << "\n=== Add New Tour ===\n";
    std::cout << "Enter Name: ";
    std::cin.ignore(); // clear buffer
    std::getline(std::cin, name);

    std::cout << "Enter Date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    std::cout << "Enter Guide ID: ";
    std::cin >> guideId;

    std::cout << "Enter Museum ID: ";
    std::cin >> museumId;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO Tour (Name, Date, Guide_ID, Museum_ID) VALUES (?, ?, ?, ?)"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, date);
        pstmt->setInt(3, guideId);
        pstmt->setInt(4, museumId);

        pstmt->executeUpdate();
        delete pstmt;

        std::cout << "User added successfully!\n";
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << "\n";
    }
}

void AdminTour::DeleteTour(Database& db) {
    int id;
    cout << "Enter Tour ID to delete: ";
    cin >> id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Tour WHERE id = ?"
        );
        pstmt->setInt(1, id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "Tour deleted successfully.\n";
        else
            cout << "No user found with that ID.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}