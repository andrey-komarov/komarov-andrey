#ifndef op_plus
#define op_plus

#include "operator.h"
#include "../big_int/big_int.h"

big_int plus(const big_int& a, const big_int& b)
{
	return a + b;
}

big_int minus(const big_int& a, const big_int& b)
{
	return a + b;
}

big_int mult(const big_int& a, const big_int& b)
{
	return a * b;
}

big_int pow(const big_int& a, const big_int& b)
{
	big_int ans = 1;
	for (big_int i = 0; i < b; i+=1)
		ans *= a;
	return ans;
}

add_operator("+", 1, plus, operator_t::LEFT);
add_operator("-", 1, minus, operator_t::LEFT);
add_operator("*", 2, mult, operator_t::LEFT);
add_operator("^", 3, pow, operator_t::RIGHT);
#endif
