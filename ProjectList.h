#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Header for class ProjectList - a binary search tree of Project
//              objects. Object data members are saved to and read from a CSV 
//              file as defined in the constructor.
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "Project.h"
#include "ClientList.h"
#include "EmployeeList.h"
#include <vector>

class ProjectList
{
private:
    struct Node
    {
        Project* project;
        Node* left;
        Node* right;

        //Node constructor
        Node(Project p) : project(new Project(p)), left(nullptr), right(nullptr) {}
    };

    //data members
    Node* root;
    std::string dir, csv;
    ClientList* cList;
    EmployeeList* eList;

    //methods
    void destroyTree(Node* node);

    void insertHelper(Project* p, Node*& node);
    void removeHelper(Project* p, Node*& node);
    Project* searchHelper(std::string n, Node* node);
    
    void saveHelper(Node* node, std::ofstream& file);
    void loadHelper(std::ifstream& file, std::vector<Project>& projects);
    void rebuildTreeHelper(std::vector<Project>& projects, int left, int right);
    
    bool fileExists();
    bool createFile();

public:
    ProjectList(EmployeeList* eList, ClientList* cList, std::string d, std::string f);
    ~ProjectList();
    
    void insert(Project* p);
    void remove(Project* p);
    Project* search(std::string n);

    //CSV operations
    bool preLoadCheck();
    void loadData();
    void saveData();
};