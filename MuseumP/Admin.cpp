#include "Admin.h"
#include "AdminAuthor.h"
#include "AdminExhibition.h"
#include "AdminExhibitionAuthor.h"
#include "AdminGuide.h"
#include "AdminHall.h"
#include "AdminMuseum.h"
#include "AdminSeller.h"
#include "AdminSponsor.h"
#include "AdminTicket.h"
#include "AdminTicketSeller.h"
#include "AdminTour.h"
#include "AdminUser.h"
#include "AdminVisitor.h"

#include <iostream>

using namespace std;

void Admin::AdminMenu(Database& db)
{
	int choice;

	while (true)
	{
		cout << "\n Admin Menu \n";
		cout << "1. Author \n";
		cout << "2. Exhibition \n";
		cout << "3. Exhibition Author\n";
		cout << "4. Guide \n";
		cout << "5. Hall \n";
		cout << "6. Museum\n";
		cout << "7. Seller\n";
		cout << "8. Sponsor\n";
		cout << "9. Ticket\n";
		cout << "10. Ticket Seller\n";
		cout << "11. Tour\n";
		cout << "12. User\n";
		cout << "13. Visitor\n";
		cout << "14. Logout\n";

		cout << "Enter choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			AdminAuthor::AuthorMenu(db);
			break;
		case 2:
			AdminExhibition::ExhibitionMenu(db);
			break;
		case 3:
			AdminExhibitionAuthor::ExhibitionAuthorMenu(db);
			break;
		case 4:
			AdminGuide::GuideMenu(db);
			break;
		case 5:
			AdminHall::HallMenu(db);
			break;
		case 6:
			AdminMuseum::MuseumMenu(db);
			break;
		case 7:
			AdminSeller::SellerMenu(db);
			break;
		case 8:
			AdminSponsor::SponsorMenu(db);
			break;
		case 9:
			AdminTicket::TicketMenu(db);
			break;
		case 10:
			AdminTicketSeller::TicketSellerMenu(db);
			break;
		case 11:
			AdminTour::TourMenu(db);
			break;
		case 12:
			AdminUser::UserMenu(db);
			break;
		case 13:
			AdminVisitor::VisitorMenu(db);
			break;
		case 14:
			return;
		default:
			cout << "Invalid choice. Try again. \n";

		}
	}
}
