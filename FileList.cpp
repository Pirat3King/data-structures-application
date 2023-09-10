// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Function definitions for class FileList - an unsorted circular linked list of HTMLFile objects. 
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "FileList.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


// Constructor 
FileList::FileList(std::string d, std::string f)
{
    head = nullptr;
    size = 0;
    dir = d;
    csv = d + "/" + f;
}

// Destructor
FileList::~FileList()
{
    Node* current = head;

    if (head != nullptr)
    {
        do
        {
            Node* temp = current;
            current = current->next;
            delete temp->data;
            delete temp;
        } while (current != head);
    }
}

// Add file object to list.
void FileList::addFile(HTMLFile* newTemplate)
{
    Node* newNode = new Node(newTemplate);
    if (head == nullptr)
    {
        head = newNode;
        head->next = head;
    }
    else
    {
        Node* current = head;
        while (current->next != head)
        {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = head;
    }
    size++;
}

// Remove file object from list.
void FileList::removeFile(std::string name)
{
    Node* current = head;
    Node* previous = nullptr;
    do
    {
        if (current->data->getName() == name)
        {
            if (current == head)
            {
                Node* tail = head;
                while (tail->next != head)
                {
                    tail = tail->next;
                }
                head = head->next;
                tail->next = head;
            }
            else
            {
                previous->next = current->next;
            }
            delete current->data;
            delete current;
            size--;
            return;
        }
        previous = current;
        current = current->next;
    } while (current != head);
}

// Search list for file object by name
HTMLFile* FileList::searchFile(std::string name)
{
    Node* temp = head;
    do
    {
        if (temp->data->getName() == name)
            return temp->data;
        temp = temp->next;

    } while (temp != head);
    return nullptr;
}

// Check if CSV file exists
bool FileList::csvExists()
{
    namespace fs = std::filesystem;

    if (fs::exists(csv))
        return true;
    else
        return false;
}

// Create CSV file
bool FileList::createCSV()
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
bool FileList::preLoadCheck()
{
    if (csvExists())
    {
        loadData();
        return true;
    }
    else
    {
        createCSV();
        return false;
    }
}

// Load data from CSV into objects and add to list.
void FileList::loadData()
{
    std::ifstream file(csv);

    if (file.is_open())
    {
        std::string line;
        std::getline(file, line); //skip header row

        //Parse each line in CSV into individual data members
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string n, d, f;

            std::getline(ss, n, ',');
            std::getline(ss, d, ',');
            std::getline(ss, f, ',');

            HTMLFile* temp = new HTMLFile(n, d, f);

            addFile(temp);
        }
        file.close();
    }
    else
        std::cout << "Could not open template data file" << std::endl;
}

// Save list of object data members to CSV file
void FileList::saveData()
{
    std::ofstream file(csv);
    if (file.is_open())
    {
        // Header row
        file << "NAME,DIRECTORY,FILENAME\n";

        // Write each File object to a new line in CSV file
        if (head != nullptr)
        {
            Node* temp = head;
            do
            {
                file << temp->data->getName() << "," << temp->data->getDir() << "," << temp->data->getFile() << std::endl;
                temp = temp->next;

            } while (temp != head);
        }
        file.close();
    }
}

// Display names of files in list
void FileList::printList()
{
    Node* temp = head;

    if (temp == nullptr)
    {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    do
    {
        std::cout << "\t- " << temp->data->getName() << std::endl;
        temp = temp->next;

    } while (temp != head);
}