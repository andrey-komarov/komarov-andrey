#ifndef normalize_negativeH
#define normalize_negativeH

#include "list.h"

// TODO!!!!

template<digit_t carry, typename T>
struct NORMALIZE_NEGATIVE
{
	typedef 
	typename NORMALIZE_NEGATIVE<
		0,
		L<
			(T::Head + carry), 
			typename T::Tail
		> 
	>::type type;
};

template<typename T>
struct NORMALIZE_NEGATIVE<0, T>
{
	typedef 
	L<
		(T::Head < 0) ? (T::Head + BASE) : T::Head,
		typename NORMALIZE_NEGATIVE<
			T::Head < 0 ? -1 : 0,
			typename T::Tail
		>::type
	> type;
};

template<>
struct NORMALIZE_NEGATIVE<0, EmptyList>
{
	typedef EmptyList type;
};

template<digit_t carry>
struct NORMALIZE_NEGATIVE<carry, EmptyList>
{
	typedef 
	typename NORMALIZE_NEGATIVE<
		0,
		L<
			carry, 
			EmptyList
		>
	>::type type;
};

#endif /* normalize_negativeH */
