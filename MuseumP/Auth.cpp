#include "Admin.h"
#include "Auth.h"
#include "Manager.h"
#include <sstream>
#include <iomanip>
//#include <openssl/sha.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>

using namespace std;



bool Auth::login(Database& db, string& role) {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;


    sql::Connection* conn = db.getConnection();
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    try {
        pstmt = conn->prepareStatement(
            "SELECT role FROM User WHERE username = ? AND password = ?"
        );
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        res = pstmt->executeQuery();

       /* role.erase(0, role.find_first_not_of(" \t\n\r\f\v"));
        role.erase(role.find_last_not_of(" \t\n\r\f\v") + 1);*/
        if (res->next()) {
            role = res->getString("role");
            cout << "Login successful. Your role: \"" << role << "\"" << endl;

            delete res;
            delete pstmt;
            return true;
        }
        else {
            cout << "Invalid login or password.\n";
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }

    return false;
}

void Auth::handleRoleMenu(Database& db, std::string& role)
{
  

   if(role == "Admin")
   { 
       Admin::AdminMenu(db);
   }
   else if (role == "Manager")
   {
       Manager::ManagerMenu(db);
   }
   else
   {
       return;
   }

}
