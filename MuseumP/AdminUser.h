#pragma once
#ifndef ADMIN_USER_H
#define ADMIN_USER_H

#include "Database.h"

namespace AdminUser
{
	void UserMenu(Database& db);
	void ViewUser(Database& db);
	void AddUser(Database& db);
	void DeleteUser(Database& db);
}

#endif