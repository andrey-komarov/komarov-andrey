#include <fstream>
#include <string>
#include "long.h"

int main()
{
	std::ifstream in("in.txt");
	std::ofstream out("out.txt");
	longint a, b;
	longint zero = 0;
	while (in >> a >> b)
	{
		if (b == zero)
			out << "<error>\n\n\n";
		else 
			out << (a / b) << "\n" << (a % b) << "\n\n";
	}
}
