// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Function definitions for class Employee
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "Employee.h"
#include <sstream>
#include <iostream>

Employee::Employee(int i, std::string f, std::string l, std::string e, std::string p, std::string a, int s, bool d, std::string b, std::set<std::string> att)
{
	id = i;
	fName = f;
	lName = l;
	email = e;
	phone = p;
	addr = a;
	salary = s;
	dirDeposit = d;
	bank = b;
	attendance = att;
}

Employee::Employee(int i, std::string f, std::string l, std::string e, std::string p, std::string a, int s, bool d, std::string b)
{
	id = i;
	fName = f;
	lName = l;
	email = e;
	phone = p;
	addr = a;
	salary = s;
	dirDeposit = d;
	bank = b;
}

Employee::Employee()
{
	id = 0;
	fName = "";
	lName = "";
	email = "";
	phone = "";
	addr = "";
	salary = 0;
	dirDeposit = false;
	bank = "";
}

//Parses full address into its component parts and return via reference
void Employee::getAddress(std::string& str, std::string& c, std::string& sta, std::string& z)
{
	std::stringstream ss(addr);

	std::getline(ss >> std::ws, str, ',');
	std::getline(ss >> std::ws, c, ',');
	std::getline(ss >> std::ws, sta, ',');
	std::getline(ss >> std::ws, z);
}

//Parses full address into its component parts and print mailing address
void Employee::printMailAddr()
{
	std::string street, city, state, zip;
	
	getAddress(street, city, state, zip);

	std::cout << "\n" << fName << " " << lName << "\n"
		<< street << "\n"
		<< city << ", " << state << " " << zip << std::endl;
}

//Display employee details
void Employee::print()
{
	std::cout << "\nName: " << fName << " " << lName
			  << "\nEmail: " << email
			  << "\nPhone: " << phone << std::endl;
}



