#include "AdminExhibitionAuthor.h"
#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

void AdminExhibitionAuthor::ExhibitionAuthorMenu(Database& db) {
    int choice;
    cout << "\n=== Admin Menu ExhibitionAuthor ===\n";
    cout << "1. View ExhibitionAuthor\n";
    cout << "2. Add ExhibitionAuthor\n";
    cout << "3. Delete ExhibitionAuthor\n";
    cout << "Select an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        ViewExhibitionAuthor(db);
        break;
    case 2:
        AddExhibitionAuthor(db);
        break;
    case 3:
        DeleteExhibitionAuthor(db);
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

void AdminExhibitionAuthor::ViewExhibitionAuthor(Database& db) {
    try {
        sql::Statement* stmt = db.getConnection()->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Exhibition_Author");

        cout << "\nExhibitionAuthor Records:\n";
        while (res->next()) {
            cout << "Exhibition ID: " << res->getInt("Exhibition_ID")
                << ", Author ID: " << res->getInt("Author_ID")
                << ", Share: " << res->getInt("Share") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminExhibitionAuthor::AddExhibitionAuthor(Database& db) {
    int exhibition_id, author_id, share;

    cout << "\n=== Add New ExhibitionAuthor ===\n";
    cout << "Enter Exhibition ID: ";
    cin >> exhibition_id;
    cout << "Enter Author ID: ";
    cin >> author_id;
    cout << "Enter Share Percentage: ";
    cin >> share;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "INSERT INTO Exhibition_Author (Exhibition_ID, Author_ID, Share) VALUES (?, ?, ?)"
        );
        pstmt->setInt(1, exhibition_id);
        pstmt->setInt(2, author_id);
        pstmt->setInt(3, share);
        pstmt->executeUpdate();
        delete pstmt;

        cout << "ExhibitionAuthor entry added successfully!\n";
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void AdminExhibitionAuthor::DeleteExhibitionAuthor(Database& db) {
    int exhibition_id, author_id;
    cout << "Enter Exhibition ID: ";
    cin >> exhibition_id;
    cout << "Enter Author ID: ";
    cin >> author_id;

    try {
        sql::PreparedStatement* pstmt = db.getConnection()->prepareStatement(
            "DELETE FROM Exhibition_Author WHERE Exhibition_ID = ? AND Author_ID = ?"
        );
        pstmt->setInt(1, exhibition_id);
        pstmt->setInt(2, author_id);
        int affected = pstmt->executeUpdate();

        if (affected > 0)
            cout << "ExhibitionAuthor entry deleted successfully.\n";
        else
            cout << "No matching entry found.\n";

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
