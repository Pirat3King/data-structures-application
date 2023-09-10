#pragma once

// ---------------------------------------------------------------------------
// Client: Web Design Business App
// Description: Header for class ClientList - a sorted list of Client objects. 
//              Object data members are saved to and read from a CSV file as 
//              defined in the constructor.
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include <vector>
#include "Client.h"

class ClientList
{
private:
    //data members
    std::vector<Client> clients;
    std::string csv;

    //methods
    bool csvExists();
    bool createCSV();

public:
    //Constructors
    ClientList(std::string c) { csv = c; };
    ClientList() { csv = ""; };

    void addClient(Client* client);
    void removeClient(int index);

    Client* search(std::string n);

    //CSV operations
    bool preLoadCheck();
    void loadData();
    void saveData();
};
