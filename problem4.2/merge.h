#ifndef mergeH
#define mergeH

#include "list.h"

template<bool C, typename A, typename B>
struct IF
{
};

template<typename A, typename B>
struct IF<true, A, B>
{
	typedef A type;
};

template<typename A, typename B>
struct IF<false, A, B>
{
	typedef B type;
};

template<typename L1, typename L2>
struct MERGE
{
	typedef	typename IF<
        (L1::Head < L2::Head),
        LIST<L1::Head, typename MERGE<typename L1::Tail, L2>::type>,
		LIST<L2::Head, typename MERGE<L1, typename L2::Tail>::type>		
	>::type type;
};

template<typename L1>
struct MERGE<L1, EmptyList>
{
	typedef L1 type;
};

template<typename L2>
struct MERGE<EmptyList, L2>
{
	typedef L2 type;
};

#endif /* mergeH */
