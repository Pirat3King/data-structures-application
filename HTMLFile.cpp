// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: Function definitions for class HTMLFile
// Author: Pirat3King
// Date: 2023-04-07
// ---------------------------------------------------------------------------

#include "HTMLFile.h"
#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <fstream>

HTMLFile::HTMLFile(std::string n, std::string d)
{
	name = n;
	dir = d;
	file = name + ".html";
	path = dir + "/" + file;
}

HTMLFile::HTMLFile(std::string n, std::string d, std::string f)
{
	name = n;
	dir = d;
	file = f;
	path = dir + "/" + file;
}


//check if the file at 'path' exists.
bool HTMLFile::fileExists()
{
	namespace fs = std::filesystem;

	if (fs::exists(path))
		return true;
	else
		return false;
}

//create file at 'path'
bool HTMLFile::createFile()
{
	//attempt to open 'path'
	std::ofstream file(path);

	if (!file.is_open())
		return false;
	else 
	{
		file.close();
		return true;
	}
}

//open file in notepad.
void HTMLFile::editFile()
{
	if (fileExists())
	{
		std::string cmd = "notepad.exe \"" + path + "\"";
		std::system(cmd.c_str());
	}
	else
		std::cout << "File " << this->path << "does not exist." << std::endl;
}

//open file in default browser
void HTMLFile::renderFile()
{
	if (fileExists())
	{
		std::string cmd = "start " + path;
		std::system(cmd.c_str());
	}
	else
		std::cout << "File " << this->path << "does not exist." << std::endl;
}

//copy contents of current file to a new file f
bool HTMLFile::copyToNew(HTMLFile* f)
{
	if (!f->fileExists())
	{
		//Create target file
		if (!f->createFile())
		{
			std::cout << "Error creating " + f->file + "." << std::endl;
			return false;
		}

		//Open both files
		std::ifstream fin(this->path);
		std::ofstream fout(f->path);

		if (!fin.is_open())
		{
			std::cout << "Error opening " + this->file + "." << std::endl;
			return false;
		}

		if (!fout.is_open())
		{
			std::cout << "Error opening " + f->file + "." << std::endl;
			return false;
		}		

		// Copy contents of input file to output file
		std::string line;
		while (getline(fin, line))
		{
			fout << line << std::endl;
		}

		// Close file streams
		fin.close();
		fout.close();

		// Done
		std::cout << "Contents copied from " << this->file << " to " << f->file << std::endl;
		return true;
	}
	else
	{
		std::cout << "File '" + f->path + " already exists." << std::endl;
		return false;
	}
}

//Display file details
void HTMLFile::print()
{
	std::cout << "\nName: " << name
			  << "\nFile: " << file << std::endl;
}