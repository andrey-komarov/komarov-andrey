#include <fstream>
#include <string>
#include "big_int.h"

int main()
{
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    big_int a, b;
    big_int zero = 0;
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
