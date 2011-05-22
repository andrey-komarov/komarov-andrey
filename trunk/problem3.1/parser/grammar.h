/*
#ifndef grammarH
#define grammarH

#include <vector>

struct symbol
{
	symbol(size_t, bool);
	bool is_terminal();
private:	
	const bool terminal;
	const size_t id_;
};

struct rule
{
	rule(const symbol&, const std::vector<symbol>&);
	const symbol from;
	const std::vector<symbol> to;
};

#endif /* grammarH */
