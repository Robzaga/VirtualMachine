#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
class Label
{
public:
	Label();
	Label(string);
	string Name;
	int location;
	void insertLoc(int);
};

