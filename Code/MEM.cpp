#include "MEM.h"



MEM::MEM()
{
	labelCount = 0;
	PC = 0;
}

void MEM::insertInt(int i)
{
	mem[*PC + 3] = i >> 24;
	mem[*PC + 2] = i >> 16;
	mem[*PC + 1] = i >> 8;
	mem[*PC] = i;
}

void MEM::insertByte(char c)
{
	mem[*PC] = c;
}

void MEM::InsertInst(int i)
{
	mem[*PC] = i;
}
void MEM::RegInsertI(int i, int j)
{
	mem[i + 3] = j >> 24;
	mem[i + 2] = j >> 16;
	mem[i + 1] = j >> 8;
	mem[i] = j;
}
void MEM::RegInsertB(int i, char j)
{
	mem[i] = j;
}
char MEM::getByte(int i)
{
	return mem[i];
}
int MEM::getInt(int i)
{
	iptr = (int*)(mem + i);
	return *iptr;
}
void MEM::setPC(int * i)
{
	PC = i;
}
int MEM::findLab(string label)
{
	for (int i = 0; i < sizeof(labels); i++)
	{
		if (labels[i].Name == label)
		{
			return i;
		}
	}
	return -1;
}

void MEM::InsertLab(Label label)
{
	labels[labelCount++] = label;	
}
void MEM::insertLabData(string name, int i )
{
	int temp = findLab(name);
	labels[temp].insertLoc(i);
}

IR MEM::Fetch(int * i)
{
	char g[4];
	g[0] = mem[*i];
	char j[4];
	j[0] = mem[*i + 4];
	char k[4];
	k[0] = mem[*i + 8];
	IR ret = IR(g,j,k);
	return ret;
}

void MEM::reinsert(int i, int k)
{
	mem[i + 3] = k >> 24;
	mem[i + 2] = k >> 16;
	mem[i + 1] = k >> 8;
	mem[i] = k;
}

void MEM::reinsertB(int i, char k)
{
	mem[i] = k;
}

