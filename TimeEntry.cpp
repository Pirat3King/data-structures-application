// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: New for phase 2 - Function definitions for class TimeEntry
// Author: Pirat3King
// Date: 2023-04-25
// ---------------------------------------------------------------------------

#include "TimeEntry.h"

TimeEntry::TimeEntry(std::string& p, std::string& e, std::string& d, int t)
{
    projectName = p;
    employeeName = e;
    date = d;
    timeSpent = t;
}

TimeEntry::TimeEntry()
{
    projectName = "";
    employeeName = "";
    date = "";
    timeSpent = 0;
}
