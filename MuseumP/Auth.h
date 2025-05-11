#ifndef AUTH_H
#define AUTH_H

#include "Database.h"
#include <string>

class Auth {
public:
    static bool login(Database& db, std::string& role);
    static void handleRoleMenu(Database& db, std::string& role);
};

#endif // AUTH_H

