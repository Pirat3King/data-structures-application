#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Header for class FileList - an unsorted circular linked list 
//              of HTMLFile objects. Object data members are saved to and read
//              from a CSV file as defined in the constructor.
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "HTMLFile.h"

class FileList
{
private:
    struct Node 
    {
        HTMLFile* data;
        Node* next;

        //Node constructor
        Node(HTMLFile* newData) : data(newData), next(nullptr) {}
    };

    //data members
    Node* head;
    int size;
    std::string csv, dir;

    //methods
    bool csvExists();
    bool createCSV();
    

public:
    FileList(std::string d, std::string f);
    ~FileList();

    void addFile(HTMLFile* newTemplate);
    void removeFile(std::string name);

    HTMLFile* searchFile(std::string name);
    
    //CSV operations
    bool preLoadCheck();
    void loadData();
    void saveData();
    
    //getters
    int getSize() { return size; }
    std::string getCSVFile() { return csv; }
    std::string getFileDirectory() { return dir; }

    void printList();
};
