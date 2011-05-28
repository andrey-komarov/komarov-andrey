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
	typedef L<1, L<0, L<0, L<9, EmptyList> > > > list;
	typedef L<1, L<0, L<0, L<8, EmptyList> > > > list4;
	typedef L<9, L<9, L<9, EmptyList> > > list2;
	typedef L<999, EmptyList> list3;
	typedef L<2, L<5, EmptyList> > list5;
	typedef L<1, L<4, EmptyList> > list6;
	typedef L<2, EmptyList> list7;
	cout << DIVIDE<list, list5>::type() << "\n";
}
