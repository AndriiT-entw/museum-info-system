#pragma once
#ifndef ADMIN_VISITOR_H
#define ADMIN_VISITOR_H

#include "Database.h"

namespace AdminVisitor
{
	void VisitorMenu(Database& db);
	void ViewVisitor(Database& db);
	void AddVisitor(Database& db);
	void DeleteVisitor(Database& db);
}

#endif