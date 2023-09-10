#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: New for phase 2 - Header for TimeEntry class. Includes 
//              definitions for basic functions and overloads.
// Author: Pirat3King
// Date: 2023-04-25
// ---------------------------------------------------------------------------

#include <string>
#include <tuple>
#include "BTree.h"

class TimeEntry
{
private:
    std::string projectName, employeeName, date;
    int timeSpent;

public:
    TimeEntry(std::string& p, std::string& e, std::string& d, int t);
    TimeEntry();

    //overloaded operators
    bool operator<(const TimeEntry& other) const
    {
        return std::tie(projectName, employeeName, date, timeSpent) < std::tie(other.projectName, other.employeeName, other.date, other.timeSpent);
    }

    bool operator>(const TimeEntry& other) const
    {
        return std::tie(projectName, employeeName, date, timeSpent) > std::tie(other.projectName, other.employeeName, other.date, other.timeSpent);
    }

    bool operator==(const TimeEntry& other) const
    {
        return std::tie(projectName, employeeName, date, timeSpent) == std::tie(other.projectName, other.employeeName, other.date, other.timeSpent);
    }

    friend std::ostream& operator<<(std::ostream& os, const TimeEntry& entry)
    {
        os << "Project: " << entry.projectName << ", "
           << "Employee: " << entry.employeeName << ", "
           << "Date: " << entry.date << ", "
           << "Time spent: " << entry.timeSpent;
        return os;
    }

    //getters
    std::string getProject() const { return projectName; }
    std::string getEmployee() const { return employeeName; }
    std::string getDate() const { return date; }
    int getTime() const { return timeSpent; }

    //setters
    void setProject(std::string n) { projectName = n; }
    void setEmployee(std::string n) { employeeName = n; }
    void setDate(std::string n) { date = n; }
    void setTime(int t) { timeSpent = t; }
};