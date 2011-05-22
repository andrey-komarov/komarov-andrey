#ifndef operatorCPP
#define operatorCPP

#include "operator.h"

std::map<std::string, operator_t>& operators()
{
	static std::map<std::string, operator_t> operators_;
	return operators_;
}

operator_t::operator_t()
{
}

operator_t::operator_t(
	const std::string& name, 
	int priority, 
	boost::function<big_int (big_int, big_int)> f, 
	ASSOCIATIVITY associativity
):
	name_(name),
	priority_(priority),
	f_(f),
	associativity_(associativity)
{
}

std::string operator_t::get_name() const
{
	return name_;
}

operator_t::ASSOCIATIVITY operator_t::get_associativity() const
{
	return associativity_;
}

#endif /* operatorCPP */
