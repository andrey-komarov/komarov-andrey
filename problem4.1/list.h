#ifndef listH
#define listH

typedef long long digit_t;
const digit_t BASE = 10;

struct EmptyList{};

template<long long A, typename T>
struct L{
	typedef T Tail;
	enum {Head = A};
};

#endif /* listH */
