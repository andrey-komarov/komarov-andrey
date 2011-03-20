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
        {
            longint q = a / b;
            longint r = a - q * b;
            out << q << "\n" << r << "\n\n";
        }
    }
}
