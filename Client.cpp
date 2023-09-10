// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Function definitions for class Client
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "Client.h"
#include <iostream>

Client::Client(std::string b, std::string c, std::string e, std::string p)
{
	businessName = b;
	contactName = c;
	email = e;
	phone = p;
}

Client::Client()
{
	businessName = "";
	contactName = "";
	email = "";
	phone = "";
}

//Display client details
void Client::print()
{
	std::cout << "\nBusiness Name: " << businessName
			  << "\nContact: " << contactName
			  << "\nEmail: " << email
			  << "\nPhone: " << phone << std::endl;
}