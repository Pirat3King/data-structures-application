// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Function definitions for class Project
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "Project.h"
#include <iostream>

Project::Project(std::string n, HTMLFile* f, Client* c, int b, int d, Employee* e)
{
	name = n;
	file = f;
	client = c;
	budget = b;
	deadline = d;
	employee = e;

	//New for phase 2 - basic project tasks
	tasks["Choose color palette"] = NotStarted;
	tasks["HTML dev"] = NotStarted;
	tasks["Writing copy"] = NotStarted;
	tasks["Testing"] = NotStarted;
	tasks["Deployment"] = NotStarted;
}

//New for phase 2
Project::Project(std::string n, HTMLFile* f, Client* c, int b, int d, Employee* e, std::map<std::string, TaskStatus> t)
{
	name = n;
	file = f;
	client = c;
	budget = b;
	deadline = d;
	employee = e;
	tasks = t;
}

Project::Project()
{
	name = "";
	file = nullptr;
	client = nullptr;
	budget = 0;
	deadline = 0;
	employee = nullptr;

	//New for phase 2 - basic project tasks
	tasks["Choose color palette"] = NotStarted;
	tasks["HTML dev"] = NotStarted;
	tasks["Writing copy"] = NotStarted;
	tasks["Testing"] = NotStarted;
	tasks["Deployment"] = NotStarted;
}

//Display project details
void Project::print()
{
	std::cout << "\nName: " << name
			  << "\nFile: " << file->getFile()
			  << "\nClient: " << client->getBusiness()
			  << "\nBudget: " << budget
			  << "\nDeadline: " << deadline
			  << "\nEmployee: " << employee->getFullName() << std::endl;
}

//New for phase 2
//update the status of a current task
void Project::updateTaskStatus(std::string t, int status)
{
	if (tasks.find(t) == tasks.end())
		std::cout << "Task not found." << std::endl;
	else
	{
		tasks[t] = static_cast<TaskStatus>(status);
		std::cout << "Task status successfully updated." << std::endl;
	}
}

//New for phase 2
//print all tasks and statuses for project
void Project::printTasks()
{
	for (auto& [task, status] : tasks)
	{
		std::cout << task << ": ";
		switch (status)
		{
			case NotStarted:
				std::cout << "Not Started";
				break;
			case InProgress:
				std::cout << "In Progress";
				break;
			case Completed:
				std::cout << "Completed";
				break;
			case OnHold:
				std::cout << "On Hold";
				break;
		}
		std::cout << std::endl;
	}
}