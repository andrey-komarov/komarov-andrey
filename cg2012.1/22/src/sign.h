#ifndef SIGN_H
#define SIGN_H
#include <ostream>

enum class Sign
{
    LEFT = 1, ON = 0, RIGHT = -1,
    NEGATIVE = -1, ZERO = 0, POSITIVE = 1,
    INSIDE = 1, OUTSIDE = -1, BOUND = 0
};

std::ostream& operator<<(std::ostream&, const Sign& s);

#endif
