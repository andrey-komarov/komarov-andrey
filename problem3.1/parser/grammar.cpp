/*

#ifndef grammarCPP
#define grammarCPP

#include "grammar.h"



symbol::symbol(size_t id, bool _terminal):
	id_(id),
	terminal(_terminal)
{
}

rule::rule(const symbol& from_, const vector<symbol>& to_):
	from(from_),
	to(to_)
{
}

#endif /* grammarH */
