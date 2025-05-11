#pragma once
#ifndef MANAGER_EXHIBITION_H
#define MANAGER_EXHIBITION_H

#include "Database.h"

namespace ManagerExhibition {
    void menu(Database& db);
    void viewExhibitions(Database& db);
    void editStartDate(Database& db);
    void editEndDate(Database& db);
    void editExhibitionPrice(Database& db);
}

#endif
