longint::longint(int b)
{
	a = vector<long long>();
	a.push_back(b);
	len = 1;
}

longint::longint(const vector<long long>& b, size_t l)
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

bool operator<(const longint& a, const longint& b) 
{
	return b > a;
}

bool operator>=(const longint& a, const longint& b)
{
	return !(a < b);
}

bool operator<=(const longint& a, const longint& b)
{
	return !(b < a);
}

bool operator!=(const longint& a, const longint& b)
{
	return !(a == b);
}

istream& operator>>(istream& is, longint& val) 
{
	string s;
	vector<long long> a;
	if (!(is >> s))
		return is >> s;
	size_t n = s.size();
	size_t m = (n - 1) / base_length + 1;
	a = vector<long long>(m);
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

void longint::norm(vector<long long>& a, size_t& l) const
{
	for (size_t i = 0; i < l - 1; i++)
	{
		if (a[i] < 0) {
			a[i] += base;
			a[i + 1]--;
		} 
		else if (a[i] >= base)
		{
			a[i + 1] += a[i] / base;
			a[i] %= base;
		}	
	}
	while (a[l - 1] == 0 && l > 1) 
		l--;
}

void longint::norm()
{
	norm(a, len);
}

longint longint::operator+(const longint& b) const
{
	size_t l = max(len, b.len) + 1;
	vector<long long> res = vector<long long>(l);
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
	vector<long long> res = vector<long long>(l);
	for (size_t i = b.len; i < l; i++)
		res[i] = 0;
	for (size_t i = 0; i < b.len; i++)
		res[i] = -b[i];
	for (size_t i = 0; i < len; i++)
		res[i] += a[i];
	return longint(res, l);
}

longint longint::operator*(const long long& b) const
{
	vector<long long> res = vector<long long>(len + 2);
	for (size_t i = 0; i < len; i++)
		res[i] = a[i] * b;
	res[len] = 0;
	size_t new_len = len + 1;
	norm(res, new_len);
	return longint(res, new_len);
}

longint longint::operator*(const longint& b) const
{
	size_t l = len + b.len + 2;
	vector<long long> res = vector<long long>(l);
	for (size_t i = 0; i < l; i++)
		res[i] = 0;
	for (size_t i = 0; i < len; i++)
	{
		for (size_t j = 0; j < b.len; j++)
			res[i + j] += a[i] * b.a[j];
		size_t tmp = l;
		if (i % 8 == 0)
			norm(res, tmp);
	}
	return longint(res, l);
}

longint longint::operator/(const long long& b) const
{
	vector<long long> res = a;
	for (int i = len - 1; i >= 1; i--)
	{
		res[i - 1] += (res[i] % b) * base;
		res[i] /= b;
	}
	res[0] /= b;
	return longint(res, len);
}

longint	longint::operator<<(const size_t shift) const
{
	size_t l = len + shift;
	vector<long long> b = vector<long long>(l);
	for (size_t i = 0; i < l; i++)
		b[i] = 0;
	for(size_t i = 0; i < len; i++)
		b[i + shift] = a[i];
	norm(b, l);
	return longint(b, l);
}


longint longint::operator/(const longint& d) const
{
	if(*this < d)
		return longint(0);
	if(*this < d * 2)
		return longint(1);
	longint a = *this;
	longint b = d;
	size_t len = a.len - b.len + 2;
	vector<long long> c = vector<long long>(len);
	for (size_t i = 0; i < len; i++)
		c[i] = 0;
	if (b.a[b.len - 1] < base / 2)
	{
		long long qq = base / (b.a[b.len - 1] + 1);
		a = a * qq;
		b = b * qq;
	}
	for (int pos = a.len - 1; pos >= 0; pos--)
	{
		if (a.len == 1)
		{
			if(a > b)
			{
				c[0] += a.a[0] / b.a[0];
				a.a[0] -= c[0] * b.a[0];
			}
			break;
		}
		size_t tmp = a.len - 1;
		long long good = 0;
		long long cc = (base * a.a[tmp] + a.a[tmp - 1]) / b.a[b.len - 1];
		long long l = max(cc - 2, 0LL);
		long long r = cc + 2;
		for (long long j = l; j <= r; j++) {
			if( ((b * j) << pos) <= a)
				good = j;
		}
		c[pos] += good;
		a = a - ((b * good) << pos);
	}
	
	if(a >= b && a < b * 2)
		c[0]++;
	norm(c, len);
	return longint(c, len);
}
