#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
using namespace std;
class IR
{
public:
	IR();
	IR(char[], char[] ,char[]);
	int opcode;
	int opd1;
	int opd2;
};

