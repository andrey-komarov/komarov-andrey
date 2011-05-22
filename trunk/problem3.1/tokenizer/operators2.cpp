#ifndef operators2
#define operators2

#include "operator.h"
#include "../big_int/big_int.h"

big_int modulo(const big_int& a, const big_int& b)
{
	return a % b;
}

add_operator("%", 2, modulo, operator_t::LEFT);

#endif

