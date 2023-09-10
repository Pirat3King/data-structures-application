#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Header for Project class. Includes definitions for basic functions.
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include <string>
#include <map>
#include "Client.h"
#include "Employee.h"
#include "HTMLFile.h"

class Project
{
public:
	//constructors
	Project(std::string n, HTMLFile* f, Client* c, int b, int d, Employee* e);
	Project();

	//getters
	std::string getName() { return name; }
	HTMLFile* getFile() { return file; }
	Client* getClient() { return client; }
	int getBudget() { return budget; }
	int getDeadline() { return deadline; }
	Employee* getEmployee() { return employee; }
	
	//setters
	void setName(std::string newName) { name = newName; }
	void setFile(HTMLFile* newFile) { file = newFile; }
	void setClient(Client* newClient) { client = newClient; }
	void setBudget(int newBudget) { budget = newBudget; }
	void setDeadline(int newDeadline) { deadline = newDeadline; }
	void setEmployee(Employee* newEmployee) { employee = newEmployee; }

	void print();

	//New for phase 2
	enum TaskStatus { NotStarted, InProgress, Completed, OnHold };
	Project(std::string n, HTMLFile* f, Client* c, int b, int d, Employee* e, std::map<std::string, TaskStatus> t);
	std::map<std::string, TaskStatus> getTasks() { return tasks; }
	void newTask(std::string n) { tasks[n] = NotStarted; }
	void updateTaskStatus(std::string t, int status);
	void printTasks();

private:
	std::string name;
	HTMLFile* file;
	Client* client;
	int budget, deadline;
	Employee* employee;

	//New for phase 2
	std::map<std::string, TaskStatus> tasks;
};

