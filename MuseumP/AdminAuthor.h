#pragma once
#ifndef ADMIN_AUTHOR_H
#define ADMIN_AUTHOR_H

#include "Database.h"

namespace AdminAuthor
{
	void AuthorMenu(Database& db);
	void ViewAuthor(Database& db);
	void AddAuthor(Database& db);
	void DeleteAuthor(Database& db);
}

#endif