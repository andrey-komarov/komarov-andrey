#ifndef tokensH
#define tokensH

#include "../big_int/big_int.h"
#include "operator.h"
#include "function.h"	

struct token
{	
	enum TOKENS
	{
		NUMBER, OPERATOR, LP, RP, FUNCTION
	};

	virtual TOKENS get_type() = 0;
};

namespace tokens
{
	struct number : token
	{
		number(const big_int& = 0);
		TOKENS get_type();
		big_int value_;
	};
	
	struct op : token
	{
		op(const operator_t*&);
		TOKENS get_type();
		const operator_t* value_;
	};
	
	struct left_parenthesis : token
	{
		TOKENS get_type();
	};
	
	struct right_parenthesis : token
	{
		TOKENS get_type();
	};
	
	struct function : token
	{
		function(const function_t*&);
		TOKENS get_type();
		const function_t* f_;
	};
};

#endif /* tokensH */
