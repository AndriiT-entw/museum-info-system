#pragma once
#ifndef ADMIN_GUIDE_H
#define ADMIN_GUIDE_H

#include "Database.h"

namespace AdminGuide
{
	void GuideMenu(Database& db);
	void ViewGuide(Database& db);
	void AddGuide(Database& db);
	void DeleteGuide(Database& db);
}

#endif