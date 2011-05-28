#include <iostream>
#include <fstream>

#include "add.h"
#include "list_utils.h"
#include "subtract.h"
#include "multiply.h"
#include "divide_by_short.h"
#include "less.h"
#include "equals.h"
#include "divide.h"

using namespace std;

ostream& operator<<(ostream& out, EmptyList)
{
	return out;
}

template<digit_t A, typename T>
ostream& operator<<(ostream& out, L<A, T> a)
{
	out << a.Head << T();
	return out;
}

int main()
{
	typedef L<1, L<8, L<7, L<6, EmptyList> > > > list;
	typedef L<2, L<5, EmptyList> > list2;
	cout << DIVIDE<list, list2>::type() << "\n";
}
