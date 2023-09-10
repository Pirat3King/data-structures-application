// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: New for phase 2 - Function definitions for TimeSheet class
// Author: Pirat3King
// Date: 2023-05-7
// ---------------------------------------------------------------------------

#include "TimeSheet.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

TimeSheet::TimeSheet(std::string c)
{
    csv = c;
}

TimeSheet::TimeSheet()
{
    csv = "";
}

// Load data from CSV into objects and add to list
void TimeSheet::loadData()
{
    std::ifstream file(csv);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << csv << std::endl;
        return;
    }

    timeEntries = new BTree<TimeEntry>();
    std::string line;
    std::getline(file, line); //skip header row

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string projectName, employeeName, date;
        int timeSpent;

        std::getline(iss, projectName, ',');
        std::getline(iss, employeeName, ',');
        std::getline(iss, date, ',');
        iss >> timeSpent;

        timeEntries->insert(TimeEntry(projectName, employeeName, date, timeSpent));
    }

    file.close();
}

//write a B-Tree of TimeEntry objects to a CSV file
void TimeSheet::saveData()
{
    std::ofstream file(csv);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << csv << std::endl;
        return;
    }

    // Header row
    file << "PROJECT,EMPLOYEE,DATE,TIME\n";

    // Traverse the BTree and write the TimeEntry objects to the file using a lambda function.
    timeEntries->traverse([&file](const TimeEntry& entry) {
        file << entry.getProject() << ',' << entry.getEmployee() << ',' << entry.getDate() << ',' << entry.getTime() << '\n';
        });

    file.close();
}

// Check if CSV file exists
bool TimeSheet::fileExists()
{
    namespace fs = std::filesystem;

    if (fs::exists(csv))
        return true;
    else
        return false;
}

// Create CSV file
bool TimeSheet::createFile()
{
    std::ofstream file(csv);

    if (!file.is_open())
        return false;
    else
    {
        file.close();
        return true;
    }
}

// loadData helper. Check for existing CSV file - load if it exists, create if it doesn't
bool TimeSheet::preLoadCheck()
{
    if (fileExists())
    {
        loadData();
        return true;
    }
    else
    {
        createFile();
        return false;
    }
}