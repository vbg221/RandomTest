// Testing1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "rapidxml.hpp"
#include "fstream"
#include "vector"


using namespace std;

string getFileContent(const std::string& path)
{
	std::ifstream file(path);
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return content;
}

int update(const std::string& filename, int row, int col) {

	cout << "Execution started..." << endl;

	std::string input_xml = getFileContent(filename);
	std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
	int len = input_xml.length();
	xml_copy.push_back('\0');

	char *c = &input_xml[0];

	rapidxml::xml_document<> doc;

	cout << "About to start parsing..." << endl;

	doc.parse <rapidxml::parse_non_destructive | rapidxml::parse_no_data_nodes>(&xml_copy[0]);

	for (int i = 0; i < xml_copy.size(); i++)
	{
		cout << xml_copy.at(i);
	}
	
	rapidxml::xml_node<>* root_node = doc.first_node("Image");

	cout << "Converting string to character pointer" << endl;

	std::string rws = std::to_string(row);
	const char * text = doc.allocate_string(rws.c_str(), rws.length());
	std::string cls = std::to_string(col);
	const char * text2 = doc.allocate_string(cls.c_str(), cls.length());

	cout << "Assigning the new values to the nodes..." << endl;

	root_node->first_node("row")->value(rws.c_str());
	root_node->first_node("col")->value(cls.c_str());

	//
	//std::string data;
	//rapidxml::print(std::back_inserter(data), doc);
	//
	
	for (int i = 0; i < xml_copy.size(); i++)
	{
		cout << xml_copy.at(i);
	}

	cout << "Saving changes..." << endl;

	std::string data = std::string(xml_copy.begin(), xml_copy.end());
	std::ofstream file;
	file.open(filename.c_str());
	file << data;
	file.close(); 

	cout << "Done" << endl;
	
	return 0;
}



int main()
{
	cout << "Starting executiong" << endl;
	return update("file.xml",3,9);
}

