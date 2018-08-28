/*
*
*		qiu_hao		2018/08/27		21:53.pm
*/
#ifndef __CQACTION_H__
#define __CQACTION_H__

template<size_t...idxs>
struct Index
{

};

template<size_t N, size_t...idxs>
struct SeqGen : SeqGen<N - 1, N - 1, idxs...>
{

};

template<size_t...idxs>
struct SeqGen<0, idxs...> : Index<idxs...>
{

};

















#endif /* __CQACTION_H__ */