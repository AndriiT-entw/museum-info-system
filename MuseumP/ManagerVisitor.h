#pragma once
#ifndef MANAGER_VISITOR_H
#define MANAGER_VISITOR_H

#include "Database.h"

namespace ManagerVisitor {
    void menu(Database& db);
    void viewVisitors(Database& db);
    void deleteVisitor(Database& db);
}

#endif
