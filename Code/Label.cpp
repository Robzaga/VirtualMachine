#include "Label.h"

Label::Label()
{
	Name = " ";
}

Label::Label(string name)
{
	Name = name;
}

void Label::insertLoc(int j)
{
	location = j;
}


