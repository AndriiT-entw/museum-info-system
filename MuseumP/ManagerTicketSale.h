#pragma once
#ifndef MANAGER_TICKET_SALE_H
#define MANAGER_TICKET_SALE_H

#include "Database.h"

namespace ManagerTicketSale {
    void menu(Database& db);
    void viewTicketSales(Database& db);
    void editSalesDate(Database& db);
    void editNumberOfTickets(Database& db);
}

#endif
