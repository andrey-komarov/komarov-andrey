#include "sign.h"

std::ostream& operator<<(std::ostream& out, const Sign& s)
{
    if (s == Sign::ON)
        return out << "0";
    else if (s == Sign::LEFT)
        return out << "+";
    else
        return out << "-";
}
