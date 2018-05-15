#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "IR.h"
#include "MEM.h"
#include "vm.h"
#include <stdio.h>
#include <bitset>
using namespace std;

void pass1();
void pass2();
void virtMach();


const int JMP = 1;
const int JMR = 2;
const int BNZ = 3;
const int BGT = 4;
const int BLT = 5;
const int BRZ = 6;
const int MOV = 7;
const int LDA = 8;
const int STR = 9;
const int LDR = 10;
const int STB = 11;
const int LDB = 12;
const int ADD = 13;
const int ADI = 14;
const int SUB = 15;
const int MUL = 16;
const int DIV = 17;
const int AND = 18;
const int OR = 19;
const int CMP = 20;
const int TRP = 21;
const int STR2 = 22;
const int LDR2 = 23;
const int STB2 = 24;
const int LDB2 = 25;
const int RUN = 26;
const int END = 27;
const int BLK = 28;
const int LCK = 29;
const int ULK = 30;

const int HALFSIZE = 500000;
const int MEMSIZE = 1000000;
const int TS = 1000;
