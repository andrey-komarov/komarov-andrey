#ifndef tokensCPP
#define tokensCPP

#include "tokens.h"

tokens::number::number(const big_int& value):
	value_(value)
{
}

token::TOKENS tokens::number::get_type()
{
	return NUMBER;
}

tokens::op::op(const operator_t*& value):
	value_(value)
{
}

token::TOKENS tokens::op::get_type()
{
	return OPERATOR;
}

token::TOKENS tokens::left_parenthesis::get_type()
{
	return LP;
}

token::TOKENS tokens::right_parenthesis::get_type()
{
	return RP;
}

tokens::function::function(const function_t*& f):
	f_(f)
{
}

token::TOKENS tokens::function::get_type()
{
	return FUNCTION;
}


#endif /* tokensCPP */
