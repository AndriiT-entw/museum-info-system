
#include "Database.h"
#include <iostream>

Database::Database(const std::string& server, const std::string& username, const std::string& password, const std::string& database_Name)
    : server(server), username(username), password(password), database_Name(database_Name), driver(nullptr), connection(nullptr) {
}

Database::~Database() {
    disconnect();
}

void Database::connect() {
    try {
        driver = get_driver_instance();
        connection = driver->connect(server, username, password);
        connection->setSchema(database_Name);
        std::cout << "Connected to the database successfully!" << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << " (SQLState: " << e.getSQLState() << ")" << std::endl;
    }
}

void Database::disconnect() {
    if (connection) {
        delete connection;
        connection = nullptr;
        std::cout << "Disconnected from the database." << std::endl;
    }
}

sql::Connection* Database::getConnection() {
    if (!connection) {
        connect();
    }
    return connection;
}

bool Database::isConnected() const {
    return connection != nullptr;
}
