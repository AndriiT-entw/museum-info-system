#pragma once
#ifndef ADMIN_SPONSOR_H
#define ADMIN_SPONSOR_H

#include "Database.h"

namespace AdminSponsor
{
	void SponsorMenu(Database& db);
	void ViewSponsor(Database& db);
	void AddSponsor(Database& db);
	void DeleteSponsor(Database& db);
}

#endif