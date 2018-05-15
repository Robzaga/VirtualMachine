#include "IR.h"


IR::IR()
{

}
IR::IR(char i[], char j[], char k[])
{
	opcode = i[0];
	opd1 = j[0];
	opd2 =k[0];
}

