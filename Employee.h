#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Header for Employee class. Includes definitions for basic functions.
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include <string>
#include <set>

class Employee
{
private:
	std::string fName, lName, email, phone, addr, bank;
	int id, salary;
	bool dirDeposit;

	//new for phase 2
	std::set<std::string> attendance;

public:
	//constructors
	Employee(int i, std::string f, std::string l, std::string e, std::string p, std::string a, int s, bool d, std::string b, std::set<std::string> att);
	Employee(int i, std::string f, std::string l, std::string e, std::string p, std::string a, int s, bool d, std::string b);
	Employee();

	//getters
	int getID() { return id; }
	std::string getFName() { return fName; }
	std::string getLName() { return lName; }
	std::string getFullName() { return fName + " " + lName; }
	std::string getEmail() { return email; }
	std::string getPhone() { return phone; }
	std::string getAddress() { return addr; }
	void getAddress(std::string& str, std::string& c, std::string& sta, std::string& z); //parses address into parts
	int getSalary() { return salary; }
	bool getDirDeposit() { return dirDeposit; }
	std::string getBank() { return bank; }

	//setters
	void setID(int newID) { id = newID; }
	void setFName(std::string newName) { fName = newName; }
	void setLName(std::string newName) { lName = newName; }
	void setEmail(std::string newEmail) { email = newEmail; }
	void setPhone(std::string newPhone) { phone = newPhone; }
	void setAddress(std::string newAddr) { addr = newAddr; }
	void setSalary(int newSal) { salary = newSal; }
	void setDirDeposit(bool newDirDeposit) { dirDeposit = newDirDeposit; }
	void setBank(std::string newBank) { bank = newBank; }

	void printMailAddr();
	void print();

	//New for phase 2
	void addAttendance(std::string date) { attendance.insert(date); }
	std::set<std::string> getAttendance() { return attendance; }
	void setAttendance(std::set<std::string> s) { attendance = s; }

};

