// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Function definitions for class ProjectList - a binary search tree of Project objects. 
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "ProjectList.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


ProjectList::ProjectList(EmployeeList* e, ClientList* c, std::string d, std::string f)
{
    eList = e;
    cList = c;
    dir = d;
    csv = f;
    root = nullptr;
}

ProjectList::~ProjectList()
{
    destroyTree(root);
}

//Destructor helper
void ProjectList::destroyTree(Node* node)
{
    if (node)
    {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node->project; // deallocate the Project object
        delete node; // deallocate the Node object
    }
}

void ProjectList::insert(Project* p)
{
    insertHelper(p, root);
}

//Recursively traverse tree to find insertion point.
void ProjectList::insertHelper(Project* p, Node*& node)
{
    if (node == nullptr)
    {
        node = new Node(*p);
    }
    else if (p->getName() < node->project->getName())
    {
        insertHelper(p, node->left);
    }
    else
    {
        insertHelper(p, node->right);
    }
}

void ProjectList::remove(Project* p)
{
    removeHelper(p, root);
}

//Search tree for the given Project object and remove it based on its number of children.
void ProjectList::removeHelper(Project* p, Node*& node)
{
    //Project not found
    if (node == nullptr)
        return;
    
    //Project is found
    if (search(p->getName()) != nullptr)
    {
        // Case 1: Node has no children
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node->project;
            delete node;
            node = nullptr;
        }

        // Case 2: Node has one child
        else if (node->left == nullptr) 
        {
            Node* temp = node;
            node = node->right;
            delete temp->project;
            delete temp;
        }
        else if (node->right == nullptr) 
        {
            Node* temp = node;
            node = node->left;
            delete temp->project;
            delete temp;
        }

        // Case 3: Node has two children
        else 
        {
            Node* temp = node->right;

            //find minimum node in right subtree (logical predecessor)
            while (temp->left != nullptr)
                temp = temp->left;

            //replace node to remove with logical predecessor
            node->project = new Project(*temp->project);
            
            //remove the logical predecessor from its original position
            removeHelper(temp->project, node->right);
        }
    }
}

Project* ProjectList::search(std::string n)
{
    return searchHelper(n, root);
}

//Recursively search tree for Project with name n
Project* ProjectList::searchHelper(std::string n, Node* node)
{
    if (node == nullptr)
        return nullptr;

    else if (n == node->project->getName())
        return node->project;

    else if (n < node->project->getName())
        return searchHelper(n, node->left);

    else
        return searchHelper(n, node->right);    
}

// Check if CSV file exists
bool ProjectList::fileExists()
{
    namespace fs = std::filesystem;

    if (fs::exists(csv))
        return true;
    else
        return false;
}

// Create CSV file
bool ProjectList::createFile()
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

// LoadFromCSV helper. Check for existing CSV file - load if it exists, create if it doesn't
bool ProjectList::preLoadCheck()
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

// Load data from CSV into objects and add to list.
void ProjectList::loadData()
{
    std::ifstream file(csv);

    if (!file.is_open())
    {
        std::cout << "Error: could not open project data file" << std::endl;
        return;
    }

    //Parse file into data members and build a vector of nodes
    std::vector<Project> projects;
    loadHelper(file, projects);

    file.close();

    //Destroy any current tree that exists in memory and reubild from the vector we just created
    if (!projects.empty())
    {
        destroyTree(root);
        rebuildTreeHelper(projects, 0, (int)projects.size() - 1);
    }
}

//Updated for phase 2
//Parse CSV into data members and build vector of Projects
void ProjectList::loadHelper(std::ifstream& file, std::vector<Project>& projects)
{
    std::string line;
    std::getline(file, line); //skip header row

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string n, f, c, e;
        int b, d;

        // Parse CSV line
        std::getline(ss, n, ',');
        std::getline(ss, f, ',');
        std::getline(ss, c, ',');
        ss >> b;
        ss.ignore();
        ss >> d;
        ss.ignore();
        std::getline(ss, e, ',');

        //New for phase 2
        //Parse map of tasks
        std::map<std::string, Project::TaskStatus> tasks;
        std::string kvPair = "";
        while (std::getline(ss, kvPair, '|'))
        {
            std::stringstream ss1(kvPair);
            std::string key;
            int value;

            std::getline(ss1, key, ':');
            ss1 >> value;
            tasks[key] = static_cast<Project::TaskStatus>(value);
        }

        // Link to client and employee objects already in memory, create project file object
        Client* client = cList->search(c);
        Employee* employee = eList->search(e);
        HTMLFile* file = new HTMLFile(n, dir, f);

        projects.push_back(Project(n, file, client, b, d, employee, tasks));
    }
}

//Build tree from vector of Project objects.
void ProjectList::rebuildTreeHelper(std::vector<Project>& projects, int start, int end)
{
    if (start <= end)
    {
        int middle = (start + end) / 2;

        insert(&projects[middle]);

        rebuildTreeHelper(projects, start, middle - 1);
        rebuildTreeHelper(projects, middle + 1, end);
    }
}

// Save list of object data members to CSV file
void ProjectList::saveData()
{
    std::ofstream file(csv);
    if (!file.is_open())
    {
        std::cout << "Error: could not open project data file" << std::endl;
        return;
    }

    // Header row
    file << "PROJECT NAME,PROJECT FILE,CLIENT,BUDGET,DEADLINE,ASSIGNED EMPLOYEE,TASKS\n";

    saveHelper(root, file);
    file.close();
}

//Updated for phase 2
//Write project data to file by traversing tree recursively (post-order).
void ProjectList::saveHelper(Node* node, std::ofstream& file)
{
    if (node != nullptr)
    {
        //convert map of tasks into formatted string
        std::stringstream tasks;
        for (auto& [key, value] : node->project->getTasks())
            tasks << key << ":" << value << "|";

        file << node->project->getName() << ","
             << node->project->getFile()->getFile() << ","
             << node->project->getClient()->getBusiness() << ","
             << node->project->getBudget() << ","
             << node->project->getDeadline() << ","
             << node->project->getEmployee()->getFullName() << "," 
             << tasks.str() << std::endl;
        saveHelper(node->left, file);
        saveHelper(node->right, file);
    }
}