#pragma once
#ifndef MANAGER_TOUR_H
#define MANAGER_TOUR_H

#include "Database.h"

namespace ManagerTour {
    void menu(Database& db);
    void viewTours(Database& db);
    void editGuideId(Database& db);
    void editTourDate(Database& db);
}

#endif
