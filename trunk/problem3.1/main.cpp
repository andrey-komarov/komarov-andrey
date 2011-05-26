#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "calculator.h"

int main()
{
    std::string str;
    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        std::cout << calculate(str) << "\n";
        
    }

    std::cout << "Bye... :-) \n\n";
    return 0;	
}
