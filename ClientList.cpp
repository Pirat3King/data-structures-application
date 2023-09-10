// ---------------------------------------------------------------------------
// Client: Web Design Business App
// Description: Function definitions for class ClientList - a sorted list of Client objects. 
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "ClientList.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


// Add client object to list while maintaining the sorted order.
void ClientList::addClient(Client* client)
{
    std::vector<Client>::iterator it = std::lower_bound(clients.begin(), clients.end(), *client,
        [](Client a, Client b) { return a.getBusiness() < b.getBusiness(); });

    clients.insert(it, *client);
}

// Remove client object from list.
void ClientList::removeClient(int index)
{
    clients.erase(clients.begin() + index);
}

// Search list for client object by business name
Client* ClientList::search(std::string n)
{
    for (auto& client : clients)
    {
        if (client.getBusiness() == n)
            return &client;
    }
    return nullptr;
}

// Check if CSV file exists
bool ClientList::csvExists()
{
    namespace fs = std::filesystem;

    if (fs::exists(csv))
        return true;
    else
        return false;
}

// Create CSV file
bool ClientList::createCSV()
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
bool ClientList::preLoadCheck()
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
void ClientList::loadData()
{
    std::ifstream file(csv);

    if (file.is_open()) 
    {
        std::string line;
        std::getline(file, line); //skip header row

        //Parse each line in CSV into individual data members and add object to list.
        while (std::getline(file, line)) 
        {
            std::stringstream ss(line);
            std::string business, contact, email, phone;
            std::getline(ss, business, ',');
            std::getline(ss, contact, ',');
            std::getline(ss, email, ',');
            std::getline(ss, phone, ',');

            Client* client = new Client(business, contact, email, phone);

            clients.push_back(*client);
        }
        file.close();
    }
    else
        std::cout << "Could not open client data file" << std::endl;
}

// Save list of object data members to CSV file
void ClientList::saveData()
{
    std::ofstream file(csv);
    if (file.is_open())
    {
        // Header row
        file << "BUSINESS NAME,CONTACT NAME,EMAIL,PHONE\n";

        // Write each Client object to a new line in csv file
        for (auto& client : clients)
        {
            file << client.getBusiness() << "," << client.getContact() << "," << client.getEmail() << "," << client.getPhone() << "\n";
        }
        file.close();
    }
}