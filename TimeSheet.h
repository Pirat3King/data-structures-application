#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: New for phase 2 - header for TimeSheet class.
// Author: Pirat3King
// Date: 2023-05-7
// ---------------------------------------------------------------------------

#include <string>
#include <tuple>
#include "BTree.h"
#include "TimeEntry.h"

class TimeSheet
{
private:
    BTree<TimeEntry>* timeEntries;
    std::string csv;

public:
    TimeSheet(std::string c);
    TimeSheet();

    //load/save timesheet data from CSV file
    void loadData();
    void saveData();

    //CSV operators
    bool fileExists();
    bool createFile();
    bool preLoadCheck();

    //getters
    BTree<TimeEntry>* getTimeEntries() { return timeEntries; }
};