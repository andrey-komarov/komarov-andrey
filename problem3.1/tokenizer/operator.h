#ifndef operatorH
#define operatorH

#include <string>
#include <boost/function.hpp>
#include <map>
#include "../big_int/big_int.h"
#include "function.h"

struct operator_t
{
	enum ASSOCIATIVITY
	{
		LEFT, RIGHT
	};
	operator_t();
	operator_t(const std::string&, int, boost::function<big_int (big_int, big_int)>, ASSOCIATIVITY);
	std::string get_name() const;
	ASSOCIATIVITY get_associativity() const;
	big_int apply(const big_int&, const big_int&) const;
private:
	std::string name_;
	boost::function<big_int (big_int, big_int)> f_;
	int priority_;
	ASSOCIATIVITY associativity_;
};

std::map<std::string, operator_t>& operators();

#define add_operator(name, priority, f, associativity) namespace{struct initializer##f{initializer##f(){operators()[name] = operator_t(name, priority, f, associativity);}};initializer##f a##f;};

#endif /* operatorH */
