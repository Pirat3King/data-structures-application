#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Header for HTMLFile class. Includes definitions for basic functions.
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include <string>

class HTMLFile
{
private:
	std::string name, dir, file, path;

public:
	//constructors
	HTMLFile(std::string n, std::string d);
	HTMLFile(std::string n, std::string d, std::string f);

	//getters
	std::string getName() { return name; }
	std::string getDir() { return dir; }
	std::string getFile() { return file; }
	std::string getPath() { return path; }

	//setters
	void setName(std::string n) { name = n; }
	void setDir(std::string n) { dir = n; }
	void setFile(std::string n) { file = n; }

	//additional operations
	bool fileExists();
	bool createFile();
	bool copyToNew(HTMLFile* f);

	void editFile();
	void renderFile();

	void print();
	
};

