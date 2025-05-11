/*#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;

// Database connection details
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "4321Qwer";

int main() {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    try {
        // Connect to the MySQL server
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    try {
        // Set the schema (database)
        con->setSchema("Museum");

        // Insert data into the Museum table
        pstmt = con->prepareStatement("INSERT INTO Museum (Name, Address, Contact_Info) VALUES (?, ?, ?)");
        pstmt->setString(1, "National History Museum");
        pstmt->setString(2, "123 Museum St, Cityville");
        pstmt->setString(3, "info@nhmuseum.com");
        pstmt->execute();
        cout << "Inserted into Museum table." << endl;

        // Insert data into the Hall table
        pstmt = con->prepareStatement("INSERT INTO Hall (Hall_Name, Capacity, Museum_ID) VALUES (?, ?, ?)");
        pstmt->setString(1, "Main Exhibition Hall");
        pstmt->setInt(2, 200);
        pstmt->setInt(3, 1); // Assuming Museum ID 1 exists
        pstmt->execute();
        cout << "Inserted into Hall table." << endl;

        // Insert data into the Guide table
        pstmt = con->prepareStatement("INSERT INTO Guide (Name, Contact_Info, Years_Experience, Museum_ID) VALUES (?, ?, ?, ?)");
        pstmt->setString(1, "John Doe");
        pstmt->setString(2, "john.doe@museum.com");
        pstmt->setInt(3, 5);
        pstmt->setInt(4, 1); // Assuming Museum ID 1 exists
        pstmt->execute();
        cout << "Inserted into Guide table." << endl;

        // Insert data into the Tour table
        pstmt = con->prepareStatement("INSERT INTO Tour (Name, Number_of_People, Guide_ID, Date, Museum_ID) VALUES (?, ?, ?, ?, ?)");
        pstmt->setString(1, "Ancient History Tour");
        pstmt->setInt(2, 20);
        pstmt->setInt(3, 1); // Assuming Guide ID 1 exists
        pstmt->setString(4, "2025-01-10"); // Example date
        pstmt->setInt(5, 1); // Assuming Museum ID 1 exists
        pstmt->execute();
        cout << "Inserted into Tour table." << endl;

        // Insert data into the Ticket table
        pstmt = con->prepareStatement("INSERT INTO Ticket (Type, Price, Visitor_Category, Tour_ID, Museum_ID) VALUES (?, ?, ?, ?, ?)");
        pstmt->setString(1, "Adult");
        pstmt->setDouble(2, 15.50);
        pstmt->setString(3, "General");
        pstmt->setInt(4, 1); // Assuming Tour ID 1 exists
        pstmt->setInt(5, 1); // Assuming Museum ID 1 exists
        pstmt->execute();
        cout << "Inserted into Ticket table." << endl;

        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQLException: " << e.what() << endl;
        cout << "SQLState: " << e.getSQLState() << endl;
    }

    delete con;
    system("pause");
    return 0;
}
*/
