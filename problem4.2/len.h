#ifndef lenH
#define lenH

#include "list.h"

template<typename T>
struct LEN
{
	enum {value = 1 + LEN<typename T::Tail>::value};
};

template<>
struct LEN<EmptyList>
{
	enum {value = 0};
};

#endif /* lenH */
