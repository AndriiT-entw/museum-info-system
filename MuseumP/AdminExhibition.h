#pragma once
#ifndef ADMIN_EXHIBITION_H
#define ADMIN_EXHIBITION_H

#include "Database.h"

namespace AdminExhibition
{
	void ExhibitionMenu(Database& db);
	void ViewExhibition(Database& db);
	void AddExhibition(Database& db);
	void DeleteExhibition(Database& db);
}


#endif