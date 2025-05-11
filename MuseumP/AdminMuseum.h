#pragma once
#ifndef ADMIN_MUSEUM_H
#define ADMIN_MUSEUM_H

#include "Database.h"

namespace AdminMuseum
{
	void MuseumMenu(Database& db);
	void ViewMuseum(Database& db);
	void AddMuseum(Database& db);
	void DeleteMuseum(Database& db);
}

#endif