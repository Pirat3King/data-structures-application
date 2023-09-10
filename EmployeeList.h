#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Header for class EmployeeList - a doubly-linked circular list 
//              of Employee objects. Object data members are saved to and read
//              from a CSV file as defined in the constructor.
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "Employee.h"

class EmployeeList
{
private:
    struct Node
    {
        Employee* data;
        Node* next;
        Node* prev;

        //Node constructor.
        Node(const Employee& employee) : data(new Employee(employee)), next(nullptr), prev(nullptr) {}
    };

    //data members
    Node* head;
    int size; //current size in memory
    int total; //total size tracked over history (to maintain non-repeating employee id)
    std::string csv;

    //methods
    bool fileExists();
    bool createFile();

public:
    EmployeeList(std::string c);
    ~EmployeeList();

    //getters
    int getSize() { return size; }
    int getTotal() { return total; }
    Employee* getEmployee() { return head->data; }
    int getLaborCost();

    void incrTotal() { total++; }

    void addEmployee(const Employee* e);
    bool removeEmployee(const std::string& n);
    Employee* search(const std::string& n);

    //CSV operations
    bool preLoadCheck();
    void loadData();
    void saveData();
    
    void printAll();
    void printMailList();

    //New for phase 2
    void recAttendance(std::string date);
    
};
