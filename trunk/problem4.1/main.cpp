#include <iostream>
#include <fstream>

#include "add.h"
#include "list_utils.h"
#include "subtract.h"
#include "multiply.h"

using namespace std;

ostream& operator<<(ostream& out, EmptyList)
{
	return out;
}

template<digit_t A, typename T>
ostream& operator<<(ostream& out, L<A, T> a)
{
	out << a.Head << " " << T();
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
	cout << ADD<list, list2>::type() << "\n";
	cout << SUBTRACT<list, list2>::type() << "\n";
	cout << SUBTRACT<list, list4>::type() << "\n";
	cout << SUBTRACT<list, list>::type() << "\n";
	cout << MULTIPLY<list, list4>::type() << "\n";
	cout << MULTIPLY<list5, list6>::type() << "\n";
	//~ cout << REVERSE<list>::type() << "\n";
	//~ cout << APPEND<list2, 132>::type() << "\n";
	//~ cout << ADD<list, list2>::type() << "\n";
}
