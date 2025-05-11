#pragma once
#ifndef ADMIN_TICKET_SELLER_H
#define ADMIN_TICKET_SELLER_H

#include "Database.h"

namespace AdminTicketSeller
{
	void TicketSellerMenu(Database& db);
	void ViewTicketSeller(Database& db);
	void AddTicketSeller(Database& db);
	void DeleteTicketSeller(Database& db);
}

#endif