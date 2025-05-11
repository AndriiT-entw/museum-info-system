#pragma once
#ifndef ADMIN_TOUR_H
#define ADMIN_TOUR_H

#include "Database.h"

namespace AdminTour
{
	void TourMenu(Database& db);
	void ViewTour(Database& db);
	void AddTour(Database& db);
	void DeleteTour(Database& db);
}

#endif