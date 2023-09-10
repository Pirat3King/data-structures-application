// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: A basic console app containing features that are useful for a 
//              web design firm. Maintains CSV 'databases' for lists of 
//              projects, employees, clients, template web files, and 
//              timesheet. The purpose of this project was to explore data 
//              structures and programming styles in CPP.
// Author: Pirat3King
// Date: 2023-05-07
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Precompiled Headers
// ---------------------------------------------------------------------------

#include <iostream>
#include <filesystem>
#include <chrono>
#include <sstream>
#include "ClientList.h"
#include "EmployeeList.h"
#include "ProjectList.h"
#include "FileList.h"
#include "TimeSheet.h"

// ---------------------------------------------------------------------------
// Function Prototypes
// ---------------------------------------------------------------------------

void printBanner();
void mainMenu();
void projectMenu();
void timeMenu();
void templateMenu();
void employeeMenu();
void payrollMenu();

void mkdir(const std::string d);
bool isValidInput(std::string name);
std::string getDate();

Project* newProject();
Project* searchProject();
void editProjectFile();
void renderProject();
void newProjectTask();
void updateProjectTask();
void printProjectTasks();

Client* newClient();
Client* searchClient(std::string n);

void updateBudget();
void updateTimesheet();

HTMLFile* newTemplate();
HTMLFile* searchTemplate();
void editTemplate();
void renderTemplate();

Employee* newEmployee();
std::string searchEmployeeHelper();
Employee* searchEmployee(std::string n);
bool delEmployee();

void printMonthlyLabor();

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------
const std::string DATA = "./DATA/";
const std::string PROJECTFILES = DATA + "PROJECTFILES";
const std::string TEMPLATES = DATA + "TEMPLATES";

EmployeeList* eList = new EmployeeList(DATA + "EMPLOYEES.txt");
ClientList* cList = new ClientList(DATA + "CLIENTS.txt");
FileList* tList = new FileList(TEMPLATES, "TEMPLATES.txt");
ProjectList* pList = new ProjectList(eList, cList, PROJECTFILES, DATA + "PROJECTS.txt");
TimeSheet* timeList = new TimeSheet(DATA + "TIMESHEET.txt");

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------
int main()
{
    printBanner();

    //if necessary, create the directories for storing data
    mkdir(DATA);
    mkdir(PROJECTFILES);
    mkdir(TEMPLATES);

    //check for existing data files. Load if they exist, create if they don't
    eList->preLoadCheck();
    cList->preLoadCheck();
    tList->preLoadCheck();
    pList->preLoadCheck();
    timeList->preLoadCheck();
    

    int sel = 0, sel1 = 0;

    do
    {
        mainMenu();
        std::cin >> sel;

        switch (sel)
        {
            case 1: //Project Submenu
            {
                projectMenu();
                std::cin >> sel1;
                switch (sel1)
                {
                    case 1: //Create New
                    {
                        newProject();
                        break;
                    }
                    case 2: //Search by name and display details if found
                    {
                        Project* p = searchProject();
                        if (p != nullptr)
                            p->print();
                        break;
                    }
                    case 3: //Edit HTML file in Notepad
                    {
                        editProjectFile();
                        break;
                    }
                    case 4: //Render in Browser
                    {
                        renderProject();
                        break;
                    }
                    case 5: //New for phase 2 - Create new task for project
                    {
                        newProjectTask();
                        break;
                    }
                    case 6: ////New for phase 2 - Update status of project task
                    {
                        updateProjectTask();
                        break;
                    }
                    case 7: ////New for phase 2 - Print statuses of project tasks
                    {
                        printProjectTasks();
                        break;
                    }
                    case 8: //Back
                        break;
                    default:
                    {
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        std::cout << "\nError: Invalid option" << std::endl;
                        break;
                    }
                }
                break;
            }

            case 2: //New for phase 2 - Timesheet Submenu
            {
                timeMenu();
                std::cin >> sel1;
                switch (sel1)
                {
                    case 1: //Update budget
                    {
                        updateBudget();
                        break;
                    }
                    case 2: //update timesheet
                    {
                        updateTimesheet();
                        break;
                    }
                    case 3: //Back
                        break;
                    default:
                    {
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        std::cout << "\nError: Invalid option" << std::endl;
                        break;
                    }
                }
                break;
            }

            case 3: //Template Submenu
            {
                templateMenu();
                std::cin >> sel1;
                switch (sel1)
                {
                    case 1: //Create New
                    {
                        newTemplate();
                        break;
                    }
                    case 2: //Search by name and display details if found
                    {
                        HTMLFile* f = searchTemplate();
                        if (f != nullptr)
                            f->print();
                        break;
                    }
                    case 3: //Edit in Notepad
                    {
                        editTemplate();
                        break;
                    }
                    case 4: //Render in Browser
                    {
                        renderTemplate();
                        break;
                    }
                    case 5: //Back
                        break;
                    default:
                    {
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        std::cout << "\nError: Invalid option" << std::endl;
                        break;
                    }
                }
                break;
            }

            case 4: //Employee Submenu
            {
                employeeMenu();
                std::cin >> sel1;
                switch (sel1)
                {
                    case 1: //Create new
                    {
                        newEmployee();
                        break;
                    }
                    case 2: //Search by name or ID and display details if found
                    {
                        Employee* e = searchEmployee(searchEmployeeHelper());
                        if (e != nullptr)
                            e->print();

                        break;
                    }
                    case 3: //Delete employee record
                    {
                        delEmployee();
                        break;
                    }
                    case 4:
                        break;
                    default:
                    {
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        std::cout << "\nError: Invalid option" << std::endl;
                        break;
                    }
                }
                break;
            }
            
            case 5: //Payroll Submenu
            {
                payrollMenu();
                std::cin >> sel1;
                switch (sel1)
                {
                    case 1: //Display monthly cost of labor 
                    {
                        printMonthlyLabor();
                        break;
                    }
                    case 2: //Display list of addresses to mail checks to
                    {
                        eList->printMailList();
                        break;
                    }
                    case 3: //New for phase 2 - Record employee attendance
                    {
                        eList->recAttendance(getDate());
                        break;
                    }
                    case 4:
                        break;
                    default:
                    {
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        std::cout << "\nError: Invalid option" << std::endl;
                        break;
                    }
                }
                break;
            }

            case 6: //Save data and quit program
            {
                std::cout << "Saving data..." << std::endl;

                eList->saveData();
                cList->saveData();
                tList->saveData();
                pList->saveData();
                timeList->saveData();

                std::cout << "Goodbye" << std::endl;
                break;
            }

            default:
            {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                std::cout << "\nError: Invalid option" << std::endl;
                break;
            }
        }
    } while (sel != 6);

    return 0;
}

// ---------------------------------------------------------------------------
// Function Definitions
// ---------------------------------------------------------------------------

// ------------------------------Menus----------------------------------------

//Display banner
void printBanner()
{
    std::cout << "---------------------------------------------------\n"
              << "             Web Design Business App               \n"
              << "---------------------------------------------------" << std::endl;
}

//Display program menu and prompt user selection
void mainMenu()
{
    std::cout << "\nChoose an option below to continue:\n"
              << "\t1) Manage Projects\n"
              << "\t2) Update Budget and Timesheets\n"
              << "\t3) Manage Template Repo\n"
              << "\t4) Manage Employees\n"
              << "\t5) Manage Payroll and Attendance\n"
              << "\t6) Quit\n\n"

              << "Select Option: ";
}

//Display project submenu and prompt user selection
void projectMenu()
{
    std::cout << "\nChoose an option below to continue:\n"
              << "\t1) New Project\n"
              << "\t2) Search Project\n"
              << "\t3) Edit Project File in Notepad\n"
              << "\t4) Render Project in Browser\n"
              << "\t5) Create New Project Task\n"
              << "\t6) Update Project Task\n"
              << "\t7) Print Project Tasks\n"
              << "\t8) Back\n\n"

              << "Select Option: ";
}

//New for phase 2
//Display budget / timesheet submenu and prompt user selection
void timeMenu()
{
    std::cout << "\nChoose an option below to continue:\n"
              << "\t1) Update Budget\n"
              << "\t2) Update Timesheet\n"
              << "\t3) Back\n\n"

              << "Select Option: ";
}

//Display website template repo submenu and prompt user selection
void templateMenu()
{
    std::cout << "\nChoose an option below to continue:\n"
              << "\t1) New Template\n"
              << "\t2) Search Template\n"
              << "\t3) Edit Template in Notepad\n"
              << "\t4) Render Template in Browser\n"
              << "\t5) Back\n\n"

              << "Select Option: ";
}

//Display employee submenu and prompt user selection
void employeeMenu()
{
    std::cout << "\nChoose an option below to continue:\n"
              << "\t1) New Employee\n"
              << "\t2) Search Employee\n"
              << "\t3) Delete Employee\n"
              << "\t4) Back\n\n"

              << "Select Option: ";
}

//Display payroll submenu and prompt user selection
void payrollMenu()
{
    std::cout << "\nChoose an option below to continue:\n"
              << "\t1) Display total monthly labor cost\n"
              << "\t2) Print mailing addresses for checks\n"
              << "\t3) Record Daily Attendance\n"
              << "\t4) Back\n\n"

              << "Select Option: ";
}

// ----------------------------Utilities--------------------------------------

//Check if directory d exists, and create it if it doesn't.
void mkdir(const std::string d)
{
    namespace fs = std::filesystem;

    fs::path p = d;
    bool dirExists = fs::is_directory(p);

    if (!dirExists)
        fs::create_directory(d);
}

//Check if user input is valid.
bool isValidInput(std::string n)
{
    // Check if the input is empty
    if (n.empty())
    {
        std::cerr << "Error: Input is empty." << std::endl;
        return false;
    }

    // Check if the input contains any invalid characters
    std::string bad_chars = "/\\?%*:|\"<>'[]{}";

    for (char c : n)
    {
        if (bad_chars.find(c) != std::string::npos)
        {
            std::cerr << "Error: Input contains invalid characters." << std::endl;
            return false;
        }
    }
    return true;
}

//New for Phase 2
//Returns current date in the format YYYY-MM-DD
std::string getDate()
{
    //current epoch time
    auto now = std::chrono::system_clock::now();

    //convert to local time
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm localtime;
    localtime_s(&localtime, &time);

    //format and convert to string
    std::stringstream date;
    date << std::put_time(&localtime, "%Y-%m-%d");

    return date.str();
}

// ----------------------------Projects---------------------------------------

//Guide user through creating a new project. Return pointer to project
Project* newProject()
{
    std::string name = "", temp = "";
    int budget = 0, deadline = 0;

    //read project name
    std::cout << "Please enter the new project's information:\n"
              << "\nProject Name: ";
    std::getline(std::cin >> std::ws, name);

    //Validate user input. Throws error if input contains invalid characters and exits function
    if (!isValidInput(name)) 
        return nullptr;

    std::transform(name.begin(), name.end(), name.begin(), ::toupper); //transform input to uppercase
    
    //check if project name exists already, exits function if so
    Project* proj = pList->search(name);
    if (proj != nullptr)
    {
        std::cout << "Project " << name << " already exists." << std::endl;
        return proj;
    }
       
    //check if project file with same name already exists, exits function if so
    HTMLFile* file = new HTMLFile(name, PROJECTFILES);
    if (file->fileExists())
    {
        std::cout << "Error: File " << file->getFile() << " already exists. Please choose a new project name." << std::endl;
        return nullptr;
    }     

    //read client name
    std::cout << "\nClient (Company) Name: ";
    std::getline(std::cin >> std::ws, temp);
    if (!isValidInput(temp))
        return nullptr;
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

    //check if client exists already and prompt to create new client if it does not. Returns error if no client found and user chooses to not create a new client
    Client* client = searchClient(temp);
    if (client == nullptr)
    {
        std::cout << "Error: Cannot continue without Client information" << std::endl;
        return nullptr;
    }
        
    //read employee name
    std::cout << "\nAssigned Employee: ";
    std::getline(std::cin >> std::ws, temp);
    if (!isValidInput(temp))
        return nullptr;
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

    //check if employee exists already and prompt to create new employee if it does not. Returns error if no employee found and user chooses to not create a new employee
    Employee* emp = searchEmployee(temp);
    if (emp == nullptr)
    {
        std::cout << "Error: Cannot continue without Employee information" << std::endl;
        return nullptr;
    }
    
    std::cout << "\nProject Budget (in billable hours): ";
    std::cin >> budget;
    if (budget < 0)
    {
        std::cout << "Error: Budget cannot be less than zero hours" << std::endl;
        return nullptr;
    }
    
    std::cout << "\nProject Deadline (in days): ";
    std::cin >> deadline;
    if (deadline < 0)
    {
        std::cout << "Error: Deadline cannot be less than zero days" << std::endl;
        return nullptr;
    }


    //Prompt to use template file
    char t = 'N';
    std::cout << "\nDo you want to create the project file from a template? (y/N): ";
    std::cin >> t;

    if (toupper(t) == 'Y')
    {
        tList->printList(); //display templates

        //read template name
        std::cout << "Please choose a file from the above list: ";
        std::getline(std::cin >> std::ws, temp);
        if (!isValidInput(temp))
            return nullptr;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

        //find template in list and copy to project file
        if (!tList->searchFile(temp)->copyToNew(file)) 
            return nullptr;
    }
    else if (file->createFile()) //create project file
    {
        std::cout << "Created file '" << file->getFile() << "'." << std::endl;
    }
    else
    {
        std::cout << "Could not create file '" << file->getFile() << "'." << std::endl;
        return nullptr;
    }

    Project* p = new Project(name, file, client, budget, deadline, emp);
    
    pList->insert(p);
    pList->saveData();

    std::cout << "\nProject '" << p->getName() << "' created successfully." << std::endl;
    
    return p;
}

//Search for project by name. Prompt user to create new project if not found. Return pointer to project
Project* searchProject()
{
    std::string n = "";
    Project* p = nullptr;

    std::cout << "Project name: ";
    std::getline(std::cin >> std::ws, n);
    if (!isValidInput(n))
        return nullptr;
    std::transform(n.begin(), n.end(), n.begin(), ::toupper);

    p = pList->search(n);

    if (p == nullptr)
    {
        char temp = 'N';
        std::cout << "Project not found. Do you want to add a new project? (y/N): ";
        std::cin >> temp;

        if (toupper(temp) == 'Y')
            return newProject();
        else
            return p;
    }
    else
    {
        std::cout << "Project found." << std::endl;
        return p;
    }
}

//Search for project by name and open project file in notepad.exe if found
void editProjectFile()
{
    Project* p = searchProject();

    if (p == nullptr)
        return;
    else
        p->getFile()->editFile();
}

//Search for project by name and open project file in default browser if found
void renderProject()
{
    Project* p = searchProject();

    if (p == nullptr)
        return;
    else
        p->getFile()->renderFile();
}

//New for Phase 2
//create a new task for a project
void newProjectTask()
{
    std::string name = "";
    Project* p = searchProject();

    if (p == nullptr)
        return;

    std::cout << "Task: ";
    std::getline(std::cin >> std::ws, name);

    if (!isValidInput(name))
        return;
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    p->newTask(name);

    std::cout << "Task " << name << " created successfully." << std::endl;
}

//New for Phase 2
//update the status of a current project task
void updateProjectTask()
{
    std::string name = "";
    int status = 0;
    Project* p = searchProject();

    if (p == nullptr)
        return;

    std::cout << "Task: ";
    std::getline(std::cin >> std::ws, name);

    if (!isValidInput(name))
        return;
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    std::cout << "New status (0=NotStarted, 1=InProgress, 2=Completed, 3=OnHold): ";
    std::cin >> status;

    if (status < 0 || status > 3)
    {
        std::cout << "Error: Invalid status" << std::endl;
        return;
    }

    p->updateTaskStatus(name, status);
}

//New for Phase 2
//display the statuses of all tasks for a given project
void printProjectTasks()
{
    Project* p = searchProject();

    if (p == nullptr)
        return;

    std::cout << "Tasks for project " << p->getName() << ":" << std::endl;
    p->printTasks();
}

// -----------------------------Clients---------------------------------------

//Guide user through creating a new client. Return pointer to client
Client* newClient()
{
    std::string bName = "", cName = "", email = "", phone = "";

    std::cout << "Please enter the client's information:\n"
        << "\tCompany Name: ";
    std::getline(std::cin >> std::ws, bName);
    if (!isValidInput(bName))
        return nullptr;
    std::transform(bName.begin(), bName.end(), bName.begin(), ::toupper);

    std::cout << "\tContact Name: ";
    std::getline(std::cin >> std::ws, cName);
    if (!isValidInput(cName))
        return nullptr;
    std::transform(cName.begin(), cName.end(), cName.begin(), ::toupper);

    std::cout << "\tEmail: ";
    std::getline(std::cin >> std::ws, email);
    if (!isValidInput(email))
        return nullptr;
    std::transform(email.begin(), email.end(), email.begin(), ::toupper);

    std::cout << "\tPhone: ";
    std::getline(std::cin >> std::ws, phone);
    if (!isValidInput(phone))
        return nullptr;
    std::transform(phone.begin(), phone.end(), phone.begin(), ::toupper);

    Client* c = new Client(bName, cName, email, phone);
    cList->addClient(c);
    cList->saveData();

    std::cout << "\nClient '" << c->getBusiness() << "' created successfully." << std::endl;

    return c;
}

//Search for client by company name. Prompt user to create new client if not found. Return pointer to client
Client* searchClient(std::string n)
{
    Client* c = nullptr;

    c = cList->search(n);

    if (c == nullptr)
    {
        char temp = 'N';
        std::cout << "Client not found. Do you want to add a new client? (y/N): ";
        std::cin >> temp;

        if (toupper(temp) == 'Y')
            return newClient();
        else
            return c;
    }
    else
    {
        std::cout << "Client found." << std::endl;
        return c;
    }
}

// ------------------------Budget / Timesheets--------------------------------

//Update project budget to reflect assigned employee's time worked
void updateBudget()
{
    int time = 0, b = 0, newB = 0;
    Project* p;
    Employee* e;

    //Search for a project, verify that it has a time budget remaining
    p = searchProject();
    b = p->getBudget();

    if (b == 0)
    {
        std::cout << p->getName() << " has no more budgeted hours." << std::endl;
        return;
    }
    else
        std::cout << "\n" << p->getName() << " has " << b << " remaining budgeted hours." << std::endl;

    //verify that the correct (assigned) employee is inputting the update
    e = searchEmployee(searchEmployeeHelper());

    if (e == nullptr)
        return;

    if (e != p->getEmployee())
    {
        std::cout << e->getFullName() << " is not assigned to project " << p->getName() << "." << std::endl;
        return;
    }

    //update project budgeted hours
    std::cout << "\nTime spent on " << p->getName() << " (in hours): ";
    std::cin >> time;
    if (time < 0)
    {
        std::cout << "Cannot enter negative time." << std::endl;
        return;
    }

    newB = b - time;

    if (newB < 0)
    {
        std::cout << "Cannot enter more than " << b << " hours for project " << p->getName() << "." << std::endl;
        return;
    }
    else
    {
        p->setBudget(newB);
        std::cout << "\nSuccessfully updated budget.\n"
                  << p->getName() << " has " << newB << " remaining budgeted hours." << std::endl;
    }
}

//New for phase 2
//Add a timesheet entry for an employee and update the project budget accordingly
void updateTimesheet()
{
    std::string pName = "", eName = "", date = getDate();
    int time = 0, b = 0;
    Project* p = nullptr;
    Employee* e = nullptr;

    //Search for employee
    e = searchEmployee(searchEmployeeHelper());
    if (e == nullptr)
        return;

    eName = e->getFullName();

    //Search for project
    p = searchProject();
    if (p == nullptr)
        return;

    b = p->getBudget();
    pName = p->getName();
    
    //verify that employee is assigned to the project
    if (e != p->getEmployee())
    {
        std::cout << eName << " is not assigned to project " << pName << "." << std::endl;
        return;
    }

    std::cout << "\n" << pName << " has " << b << " remaining budgeted hours.\n"
              << "Enter time spent (in hours): ";
    std::cin >> time;

    if (time < 0)
    {
        std::cout << "Cannot enter negative time." << std::endl;
        return;
    }

    if ((b - time) < 0)
    {
        std::cout << "Cannot enter more than " << b << " hours for project " << pName << "." << std::endl;
        return;
    }
    else
    {
        p->setBudget(b - time);
        timeList->getTimeEntries()->insert(TimeEntry(pName, eName, date, time));
        std::cout << "\nSuccessfully updated "<< eName << "'s timesheet.\n"
                  << pName << " has " << b - time << " remaining budgeted hours." << std::endl;
    }
}

// ----------------------------Templates--------------------------------------

//Guide user through creating a new template file and open new file in notepad if successful. Return pointer to file
HTMLFile* newTemplate()
{
    std::string name = "";

    std::cout << "Please give the template a name: ";
    std::getline(std::cin >> std::ws, name);
    if (!isValidInput(name))
        return nullptr;
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    HTMLFile* f = new HTMLFile(name, TEMPLATES);

    if (f->fileExists())
    {
        std::cout << "Template '" << name << "' already exists." << std::endl;
        return nullptr;
    }
    else if (f->createFile())
    {
        std::cout << "Created template '" << f->getFile() << "'." << std::endl;
        tList->addFile(f);
        tList->saveData();
        f->editFile();
        return f;
    }
    else
    {
        std::cout << "Could not create template '" << f->getFile() << "'." << std::endl;
        return nullptr;
    }
}

//Search for template by name. Prompt user to create new template if not found. Return pointer to file
HTMLFile* searchTemplate()
{
    std::string n = "";
    HTMLFile* f = nullptr;

    std::cout << "Template name: ";
    std::getline(std::cin >> std::ws, n);
    if (!isValidInput(n))
        return nullptr;
    std::transform(n.begin(), n.end(), n.begin(), ::toupper);

    f = tList->searchFile(n);

    if (f == nullptr)
    {
        char temp = 'N';
        std::cout << "Template not found. Do you want to create a new template? (y/N): ";
        std::cin >> temp;

        if (toupper(temp) == 'Y')
            return newTemplate();
        else
            return f;
    }
    else
    {
        std::cout << "Template found." << std::endl;
        return f;
    }
}

//Search for template by name and open file in notepad.exe if found
void editTemplate()
{
    HTMLFile* f = searchTemplate();

    if (f == nullptr)
        return;
    else
        f->editFile();
}

//Search for template by name and open file in default browser if found
void renderTemplate()
{
    HTMLFile* f = searchTemplate();

    if (f == nullptr)
        return;
    else
        f->renderFile();
}

// ----------------------------Employees--------------------------------------

//Guide user through creating a new project. Return pointer to project
Employee* newEmployee()
{
    std::string fName = "", lName = "", email = "", phone = "", addr = "", bank = "";
    int sal = 0;
    bool dir = false;
    char temp = 'N';

    //Prompt first name
    std::cout << "Please enter the new employee's information:\n"
              << "\tFirst Name: ";
    std::getline(std::cin >> std::ws, fName);
    if (!isValidInput(fName))
        return nullptr;
    std::transform(fName.begin(), fName.end(), fName.begin(), ::toupper);
    
    //Prompt last name
    std::cout << "\tLast Name: ";
    std::getline(std::cin >> std::ws, lName);
    if (!isValidInput(lName))
        return nullptr;
    std::transform(lName.begin(), lName.end(), lName.begin(), ::toupper);

    //check if employee exists already, exits function if so
    Employee* emp = eList->search(fName + " " + lName);
    if (emp != nullptr)
    {
        std::cout << "Employee " << emp->getFullName() << " already exists." << std::endl;
        return emp;
    }

    //Prompt email
    std::cout << "\tEmail: ";
    std::getline(std::cin >> std::ws, email);
    if (!isValidInput(email))
        return nullptr;
    std::transform(email.begin(), email.end(), email.begin(), ::toupper);

    //Prompt phone
    std::cout << "\tPhone: ";
    std::getline(std::cin >> std::ws, phone);
    if (!isValidInput(phone))
        return nullptr;
    std::transform(phone.begin(), phone.end(), phone.begin(), ::toupper);

    //Prompt address
    std::cout << "\tAddress (Street, City, State, Zip): ";
    std::getline(std::cin >> std::ws, addr);
    if (!isValidInput(addr))
        return nullptr;
    std::transform(addr.begin(), addr.end(), addr.begin(), ::toupper);

    //Prompt salary
    std::cout << "\tSalary: ";
    std::cin >> sal;
    if (sal < 0)
    {
        std::cout << "Error: Salary cannot be less than zero" << std::endl;
        return nullptr;
    }

    //Prompt use of direct deposit. If yes, asks for bank info, else continue
    std::cout << "\tDirect Deposit (y/N): ";
    std::cin >> temp;

    if (toupper(temp) == 'Y')
    {
        dir = true;
        std::cout << "\tBank Account: ";
        std::getline(std::cin >> std::ws, bank);
        if (!isValidInput(bank))
            return nullptr;
        std::transform(bank.begin(), bank.end(), bank.begin(), ::toupper);
    }
    else
    {
        dir = false;
        bank = "NULL";
    }


    eList->incrTotal(); //increment total number of employees in history. Used to provide unique IDs

    Employee* e = new Employee(eList->getTotal(), fName, lName, email, phone, addr, sal, dir, bank);
    eList->addEmployee(e);
    eList->saveData();

    std::cout << "\nEmployee '" << e->getFullName() << "' created successfully." << std::endl;

    return e;
}

//Prompt for user input to search employee list
std::string searchEmployeeHelper()
{
    std::string n = "";
    
    std::cout << "Employee name or ID: ";
    std::getline(std::cin >> std::ws, n);
    if (!isValidInput(n))
        return "";

    std::transform(n.begin(), n.end(), n.begin(), ::toupper);
    
    return n;
}

//Search for employee by name or id. Prompt user to create new employee record if not found. Return pointer to employee
Employee* searchEmployee(std::string n)
{
    Employee* e = eList->search(n);

    if (e == nullptr)
    {
        char temp = 'N';
        std::cout << "Employee not found. Do you want to add a new employee? (y/N): ";
        std::cin >> temp;

        if (toupper(temp) == 'Y')
            return newEmployee();
        else
            return e;
    }
    else
    {
        std::cout << "Employee found." << std::endl;
        return e;
    }
}

//Delete employee record
bool delEmployee()
{
    std::string n = searchEmployeeHelper();

    Employee* emp = eList->search(n);

    if (emp == nullptr)
    {
        std::cout << "Employee not found." << std::endl;
        return false;
    }
    else //employee record found
    {
        //double check choice
        char t = 'N';
        std::cout << "Are you sure you want to delete the employee record for " << emp->getFullName() << "? (y/N): ";
        std::cin >> t;

        if (toupper(t) == 'Y')
        {
            if (eList->removeEmployee(n)) //attempt to remove employee from list
            {
                std::cout << "Employee removed successfully." << std::endl;
                return true;
            } 
            else
            {
                std::cout << "Error removing employee." << std::endl;
                return false;
            }  
        }
        else
        {
            std::cout << "Employee not removed." << std::endl;
            return false;
        }
    }
}

// -----------------------------Payroll---------------------------------------

//Display the total monthly cost of labor
void printMonthlyLabor()
{
    int total = (eList->getLaborCost()) / 12;

    std::cout << "\nTotal monthly labor: $" << total << std::endl;
}