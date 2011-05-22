#include <fstream>
#include <iostream>
#include <string>
#include "tokenizer/tokens.h"
#include <map>

using std::cerr;

int main()
{
	for (std::map<std::string, operator_t>::iterator it = operators().begin(); it != operators().end(); it++)
	{
		cerr << (*it).first << "\n";
	}
	//~ parse("2 -  3*4/  5 - 6 +7");
}
