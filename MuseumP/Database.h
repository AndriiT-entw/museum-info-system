
#ifndef DATABASE_H
#define DATABASE_H

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <string>

class Database {
private:
    std::string server;
    std::string username;
    std::string password;
    std::string database_Name;

    sql::Driver* driver;
    sql::Connection* connection;

public:
    Database(
        const std::string& server = "tcp://127.0.0.1:3306",
        const std::string& username = "root",
        const std::string& password = "4321Qwer",
        const std::string& database_Name = "museum"
    );

    ~Database();

    void connect();
    void disconnect();
    bool isConnected() const;
    sql::Connection* getConnection();
};

#endif


