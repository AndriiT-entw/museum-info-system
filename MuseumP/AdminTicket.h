#pragma once
#ifndef ADMIN_TICKET_H
#define ADMIN_TICKET_H

#include "Database.h"

namespace AdminTicket
{
	void TicketMenu(Database& db);
	void ViewTicket(Database& db);
	void AddTicket(Database& db);
	void DeleteTicket(Database& db);
}

#endif
