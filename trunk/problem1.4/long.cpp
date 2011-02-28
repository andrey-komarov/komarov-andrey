longint::longint(int b)
{
	a = new long long[1];
	a[0] = b;
	len = 1;
}

longint::longint(long long*& b, size_t l)
{
	a = b;
	len = l;
	norm();
}

long long longint::operator[](int pos) const
{
	return a[pos];
}

longint& longint::operator=(const longint& b)
{
	a = b.a;
	len = b.len;
	return *this;
}

bool longint::operator>(const longint& b) const
{
	if (len != b.len)
		return len > b.len;
	for (int i = len - 1; i >= 0; i--)
		if (a[i] != b.a[i])
			return a[i] > b.a[i];
	return false;
}

bool longint::operator==(const longint& b) const
{
	if (len != b.len)
		return false;
	for (size_t i = 0; i < len; i++)
		if (a[i] != b.a[i])
			return false;
	return true;
}

bool longint::operator<(const longint& b) const
{
	return b > *this;
}

bool longint::operator>=(const longint& b) const
{
	return *this > b || *this == b;
}

bool longint::operator<=(const longint& b) const
{
	return *this < b || *this == b;
}

bool longint::operator!=(const longint& b) const
{
	return !(*this == b);
}

istream& operator>>(istream& is, longint& val) 
{
	string s;
	long long* a;
	if (!(is >> s))
		return is >> s;
	size_t n = s.size();
	size_t m = (n - 1) / base_length + 1;
	a = new long long[m];
	for (int i = n - 1, j = 0; i >= 0; i -= base_length, j++)
		if (i >= base_length)
			a[j] = atol(s.substr(i - base_length + 1,base_length).c_str());
		else
			a[j] = atol(s.substr(0, i + 1).c_str());
	val = longint(a, m);
	return is;
}

ostream& operator<<(ostream& os, const longint& val)
{
	int n = val.len;
	os << val.a[n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		long long now = val.a[i];
		long long now2 = now;
		int len = 0;
		for (len = 0; now2 > 9; now2 /=10, len++);
		for (int i = 0; i < base_length - len - 1; i++)
			os << "0";
		os << now;
	}
	return os;
}

void longint::norm(long long*& a, size_t& l, bool need_shorten = true) const
{
	for (size_t i = 0; i < l - 1; i++)
	{
		if (a[i] < 0) {
			a[i] += base;
			a[i + 1]--;
		} 
		else if (a[i] > base)
		{
			a[i + 1] += a[i] / base;
			a[i] %= base;
		}	
	}
	while (need_shorten && a[l - 1] == 0 && l > 1) 
		l--;
}

void longint::norm()
{
	norm(a, len);
}

longint longint::operator+(const longint& b) const
{
	size_t l = max(len, b.len) + 1;
	long long *res = new long long[l];
	for (size_t i = b.len; i < l; i++)
		res[i] = 0;
	for (size_t i = 0; i < b.len; i++)
		res[i] = b[i];
	for (size_t i = 0; i < len; i++)
		res[i] += a[i];
	return longint(res, l);
}

longint longint::operator-(const longint& b) const
{
	size_t l = max(len, b.len) + 1;
	long long *res = new long long[l];
	for (size_t i = b.len; i < l; i++)
		res[i] = 0;
	for (size_t i = 0; i < b.len; i++)
		res[i] = -b[i];
	for (size_t i = 0; i < len; i++)
		res[i] += a[i];
	return longint(res, l);
}

longint longint::operator*(const longint& b) const
{
	size_t l = len + b.len + 1;
	long long *res = new long long[l];
	for (size_t i = 0; i < l; i++)
		res[i] = 0;
	for (size_t i = 0; i < len; i++)
	{
		for (size_t j = 0; j < b.len; j++)
			res[i + j] += a[i] * b[j];
		if (i % 8 == 0)
			norm(res, l, false);
	}
	return longint(res, l);
}

longint longint::operator/(const long long& b) const
{
	long long *res = a;
	for (int i = len - 1; i >= 1; i--)
	{
		res[i - 1] += (res[i] % b) * base;
		res[i] /= b;
	}
	res[0] /= b;
	return longint(res, len);
}

longint longint::operator/(const longint& b) const
{
	longint l(0);
	longint r = *this + longint(1);
	longint one = 1;
	while (l + one < r)
	{
		longint c = (l + r) / 2;
		size_t lenB = b.len;
		size_t lenC = c.len;
		if (lenB + lenC > len + 1)
		{
			r = c;
			continue;
		}
		if (lenB + lenC + 1 < len)
		{
			l = c;
			continue;
		}
		if (b * c > *this)
			r = c;
		else
			l = c;
	}
	return l;
}

longint longint::operator%(const longint& b) const
{
	return *this - (*this / b) * b;
}
