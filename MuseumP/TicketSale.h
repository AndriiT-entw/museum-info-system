
#ifndef TICKETSALE_H
#define TICKETSALE_H

#include "Database.h"
#include <iostream>
#include <string>

using namespace std;

class TicketSale {
public:
    static void buyTickets(Database& db);
};

#endif
