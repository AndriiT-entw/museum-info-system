#pragma once
#ifndef MANAGER_TICKET_H
#define MANAGER_TICKET_H

#include "Database.h"

namespace ManagerTicket {
    void menu(Database& db);
    void viewTickets(Database& db);
    void editTicketPrice(Database& db);
}

#endif
