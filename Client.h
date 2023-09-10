#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Header for Client class. Includes definitions for basic functions.
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include <string>

class Client
{
private:
	std::string businessName, contactName, email, phone;

public:
	//constructors
	Client(std::string b, std::string c, std::string e, std::string p);
	Client();

	//getters
	std::string getBusiness() { return businessName; }
	std::string getContact() { return contactName; }
	std::string getEmail() { return email; }
	std::string getPhone() { return phone; }

	//setters
	void setBusiness(std::string newName) { businessName = newName; }
	void setContact(std::string newName) { contactName = newName; }
	void setEmail(std::string newEmail) { email = newEmail; }
	void setPhone(std::string newPhone) { phone = newPhone; }

	void print();
};

