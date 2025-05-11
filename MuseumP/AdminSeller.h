#pragma once
#ifndef ADMIN_SELLER_H
#define ADMIN_SELLER_H

#include "Database.h"

namespace AdminSeller
{
	void SellerMenu(Database& db);
	void ViewSeller(Database& db);
	void AddSeller(Database& db);
	void DeleteSeller(Database& db);
}

#endif
