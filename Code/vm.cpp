#include "vm.h"

fstream getFile;
string temp;
char str[20];
bool Running = false;
char * token;
char * secToken;
string label;
string label1;
string label2;
string label3;
string fileName;
bool isLabel = false;
IR ir = IR();
MEM mem = MEM();
Label templab;
int labelcount = 0;
int reg[13] = { 0,0,0,0,0,0,0,0,0,MEMSIZE - 52,MEMSIZE - 52,MEMSIZE - 52,MEMSIZE -1000 };
int * PC = &reg[8];
int * SP = &reg[9];
int * FP = &reg[10];
int * SB = &reg[11];
int * SL = &reg[12];
int line = 0;
int userInt = 0;
int userInt2 = 0;
int userInt3 = 0;
int flag = -1;
char userchar;
int Tarr[5] = { 0 };
int arrL = -1;
int currentThread = 0;
int * iptr;

int main(int argc, char* argv[])
{
	fileName = argv[1];
	pass1();
	fileName = argv[1];
	pass2();
	virtMach();
	return 0;
}
void pass1()
{
	getFile.open(fileName);
	if (getFile.is_open())
	{
		line = 0;
		*PC = 0;
		while (getline(getFile, temp))
		{
			line++;
			strcpy(str, temp.c_str());
			token = strtok(str, " ");
			while (token != NULL)
			{
				if (line >= 29)
					line = line;
				if (token != NULL)
					if (token == ";")
						token = NULL;
				if (token != NULL)
				{
					label = token;
					if (label == "TRP" || label == ".INT" || label == ".BYT" || label == ".ALN" || label == "JMP" || label == "JMR" || label == "LCK" || label == "ULK" || label == "BLK" || label == "END")
					{
						if (label == "TRP")
						{
							token = strtok(NULL, " ");
							temp = token;
							userInt = stoi(temp);
							if (!(userInt == 0 || userInt == 1 || userInt == 2 || userInt == 3 || userInt == 4))
							{
								cout << line << " has errors" << endl;
							}
							*PC = *PC + 12;
						}
						else if (label == ".INT")
						{
							token = strtok(NULL, " ");
							userInt = 0;
							label1 = token;
							userInt = stoi(label1);
							*PC = *PC + 4;
						}
						else if (label == ".BYT")
						{
							token = strtok(NULL, " ");
							label1 = token;
							*PC = *PC + 1;
						}
					}
					else if (label == "R0" || label == "R1" || label == "R2" || label == "R3" || label == "R4" || label == "R5" || label == "R6" || label == "R7" || label == "PC"
						|| label == "SP" || label == "FP" || label == "SB" || label == "SL")
					{
						cout << "Can't continue, Incorrect label used" << endl;
					}
					else
					{
						if (!(label == "JMP" || label == "JMR" || label == "BNZ" || label == "BGT" || label == "BLT" || label == "BRZ" || label == "MOV" || label == "LDA"
							|| label == "STR" || label == "LDR" || label == "STB" || label == "LDB" || label == "ADD" || label == "ADI" || label == "SUB" || label == "MUL"
							|| label == "DIV" || label == "AND" || label == "OR" || label == "CMP" || label == "TRP" || label == ".INT" || label == ".BYT" || label == ".ALN"
							|| label == "RUN" || label == "END" || label == "BLK" || label == "LCK" || label == "ULK"))
						{
							Label LabelObj = Label(label);
							mem.InsertLab(LabelObj);
							token = strtok(NULL, " ");
							label1 = token;
						}
						else if (label == "JMP" || label == "JMR" || label == "BNZ" || label == "BGT" || label == "BLT" || label == "BRZ" || label == "MOV" || label == "LDA"
							|| label == "STR" || label == "LDR" || label == "STB" || label == "LDB" || label == "ADD" || label == "ADI" || label == "SUB" || label == "MUL"
							|| label == "DIV" || label == "AND" || label == "OR" || label == "CMP" || label == "RUN" || label == "END" || label == "BLK" || label == "LCK" || label == "ULK")
						{
							label1 = label;
						}
						if (label1 == "TRP" || label1 == ".INT" || label1 == ".BYT" || label1 == ".ALN" || label1 == "JMP" || label1 == "LCK" || label1 == "ULK" || label1 == "END")
						{
							if (label1 == "TRP")
							{
								token = strtok(NULL, " ");
								string templabel1 = token;
								userInt = stoi(templabel1);
								if (!(userInt == 0 || userInt == 1 || userInt == 2 || userInt == 3 || userInt == 4))
								{
									cout << line << " has errors" << endl;
								}
								*PC = *PC + 12;
							}
							else if (label1 == ".INT")
							{
								token = strtok(NULL, " ");
								userInt = 0;
								label1 = token;
								userInt = stoi(label1);
								*PC = *PC + 4;
							}
							else if (label1 == ".BYT")
							{
								token = strtok(NULL, " ");
								label1 = token;
								*PC = *PC + 1;
							}
						}
						else
						{
							token = strtok(NULL, " ");
							label2 = token;
							strcpy(str, label2.c_str());
							secToken = strtok(str, ",");
							label2 = secToken;
							secToken = strtok(NULL, ",");
							label3 = secToken;

							if (label1 == "BNZ" || label1 == "BGT" || label1 == "BLT" || label1 == "BRZ" || label1 == "MOV" || label1 == "LDA"
								|| label1 == "STR" || label1 == "LDR" || label1 == "STB" || label1 == "LDB" || label1 == "ADD" || label1 == "ADI" || label1 == "SUB" || label1 == "MUL"
								|| label1 == "DIV" || label1 == "AND" || label1 == "OR" || label1 == "CMP" || label1 == "RUN")
							{
								if (!(label2 == "R0" || label2 == "R1" || label2 == "R2" || label2 == "R3" || label2 == "R4" || label2 == "R5" || label2 == "R6" || label2 == "R7" || label2 == "SP" || label2 == "SB" || label2 == "FP" || label2 == "SL" || label2 == "PC"))
								{
									cout << "Error on line" << line << endl;
								}
								if (label2 == "JMP" || label2 == "JMR" || label2 == "BNZ" || label2 == "BGT" || label2 == "BLT" || label2 == "BRZ" || label2 == "LDA"
									|| label2 == "STR" || label2 == "LDR" || label2 == "STB" || label2 == "LDB")
								{
									cout << "error on line " << line << endl;
								}
								else if (label1 == "MOV" || label1 == "ADD" || label1 == "SUB" || label1 == "CMP" || label1 == "OR" || label1 == "AND" || label1 == "DIV" || label1 == "MUL")
								{
									if (!(label2 == "R0" || label2 == "R1" || label2 == "R2" || label2 == "R3" || label2 == "R4" || label2 == "R5" || label2 == "R6" || label2 == "R7" || label2 == "SP" || label2 == "SB" || label2 == "FP" || label2 == "SL" || label2 == "PC"))
									{
										cout << "Error on line" << line << endl;
									}
									if (!(label3 == "R0" || label3 == "R1" || label3 == "R2" || label3 == "R3" || label3 == "R4" || label3 == "R5" || label3 == "R6" || label3 == "R7" || label3 == "SP" || label3 == "SB" || label3 == "FP" || label3 == "SL" || label3 == "PC"))
									{
										cout << "Error on line" << line << endl;
									}
								}
								else if (label1 == "ADI")
								{
									if (!(label2 == "R0" || label2 == "R1" || label2 == "R2" || label2 == "R3" || label2 == "R4" || label2 == "R5" || label2 == "R6" || label2 == "R7" || label2 == "SP" || label2 == "SB" || label2 == "FP" || label2 == "SL" || label2 == "PC"))
									{
										cout << "Error on line" << line << endl;
									}
									if ((label3 == "R0" || label3 == "R1" || label3 == "R2" || label3 == "R3" || label3 == "R4" || label3 == "R5" || label3 == "R6" || label3 == "R7" || label3 == "SP" || label3 == "SB" || label3 == "FP" || label3 == "SL" || label3 == "PC"))
									{
										cout << "Error on line" << line << endl;
									}
								}
							}
							else if (label1 == "JMR" )
							{
								if (!(label2 == "R0" || label2 == "R1" || label2 == "R2" || label2 == "R3" || label2 == "R4" || label2 == "R5" || label2 == "R6" || label2 == "R7" || label2 == "SP" || label2 == "SB" || label2 == "FP" || label2 == "SL" || label2 == "PC"))
								{
									cout << "Error on line" << line << endl;
								}
							}
							*PC = *PC + 12;
						}
					}
					token = NULL;
					secToken = NULL;
				}
			}
		}
		getFile.close();

	}
	else
	{
		cout << "Unable to open file";
		system("PAUSE");
	}
}

void pass2()
{
	getFile.open(fileName);
	if (getFile.is_open())
	{
		line = 0;
		*PC = 0;
		mem.setPC(PC);
		while (getline(getFile, temp))
		{
			line++;
			strcpy(str, temp.c_str());
			token = strtok(str, " ");
			while (token != NULL)
			{
				if (token != NULL)
					if (token == ";")
						token = NULL;
				if (token != NULL)
				{
					label = token;
					if (label == "TRP" || label == ".INT" || label == ".BYT" || label == ".ALN" || label == "JMP" || label == "JMR"
						|| label == "END" || label == "BLK" || label == "LCK" || label == "ULK")
					{
						if (label == "TRP")
						{
							if (flag < 0)
								flag = *PC;
							mem.InsertInst(TRP);
							*PC = *PC + 4;
							token = strtok(NULL, " ");
							label1 = token;
							userInt = stoi(label1);
							if (!(userInt == 0 || userInt == 1 || userInt == 2 || userInt == 3 || userInt == 4))
							{
								cout << line << " has errors" << endl;
							}
							mem.InsertInst(userInt);
							*PC = *PC + 8;
						}
						else if (label == ".INT")
						{
							token = strtok(NULL, " ");
							label1 = token;
							userInt = stoi(label1);
							mem.insertInt(userInt);
							*PC = *PC + 4;
						}
						else if (label == ".BYT")
						{
							token = strtok(NULL, " ");
							label1 = token;
							strcpy(str, label1.c_str());
							if (str[1] == '\\' && str[2] == 'n')
							{
								str[0] = '\n';
							}
							else
							{
								str[0] = str[1];
							}

							mem.insertByte(str[0]);
							*PC = *PC + 1;
						}
						else if (label == "JMP")
						{
							if (flag < 0)
								flag = *PC;
							mem.InsertInst(JMP);
							*PC = *PC + 4;
							token = strtok(NULL, " ");
							label1 = token;
							mem.InsertInst(mem.findLab(label1));
							*PC = *PC + 8;
						}
						else if (label == "JMR")
						{
							if (flag < 0)
								flag = *PC;
							mem.InsertInst(JMR);
							*PC = *PC + 4;
							token = strtok(NULL, " ");
							label1 = token;
							if (label1 == "R0")
								mem.InsertInst(0);
							else if (label1 == "R1")
								mem.InsertInst(1);
							else if (label1 == "R2")
								mem.InsertInst(2);
							else if (label1 == "R3")
								mem.InsertInst(3);
							else if (label1 == "R4")
								mem.InsertInst(4);
							else if (label1 == "R5")
								mem.InsertInst(5);
							else if (label1 == "R6")
								mem.InsertInst(6);
							else if (label1 == "R7")
								mem.InsertInst(7);
							else if (label1 == "PC")
								mem.InsertInst(8);
							else if (label1 == "SP")
								mem.InsertInst(9);
							else if (label1 == "FP")
								mem.InsertInst(10);
							else if (label1 == "SB")
								mem.InsertInst(11);
							else if (label1 == "SL")
								mem.InsertInst(12);
							else
								cout << "Wrong! Line" << line << endl;
							*PC = *PC + 8;
						}
						else if (label == "END")
						{
							if (flag < 0)
								flag = *PC;
							mem.InsertInst(END);
							*PC = *PC + 12;
						}
						else if (label == "BLK")
						{
							if (flag < 0)
								flag = *PC;
							mem.InsertInst(BLK);
							*PC = *PC + 12;
						}
						else if (label == "LCK")
						{
							if (flag < 0)
								flag = *PC;
							mem.InsertInst(LCK);
							*PC = *PC + 4;
							token = strtok(NULL, " ");
							label1 = token;
							mem.InsertInst(mem.findLab(label1));
							*PC = *PC + 8;
						}
						else if (label == "ULK")
						{
							if (flag < 0)
								flag = *PC;
							mem.InsertInst(ULK);
							*PC = *PC + 4;
							token = strtok(NULL, " ");
							label1 = token;
							mem.InsertInst(mem.findLab(label1));
							*PC = *PC + 8;
						}
					}
					else if (label == "R0" || label == "R1" || label == "R2" || label == "R3" || label == "R4" || label == "R5" || label == "R6" || label == "R7" || label == "PC")
					{
						cout << "Can't continue, Incorrect label used" << endl;
					}
					else
					{
						if (!(label == "BNZ" || label == "BGT" || label == "BLT" || label == "BRZ" || label == "MOV" || label == "LDA"
							|| label == "STR" || label == "LDR" || label == "STB" || label == "LDB" || label == "ADD" || label == "ADI" || label == "SUB" || label == "MUL"
							|| label == "DIV" || label == "AND" || label == "OR" || label == "CMP" || label == "TRP" || label == ".INT" || label == ".BYT" || label == ".ALN"
							|| label == "RUN"))
						{
							mem.insertLabData(label, *PC);
							token = strtok(NULL, " ");
							label1 = token;
						}
						else if (label == "JMP" || label == "JMR" || label == "BNZ" || label == "BGT" || label == "BLT" || label == "BRZ" || label == "MOV" || label == "LDA"
							|| label == "STR" || label == "LDR" || label == "STB" || label == "LDB" || label == "ADD" || label == "ADI" || label == "SUB" || label == "MUL"
							|| label == "DIV" || label == "AND" || label == "OR" || label == "CMP" || label == "RUN")
						{
							label1 = label;
						}
						if (label1 == "TRP" || label1 == ".INT" || label1 == ".BYT" || label1 == ".ALN" || label1 == "JMP" || label1 == "JMR" || label1 == "LCK" || label1 == "ULK" || label1 == "END")
						{
							if (label1 == "TRP")
							{
								if (flag < 0)
									flag = *PC;
								mem.InsertInst(TRP);
								*PC = *PC + 4;
								token = strtok(NULL, " ");
								label2 = token;
								userInt = stoi(label2);
								if (!(userInt == 0 || userInt == 1 || userInt == 2 || userInt == 3 || userInt == 4))
								{
									cout << line << " has errors" << endl;
								}
								mem.InsertInst(userInt);
								*PC = *PC + 8;
							}
							else if (label1 == ".INT")
							{
								token = strtok(NULL, " ");
								label2 = token;
								userInt = stoi(label2);
								mem.insertInt(userInt);
								*PC = *PC + 4;
							}
							else if (label1 == ".BYT")
							{
								token = strtok(NULL, " ");
								label2 = token;
								strcpy(str, label2.c_str());
								if (str[1] == '\\' && str[2] == 'n')
								{
									str[0] = '\n';
								}
								else
								{
									str[0] = str[1];
								}

								mem.insertByte(str[0]);
								*PC = *PC + 1;
							}
							else if (label1 == "JMP")
							{
								if (flag < 0)
									flag = *PC;
								mem.InsertInst(JMP);
								*PC = *PC + 4;
								token = strtok(NULL, " ");
								label2 = token;
								mem.InsertInst(mem.findLab(label2));
								*PC = *PC + 8;
							}
							else if (label1 == "JMR")
							{
								if (flag < 0)
									flag = *PC;
								mem.InsertInst(JMR);
								*PC = *PC + 4;
								token = strtok(NULL, " ");
								label2 = token;
								if (label2 == "R0")
									mem.InsertInst(0);
								else if (label2 == "R1")
									mem.InsertInst(1);
								else if (label2 == "R1")
									mem.InsertInst(2);
								else if (label2 == "R1")
									mem.InsertInst(3);
								else if (label2 == "R1")
									mem.InsertInst(4);
								else if (label2 == "R1")
									mem.InsertInst(5);
								else if (label2 == "R1")
									mem.InsertInst(6);
								else if (label2 == "R1")
									mem.InsertInst(7);
								else
									cout << "Wrong! Line" << line << endl;
								*PC = *PC + 8;
							}
							else if (label1 == "END")
							{
								if (flag < 0)
									flag = *PC;
								mem.InsertInst(END);
								*PC = *PC + 12;
							}
							else if (label1 == "BLK")
							{
								if (flag < 0)
									flag = *PC;
								mem.InsertInst(BLK);
								*PC = *PC + 12;
							}
							else if (label1 == "LCK")
							{
								if (flag < 0)
									flag = *PC;
								mem.InsertInst(LCK);
								*PC = *PC + 4;
								token = strtok(NULL, " ");
								label2 = token;
								mem.InsertInst(mem.findLab(label2));
								*PC = *PC + 8;
							}
							else if (label1 == "ULK")
							{
								if (flag < 0)
									flag = *PC;
								mem.InsertInst(ULK);
								*PC = *PC + 4;
								token = strtok(NULL, " ");
								label2 = token;
								mem.InsertInst(mem.findLab(label2));
								*PC = *PC + 8;
							}
						}
						else
						{
							token = strtok(NULL, " ");
							label2 = token;
							strcpy(str, label2.c_str());
							secToken = strtok(str, ",");
							label2 = secToken;
							secToken = strtok(NULL, ",");
							label3 = secToken;

							if (label1 == "BNZ" || label1 == "BGT" || label1 == "BLT" || label1 == "BRZ" || label1 == "MOV" || label1 == "LDA"
								|| label1 == "STR" || label1 == "LDR" || label1 == "STB" || label1 == "LDB" || label1 == "ADD" || label1 == "ADI" || label1 == "SUB" || label1 == "MUL"
								|| label1 == "DIV" || label1 == "AND" || label1 == "OR" || label1 == "CMP" || label1 == "RUN")
							{
								if (flag < 0)
									flag = *PC;
								if (label1 == "BNZ")
								{
									mem.InsertInst(BNZ);
									*PC = *PC + 4;
								}
								else if (label1 == "BGT")
								{
									mem.InsertInst(BGT);
									*PC = *PC + 4;
								}
								else if (label1 == "BLT")
								{
									mem.InsertInst(BLT);
									*PC = *PC + 4;
								}
								else if (label1 == "BRZ")
								{
									mem.InsertInst(BRZ);
									*PC = *PC + 4;
								}
								else if (label1 == "MOV")
								{
									mem.InsertInst(MOV);
									*PC = *PC + 4;
								}
								else if (label1 == "LDA")
								{
									mem.InsertInst(LDA);
									*PC = *PC + 4;
								}
								else if (label1 == "STR")
								{
									if (label3 == "R0" || label3 == "R1" || label3 == "R2" || label3 == "R3" || label3 == "R4" || label3 == "R5" || label3 == "R6" || label3 == "R7" || label3 == "SP" || label3 == "SB" || label3 == "FP" || label3 == "SL" || label3 == "PC")
									{
										mem.InsertInst(STR2);
									}
									else
									{
										mem.InsertInst(STR);
									}
									*PC = *PC + 4;
								}
								else if (label1 == "LDR")
								{
									if (label3 == "R0" || label3 == "R1" || label3 == "R2" || label3 == "R3" || label3 == "R4" || label3 == "R5" || label3 == "R6" || label3 == "R7" || label3 == "PC" || label3 == "FP" || label3 == "SP" || label3 == "SB" || label3 == "SL")
									{
										mem.InsertInst(LDR2);
									}
									else
									{
										mem.InsertInst(LDR);
									}
									*PC = *PC + 4;

								}
								else if (label1 == "STB")
								{
									if (label3 == "R0" || label3 == "R1" || label3 == "R2" || label3 == "R3" || label3 == "R4" || label3 == "R5" || label3 == "R6" || label3 == "R7" || label3 == "PC" || label3 == "FP" || label3 == "SP" || label3 == "SB" || label3 == "SL")
									{
										mem.InsertInst(STB2);
									}
									else
									{
										mem.InsertInst(STB);
									}
									*PC = *PC + 4;
								}
								else if (label1 == "LDB")
								{
									if (label3 == "R0" || label3 == "R1" || label3 == "R2" || label3 == "R3" || label3 == "R4" || label3 == "R5" || label3 == "R6" || label3 == "R7" || label3 == "PC" || label3 == "FP" || label3 == "SP" || label3 == "SB" || label3 == "SL")
									{
										mem.InsertInst(LDB2);
									}
									else
									{
										mem.InsertInst(LDB);
									}
									*PC = *PC + 4;
								}
								else if (label1 == "ADD")
								{
									mem.InsertInst(ADD);
									*PC = *PC + 4;
								}
								else if (label1 == "ADI")
								{
									mem.InsertInst(ADI);
									*PC = *PC + 4;
								}
								else if (label1 == "SUB")
								{
									mem.InsertInst(SUB);
									*PC = *PC + 4;
								}
								else if (label1 == "MUL")
								{
									mem.InsertInst(MUL);
									*PC = *PC + 4;
								}
								else if (label1 == "DIV")
								{
									mem.InsertInst(DIV);
									*PC = *PC + 4;
								}
								else if (label1 == "AND")
								{
									mem.InsertInst(AND);
									*PC = *PC + 4;
								}
								else if (label1 == "OR")
								{
									mem.InsertInst(OR);
									*PC = *PC + 4;
								}
								else if (label1 == "CMP")
								{
									mem.InsertInst(CMP);
									*PC = *PC + 4;
								}
								else if (label1 == "RUN")
								{
									mem.InsertInst(RUN);
									*PC = *PC + 4;
								}
								if (label1 == "JMR" || label1 == "BNZ" || label1 == "BGT" || label1 == "BLT" || label1 == "BRZ" || label1 == "MOV" || label1 == "LDA"
									|| label1 == "STR" || label1 == "LDR" || label1 == "STB" || label1 == "LDB" || label1 == "ADD" || label1 == "ADI" || label1 == "SUB" || label1 == "MUL"
									|| label1 == "DIV" || label1 == "AND" || label1 == "OR" || label1 == "CMP" || label1 == "RUN")
								{
									if (label2 == "R0")
									{
										mem.InsertInst(0);
										*PC = *PC + 4;
									}
									else if (label2 == "R1")
									{
										mem.InsertInst(1);
										*PC = *PC + 4;
									}
									else if (label2 == "R2")
									{
										mem.InsertInst(2);
										*PC = *PC + 4;
									}
									else if (label2 == "R3")
									{
										mem.InsertInst(3);
										*PC = *PC + 4;
									}
									else if (label2 == "R4")
									{
										mem.InsertInst(4);
										*PC = *PC + 4;
									}
									else if (label2 == "R5")
									{
										mem.InsertInst(5);
										*PC = *PC + 4;
									}
									else if (label2 == "R6")
									{
										mem.InsertInst(6);
										*PC = *PC + 4;
									}
									else if (label2 == "R7")
									{
										mem.InsertInst(7);
										*PC = *PC + 4;
									}
									else if (label2 == "PC")
									{
										mem.InsertInst(8);
										*PC = *PC + 4;
									}
									else if (label2 == "SP")
									{
										mem.InsertInst(9);
										*PC = *PC + 4;
									}
									else if (label2 == "FP")
									{
										mem.InsertInst(10);
										*PC = *PC + 4;
									}
									else if (label2 == "SB")
									{
										mem.InsertInst(11);
										*PC = *PC + 4;
									}
									else if (label2 == "SL")
									{
										mem.InsertInst(12);
										*PC = *PC + 4;
									}
									if (label1 == "BNZ" || label1 == "BGT" || label1 == "BLT" || label1 == "BRZ" || label1 == "LDA")
									{
										if (label3 == "R0" || label3 == "R1" || label3 == "R3" || label3 == "R4" || label3 == "R5" || label3 == "R6" || label3 == "R7" || label3 == "PC" || label3 == "SP" || label3 == "FP" || label3 == "SB" || label3 == "SL")
										{

										}
										else
										{
											userInt = mem.findLab(label3);
											mem.InsertInst(userInt);
										}
										*PC = *PC + 4;
									}
									else if (label1 == "LDR" || label1 == "LDB" || label1 == "STR" || label1 == "STB" || label1 == "RUN")
									{
										if (label3 == "R0" || label3 == "R1" || label3 == "R2" || label3 == "R3" || label3 == "R4" || label3 == "R5" || label3 == "R6" || label3 == "R7" || label3 == "PC" || label3 == "FP" || label3 == "SP" || label3 == "SB" || label3 == "SL")
										{
											if (label3 == "R0")
											{
												mem.InsertInst(0);
												*PC = *PC + 4;
											}
											else if (label3 == "R1")
											{
												mem.InsertInst(1);
												*PC = *PC + 4;
											}
											else if (label3 == "R2")
											{
												mem.InsertInst(2);
												*PC = *PC + 4;
											}
											else if (label3 == "R3")
											{
												mem.InsertInst(3);
												*PC = *PC + 4;
											}
											else if (label3 == "R4")
											{
												mem.InsertInst(4);
												*PC = *PC + 4;
											}
											else if (label3 == "R5")
											{
												mem.InsertInst(5);
												*PC = *PC + 4;
											}
											else if (label3 == "R6")
											{
												mem.InsertInst(6);
												*PC = *PC + 4;
											}
											else if (label3 == "R7")
											{
												mem.InsertInst(7);
												*PC = *PC + 4;
											}
											else if (label3 == "PC")
											{
												mem.InsertInst(8);
												*PC = *PC + 4;
											}
											else if (label3 == "SP")
											{
												mem.InsertInst(9);
												*PC = *PC + 4;
											}
											else if (label3 == "FP")
											{
												mem.InsertInst(10);
												*PC = *PC + 4;
											}
											else if (label3 == "SB")
											{
												mem.InsertInst(11);
												*PC = *PC + 4;
											}
											else if (label3 == "SL")
											{
												mem.InsertInst(12);
												*PC = *PC + 4;
											}
										}
										else
										{
											userInt = mem.findLab(label3);
											mem.InsertInst(userInt);
											*PC = *PC + 4;
										}
									}
									else if (label1 == "MOV" || label1 == "ADD" || label1 == "SUB" || label1 == "MUL"
										|| label1 == "DIV" || label1 == "AND" || label1 == "OR" || label1 == "CMP")
									{
										if (label3 == "R0")
										{
											mem.InsertInst(0);
											*PC = *PC + 4;
										}
										else if (label3 == "R1")
										{
											mem.InsertInst(1);
											*PC = *PC + 4;
										}
										else if (label3 == "R2")
										{
											mem.InsertInst(2);
											*PC = *PC + 4;
										}
										else if (label3 == "R3")
										{
											mem.InsertInst(3);
											*PC = *PC + 4;
										}
										else if (label3 == "R4")
										{
											mem.InsertInst(4);
											*PC = *PC + 4;
										}
										else if (label3 == "R5")
										{
											mem.InsertInst(5);
											*PC = *PC + 4;
										}
										else if (label3 == "R6")
										{
											mem.InsertInst(6);
											*PC = *PC + 4;
										}
										else if (label3 == "R7")
										{
											mem.InsertInst(7);
											*PC = *PC + 4;
										}
										else if (label3 == "PC")
										{
											mem.InsertInst(8);
											*PC = *PC + 4;
										}
										else if (label3 == "SP")
										{
											mem.InsertInst(9);
											*PC = *PC + 4;
										}
										else if (label3 == "FP")
										{
											mem.InsertInst(10);
											*PC = *PC + 4;
										}
										else if (label3 == "SB")
										{
											mem.InsertInst(11);
											*PC = *PC + 4;
										}
										else if (label3 == "SL")
										{
											mem.InsertInst(12);
											*PC = *PC + 4;
										}
									}
									else if (label1 == "ADI")
									{
										userInt = stoi(label3);
										mem.InsertInst(userInt);
										*PC = *PC + 4;
									}
								}
								else
									token = NULL;
							}
						}
					}
				}
				else
					cout << "wrong line" << line << endl;
				token = NULL;
				secToken = NULL;
			}
		}
		getFile.close();
	}
	else
	{
		cout << "Unable to open file";
		system("PAUSE");
	}
}

void virtMach()
{
	*PC = flag;
	line = *PC;
	Tarr[0] = 1;
	Tarr[1] = -1;
	Tarr[2] = -1;
	Tarr[3] = -1;
	Tarr[4] = -1;
	Running = true;
	string userstring;
	char userchar2[20];
	while (Running)
	{
		line++;
		ir = mem.Fetch(PC);
		switch (ir.opcode)
		{
		case JMP:
			*PC = mem.labels[ir.opd1].location;
			break;
		case JMR:
			*PC = reg[ir.opd1];
			break;
		case BNZ:
			if (reg[ir.opd1] != 0)
			{
				*PC = (int)(mem.labels[ir.opd2].location);
			}
			else
				*PC = *PC + 12;
			break;
		case BGT:
			if ((reg[ir.opd1] > 0))
			{
				*PC = (int)(mem.labels[ir.opd2].location);
			}
			else
				*PC = *PC + 12;
			break;
		case BLT:
			if (reg[ir.opd1] < 0)
			{
				*PC = (int)(mem.labels[ir.opd2].location);
			}
			else
				*PC = *PC + 12;
			break;
		case BRZ:
			if (reg[ir.opd1] == 0)
			{
				*PC = (int)(mem.labels[ir.opd2].location);
			}
			else
				*PC = *PC + 12;
			break;
		case MOV:
			reg[ir.opd1] = reg[ir.opd2];
			*PC = *PC + 12;
			break;
		case LDA:
			reg[ir.opd1] = (mem.labels[ir.opd2].location);
			*PC = *PC + 12;
			break;
		case STR:
			mem.reinsert(mem.labels[ir.opd2].location, reg[ir.opd1]);
			*PC = *PC + 12;
			break;
		case LDR:
			userInt = mem.labels[ir.opd2].location;
			userchar2[0] = mem.mem[userInt];
			userchar2[1] = mem.mem[userInt + 1];
			userchar2[2] = mem.mem[userInt + 2];
			userchar2[3] = mem.mem[userInt + 3];
			reg[ir.opd1] = *(int*)userchar2;
			*PC = *PC + 12;
			break;
		case STB:
			mem.reinsertB(mem.labels[ir.opd2].location, reg[ir.opd1]);
			*PC = *PC + 12;
			break;
		case LDB:
			reg[ir.opd1] = mem.mem[mem.labels[ir.opd2].location];
			*PC = *PC + 12;
			break;
		case ADD:
			reg[ir.opd1] = reg[ir.opd1] + reg[ir.opd2];
			*PC = *PC + 12;
			break;
		case ADI:
			reg[ir.opd1] = reg[ir.opd1] + ir.opd2;
			*PC = *PC + 12;
			break;
		case SUB:
			reg[ir.opd1] = reg[ir.opd1] - reg[ir.opd2];
			*PC = *PC + 12;
			break;
		case MUL:
			reg[ir.opd1] = reg[ir.opd1] * reg[ir.opd2];
			*PC = *PC + 12;
			break;
		case DIV:
			reg[ir.opd1] = reg[ir.opd1] / reg[ir.opd2];
			*PC = *PC + 12;
			break;
		case AND:
			break;
		case OR:
			break;
		case CMP:
			if (reg[ir.opd1] == reg[ir.opd2])
				reg[ir.opd1] = 0;
			else if (reg[ir.opd1] > reg[ir.opd2])
				reg[ir.opd1] = 1;
			else if (reg[ir.opd1] < reg[ir.opd2])
				reg[ir.opd1] = -1;
			*PC = *PC + 12;
			break;
		case TRP:
			if (ir.opd1 == 0 && currentThread == 0)
				Running = false;
			else if (ir.opd1 == 1)
			{
				userInt = reg[3];
				cout << userInt;
			}
			else if (ir.opd1 == 2)
			{
				cin >> temp;
				reg[3] = stoi(temp);
			}
			else if (ir.opd1 == 3)
				cout << char(reg[3]);
			else if (ir.opd1 == 4)
			{
				reg[3] = getchar();
			}
			else
				cout << " error with trap";
			*PC = *PC + 12;
			break;
		case STR2:
			mem.RegInsertI(reg[ir.opd2], reg[ir.opd1]);
			*PC = *PC + 12;
			break;
		case LDR2:
			reg[ir.opd1] = mem.getInt(reg[ir.opd2]);
			*PC = *PC + 12;
			break;
		case STB2:
			mem.RegInsertB(reg[ir.opd2], reg[ir.opd1]);
			*PC = *PC + 12;
			break;
		case LDB2:
			reg[ir.opd1] = mem.getByte(reg[ir.opd2]);
			*PC = *PC + 12;
			break;
		case RUN:
			userInt = currentThread;
			if (!((currentThread + 1) == 5))
				currentThread++;
			else
				currentThread = 0;
			while (Tarr[currentThread] == 1)
			{
				if (!(++currentThread % 5))
					currentThread = 0;
			}
			userInt2 = MEMSIZE - (TS * currentThread);
			for (int i = 0; i < 8; i++)
			{
				mem.RegInsertI(userInt2, reg[i]);
				userInt2 = userInt2 - 4;
			}
			mem.RegInsertI(userInt2,mem.labels[ir.opd2].location);
			userInt2 = userInt2 - 4;
			mem.RegInsertI(userInt2, MEMSIZE - (TS*currentThread + 52));
			userInt2 = userInt2 - 4;
			mem.RegInsertI(userInt2, MEMSIZE - (TS*currentThread + 52));
			userInt2 = userInt2 - 4;
			mem.RegInsertI(userInt2, MEMSIZE - (TS*currentThread + 52));
			userInt2 = userInt2 - 4;
			mem.RegInsertI(userInt2, MEMSIZE - (TS*currentThread + 1000));
			reg[ir.opd1] = currentThread;
			Tarr[currentThread] = 1;
			currentThread = userInt;
			*PC = *PC + 12;
			break;
		case END:
			if (currentThread == 0)
				*PC = *PC + 12;
			else
				Tarr[currentThread] = -1;
			break;
		case BLK:
			if (!(Tarr[1] != -1 || Tarr[2] != -1 || Tarr[3] != -1 || Tarr[4] != -1))
				*PC = *PC + 12;
			break;
		case LCK:
			if (mem.mem[mem.labels[ir.opd1].location] == -1)
			{
				mem.reinsert(mem.labels[ir.opd1].location, currentThread);
				*PC = *PC + 12;
			}
			break;
		case ULK:
			if (mem.mem[mem.labels[ir.opd1].location] == currentThread)
			{
				mem.reinsert(mem.labels[ir.opd1].location, -1);
				*PC = *PC + 12;
			}
			break;
		default:
			cout << "something didn't go correctly";
			break;
		}
		userInt = 0;
		for (int i = MEMSIZE - (TS * currentThread); i > MEMSIZE - (TS *currentThread) - 52; i = i-4)
		{
			mem.RegInsertI(i, reg[userInt++]);
		}
		if (!((currentThread + 1) == 5))
			currentThread++;
		else
			currentThread = 0;
		while (Tarr[currentThread] != 1)
		{
			if (!(++currentThread % 5))
				currentThread = 0;
		}
		userInt = 0;
		for (int i = MEMSIZE - (TS*currentThread); i > MEMSIZE - ((TS * currentThread) + (52)); i = i - 4)
		{
			iptr = (int*)(mem.mem + i);
			reg[userInt++] = *iptr;
		}
	}
}