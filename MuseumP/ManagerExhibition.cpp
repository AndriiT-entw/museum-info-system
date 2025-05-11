#include "ManagerExhibition.h"
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void ManagerExhibition::menu(Database& db) {
    int choice;
    cout << "\n=== Manager Menu Exhibition ===\n";
    cout << "1. View Exhibition\n";
    cout << "2. Edit Exhibition Start Date\n";
    cout << "3. Edit Exhibition End Date\n";
    cout << "4. Edit Exhibition Price\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        viewExhibitions(db);
        break;
    case 2:
        editStartDate(db);
        break;
    case 3:
        editEndDate(db);
        break;
    case 4:
        editExhibitionPrice(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void ManagerExhibition::viewExhibitions(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM exhibition");

        cout << "\nExhibitions:\n";
        while (res->next()) {
            cout << "ID: " << res->getInt("ID")
                << ", Name: " << res->getString("Name")
                << ", Start: " << res->getString("Start_Date")
                << ", End: " << res->getString("End_Date")
                << ", Cost: " << res->getDouble("Cost") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void ManagerExhibition::editStartDate(Database& db) {
    int id;
    string new_date;
    cout << "Enter Exhibition ID: ";
    cin >> id;
    cout << "Enter New Start Date (YYYY-MM-DD): ";
    cin >> new_date;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "UPDATE exhibition SET start_date = ? WHERE id = ?"
        );
        pstmt->setString(1, new_date);
        pstmt->setInt(2, id);
        pstmt->executeUpdate();

        cout << "Start date updated.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void ManagerExhibition::editEndDate(Database& db) {
    int id;
    string new_date;
    cout << "Enter Exhibition ID: ";
    cin >> id;
    cout << "Enter New End Date (YYYY-MM-DD): ";
    cin >> new_date;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "UPDATE exhibition SET end_date = ? WHERE id = ?"
        );
        pstmt->setString(1, new_date);
        pstmt->setInt(2, id);
        pstmt->executeUpdate();

        cout << "End date updated.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void ManagerExhibition::editExhibitionPrice(Database& db) {
    int id;
    double new_price;
    cout << "Enter Exhibition ID: ";
    cin >> id;
    cout << "Enter New Cost: ";
    cin >> new_price;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "UPDATE exhibition SET Cost = ? WHERE id = ?"
        );
        pstmt->setDouble(1, new_price);
        pstmt->setInt(2, id);
        pstmt->executeUpdate();

        cout << "Cost updated.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

