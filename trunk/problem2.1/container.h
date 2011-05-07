#ifndef containerH
#define containerH

#include <cstddef>
#include <iostream>

typedef long long digit_t;

using std::cerr;

class badindex{};

struct container
{
	container();
	container(size_t);
	container(const container&);
	container& operator=(const container&);
	void resize(size_t);
	size_t size() const;
	digit_t& operator[](size_t);
	digit_t operator[](size_t) const;
	~container();
	void norm();

private:
	container(const container&, size_t);
	size_t size_;
	union {
		digit_t * digits_;
		digit_t digit_;
	};

	friend void swap(container&, container&);
	friend std::ostream& operator<<(std::ostream&, const container&);
};

#include "container.cpp"

#endif
