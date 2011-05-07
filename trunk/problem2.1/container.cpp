#ifndef containerCPP
#define containerCPP

#include "container.h"

container::container(): size_(0)
{
}

container::container(size_t size): size_(size)
{
	if (size_ > 1) {
		digits_ = new digit_t[size_];
		for (size_t i = 0; i < size_; i++)
			digits_[i] = 0;
	} else 
		digit_ = 0;
}

container::container(const container& other): size_(other.size_)
{
	if (size_ == 1)
	{
		digit_ = other.digit_;
	}
	else
	{
		digits_ = new digit_t[size_];
		for (size_t i = 0; i < size_; i++)
			digits_[i] = other.digits_[i];
	}
}

container::container(const container& other, size_t size): size_(size)
{
	if (size_ == 1)
	{
		digit_ = other[0];
	}
	else
	{
		digits_ = new digit_t[size_];
		for (size_t i = 0; i < size_; i++)
			digits_[i] = 0;
		for (size_t i = 0; i < other.size_; i++)
			digits_[i] = other[i];
	}
}

container& container::operator=(const container& a) {
	size_ = a.size_;
	if (size_ > 1)
		digits_ = new digit_t[size_];
	for (size_t i = 0; i < size_; i++)
		(*this)[i] = a[i];
	return *this;
}

container::~container()
{
	if (size_ > 1) {
		delete digits_;
	}
}

std::ostream& operator<<(std::ostream& out, const container& a)
{
	out << "[";
	for (size_t i = 0; i < a.size_; i++)
		out << a[i] << ", ";
	out << "]";
	return out;
}

void swap(container &a, container &b)
{
	container c = a;
	a = b;
	b = c;
}

void container::resize(size_t sz)
{
	container tmp(*this, sz);
	swap(*this, tmp);
}

digit_t& container::operator[] (size_t pos)
{
	if (pos >= size_)
		resize((int)(1.9 * pos) + 2);
	return size_ == 1 ? digit_ : digits_[pos];
}

digit_t container::operator[] (size_t pos) const
{
	if (pos >= size_)
		return 0;
	return size_ == 1 ? digit_ : digits_[pos];
}

#endif
