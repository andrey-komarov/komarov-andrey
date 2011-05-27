#ifndef listH
#define listH

struct EmptyList{};

template<int A, typename T>
struct L{
	typedef T Tail;
	enum {Head = A};
};

#endif /* listH */
