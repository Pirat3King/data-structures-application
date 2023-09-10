// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Header for class EmployeeList - a doubly-linked circular list of Employee objects.
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "EmployeeList.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

EmployeeList::EmployeeList(std::string c)
{
    head = nullptr;
    size = 0;
    total = 0;
    csv = c;
}

EmployeeList::~EmployeeList()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current->data;
        delete current;
        current = next;
    }
}

//Add employee object to list.
void EmployeeList::addEmployee(const Employee* e)
{
    Node* newNode = new Node(*e);

    if (head == nullptr)
    {
        head = newNode;
        head->next = head;
        head->prev = head;
    }
    else
    {
        newNode->prev = head->prev;
        newNode->next = head;
        head->prev->next = newNode;
        head->prev = newNode;
    }
    size++;
}

//Remove employee object from list.
bool EmployeeList::removeEmployee(const std::string& nameOrID)
{
    //find employee object in list
    Employee* employeeToRemove = search(nameOrID);
    
    if (employeeToRemove == nullptr)
        return false;

    if (employeeToRemove == head->data)
        head = head->next;

    Node* nodeToRemove = head;

    //find node in list that contains employee
    while (nodeToRemove->data != employeeToRemove)
    {
        nodeToRemove = nodeToRemove->next;
    }

    //remove node
    nodeToRemove->prev->next = nodeToRemove->next;
    nodeToRemove->next->prev = nodeToRemove->prev;
    delete nodeToRemove->data;
    delete nodeToRemove;
    
    size--;
    return true;
}

//Search list for employee object by last name, full name, or ID. 
Employee* EmployeeList::search(const std::string& n)
{
    if (head == nullptr || n.empty())
        return nullptr;

    Node* temp = head;
    do
    {
        if (temp->data->getLName() == n || temp->data->getFullName() == n || std::to_string(temp->data->getID()) == n)
            return temp->data;

        //Decide which direction to traverse doubly-linked list
        if(temp->data->getLName() < n || temp->data->getFullName() < n || std::to_string(temp->data->getID()) < n)
            temp = temp->next;
        else
            temp = temp->prev;

    } while (temp != head);

    return nullptr;
}

// Check if CSV file exists
bool EmployeeList::fileExists()
{
    namespace fs = std::filesystem;

    if (fs::exists(csv))
        return true;
    else
        return false;
}

// Create CSV file
bool EmployeeList::createFile()
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
bool EmployeeList::preLoadCheck()
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

// Load data from CSV into objects and add to list
void EmployeeList::loadData()
{
    Employee* x = nullptr;
    std::ifstream file;
    file.open(csv);

    if (file.is_open())
    {
        std::string line;
        std::getline(file, line); //skip header row

        file >> total; //ingest total employees

        while (file >> std::ws && std::getline(file, line))
        {
            std::istringstream ss(line);
            std::string f, l, e, p, a, b;
            int i, s;
            bool d;
            
            // Parse CSV line
            ss >> i;
            ss.ignore();
            std::getline(ss, f, ',');
            std::getline(ss, l, ',');
            std::getline(ss, e, ',');
            std::getline(ss, p, ',');
            std::getline(ss, a, ',');
            std::replace(a.begin(), a.end(), '|', ',');
            ss >> s;
            ss.ignore();
            ss >> d;
            ss.ignore();
            std::getline(ss, b, ',');

            //New for phase 2
            std::set<std::string> attendance;
            std::string loadAtt, att;
            std::getline(ss, loadAtt, ',');

            std::istringstream ss1(loadAtt);
            while (std::getline(ss1, att, '|'))
                attendance.insert(att);
            
            x = new Employee(i, f, l, e, p, a, s, d, b, attendance);
            addEmployee(x);
        }

        file.close();
    }
    else
    {
        std::cout << "Error: Could not open employee data file" << std::endl;
    }
}

// Save list of object data members to CSV file
void EmployeeList::saveData()
{
    std::ofstream file(csv);

    if (file.is_open())
    {
        // Header row
        file << "ID,FIRST NAME,LAST NAME,EMAIL,PHONE,ADDRESS,SALARY,DIRECT DEPOSIT,BANK ACCOUNT,ATTENDANCE\n";

        // Write data rows
        if (head != nullptr)
        {
            file << total << std::endl; //place total employees at start of file on its own line

            Node* temp = head->next;
            std::string street, city, state, zip;

            do
            {
                temp->data->getAddress(street, city, state, zip);

                //New for phase 2
                //convert set of attendance into formatted string
                std::set<std::string> a = temp->data->getAttendance();
                std::string a_str;
                for (auto i = a.begin(); i != a.end(); ++i)
                {
                    a_str += *i;
                    if (std::next(i) != a.end())
                        a_str += "|";
                }

                file << temp->data->getID() << ","
                     << temp->data->getFName() << ","
                     << temp->data->getLName() << ","
                     << temp->data->getEmail() << ","
                     << temp->data->getPhone() << ","
                     << street << "|"
                     << city << "|"
                     << state << "|"
                     << zip << ","
                     << temp->data->getSalary() << ","
                     << temp->data->getDirDeposit() << ","
                     << temp->data->getBank() << ","
                     << a_str << std::endl;

                temp = temp->next;
            } while (temp != head->next);
        }
        file.close();
    }
    else
    {
        std::cout << "Error: Could not open employee data file" << std::endl;
    }
}

void EmployeeList::printAll()
{
    if (head == nullptr)
    {
        std::cout << "List is empty." << std::endl;
        return;
    }
 
    Node* temp = head->next;
    do
    {
        std::cout << "\nName: " << temp->data->getFullName() << "\n"
                  << "Email: " << temp->data->getEmail() << "\n"
                  << "Phone: " << temp->data->getPhone() << "\n"
                  << "Address: " << temp->data->getAddress() << std::endl;

        temp = temp->next;
    } while (temp != head->next);
}

//Return total salary of employees in list
int EmployeeList::getLaborCost()
{
    int totalSalary = 0;

    if (head == nullptr)
    {
        std::cout << "List is empty." << std::endl;
        return 0;
    }

    Node* temp = head;

    do 
    {
        totalSalary += temp->data->getSalary();
        temp = temp->next;
    } while (temp != head);

    return totalSalary;
}

//Display list of addresses to mail checks to
 void EmployeeList::printMailList()
{
    if (head == nullptr)
    {
        std::cout << "List is empty." << std::endl;
        return;
    }

    Node* temp = head;

    do
    {
        if (!temp->data->getDirDeposit())
            temp->data->printMailAddr();

        temp = temp->next;

    } while (temp != head);

}
 //New for phase 2
 //Record all employee attendance for a given date
 void EmployeeList::recAttendance(std::string date)
 {
     if (head == nullptr)
     {
         std::cout << "List is empty." << std::endl;
         return;
     }

     char response = 'N';
     std::cout << "Enter attendance for " << date << " (y/N):" << std::endl;

     Node* temp = head->next;
     do
     {
         std::cout << temp->data->getFullName() << ": ";
         std::cin >> response;

         if (toupper(response) == 'Y')
             temp->data->addAttendance(date);

         temp = temp->next;
     } while (temp != head->next);
 }