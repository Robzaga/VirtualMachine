#pragma once
#include "IR.h"
#include "Label.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class MEM
{
public:
	MEM();
	void InsertInst(int);
	void insertByte(char);
	void insertInt(int);
	void InsertLab(Label);
	int findLab(string);
	void insertLabData(string, int);
	void setPC(int*);
	IR Fetch(int*);
	void reinsert(int, int);
	void reinsertB(int, char);
	void RegInsertI(int, int);
	void RegInsertB(int, char);
	char getByte(int);
	int getInt(int);
	Label labels[1000];
	char mem[1000003];
private:
	int labelCount;
	int * PC;
	int * iptr;
	char * cptr;
};

