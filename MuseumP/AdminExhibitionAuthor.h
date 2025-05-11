#pragma once
#ifndef ADMIN_EXHIBITION_AUTHOR_H
#define ADMIN_EXHIBITION_AUTHOR_H

#include "Database.h"

namespace AdminExhibitionAuthor
{
	void ExhibitionAuthorMenu(Database& db);
	void ViewExhibitionAuthor(Database& db);
	void AddExhibitionAuthor(Database& db);
	void DeleteExhibitionAuthor(Database& db);
}

#endif