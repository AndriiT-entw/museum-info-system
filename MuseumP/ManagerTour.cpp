#include "ManagerTour.h"
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void ManagerTour::menu(Database& db) {
    int choice;
    cout << "\n=== Manager Menu Tours ===\n";
    cout << "1. View Tours\n";
    cout << "2. Edit Guide ID\n";
    cout << "3. Edit Tour Date\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        viewTours(db);
        break;
    case 2:
        editGuideId(db);
        break;
    case 3:
        editTourDate(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void ManagerTour::viewTours(Database& db) {
    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "SELECT tu.ID, tu.Date, " 
            "Guide.Name AS Guide_Name "
            "FROM Tour tu "
            "LEFT JOIN Guide guide ON tu.Guide_ID = Guide.ID");
        sql::ResultSet* res = pstmt->executeQuery();

        cout << "\nTours:\n";
        while (res->next()) {
            cout << "Tour ID: " << res->getInt("ID")
                << ", Tour Date: " << res->getString("Date") 
                << ", Guide Name: " << res->getString("Guide_Name") << endl;
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void ManagerTour::editGuideId(Database& db) {
    int tour_id, new_guide_id;
    cout << "Enter Tour ID: ";
    cin >> tour_id;
    cout << "Enter New Guide ID: ";
    cin >> new_guide_id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "UPDATE tour SET guide_id = ? WHERE id = ?"
        );
        pstmt->setInt(1, new_guide_id);
        pstmt->setInt(2, tour_id);
        pstmt->executeUpdate();

        cout << "Guide ID updated.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void ManagerTour::editTourDate(Database& db) {
    int tour_id;
    string new_date;
    cout << "Enter Tour ID: ";
    cin >> tour_id;
    cout << "Enter New Tour Date (YYYY-MM-DD): ";
    cin >> new_date;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "UPDATE tour SET Date = ? WHERE id = ?"
        );
        pstmt->setString(1, new_date);
        pstmt->setInt(2, tour_id);
        pstmt->executeUpdate();

        cout << "Tour date updated.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
