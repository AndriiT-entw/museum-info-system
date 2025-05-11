#pragma once
#ifndef ADMIN_HALL_H
#define ADMIN_HALL_H

#include "Database.h"

namespace AdminHall
{
	void HallMenu(Database& db);
	void ViewHall(Database& db);
	void AddHall(Database& db);
	void DeleteHall(Database& db);
}

#endif