/*
*		dynamic array
*
*		qiu_hao    2016/4/30	6:20 pm.
*/

/*
*
*	struct Data{int n0, n1;};
*	Data* data0 = new Data();
*	Data* data1 = new Data();
*
*	Array<Data*>* array0 = Array<Data*>::Create();
*	(*array0)[0] = data0;	// array0->push(data0);
*	(*array0)[1] = data1;	// array0->push(data1);
*	array0->pop();
*	...
*	array0 = array1;
*
*/
#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include <stdlib.h>
#include <new>
using namespace std;

#define Allocate	malloc
#define Deallocte	free
#define Reallocate	realloc

#define DEFAULT_NUM 1<<1

#ifndef roundup32(x) 
#define roundup32(x) (--(x), (x)|=(x)>>1, (x)|=(x)>>2, (x)|=(x)>>4, (x)|=(x)>>8, (x)|=(x)>>16, ++(x))
#endif

template<class Type>
class Array
{
public:
	static
	Array* Create()
	{
		void* buffer = Allocate(sizeof(Array));	// Allocate : can be a pool to allocate
		return new(buffer)	Array; 
	}
	static 
	Array* Create(size_t _capacity)
	{
		void* buffer = Allocate(sizeof(Array));	// Allocate : can be a pool to allocate
		return new(buffer)Array(_capacity);
	}
	static void
	destroy(void* arr)
	{
		static_cast<Array*>(arr)->~Array();
	}
public:
	bool operator==(const Array& _array)
	{
		return _array.m_capacity == m_capacity && __equal( _array ) ;
	}

	/*
	Array<Type>& operator=(const Array<Type>& _array)
	{
		if (_array == this) return *this;
		if ()
		{

		}
		else
		{

		}
		return *this;
	}
	*/

	Type& operator[](size_t i)
	{
			
	}


	size_t getCur()
	{
		return this->m_cur;
	}

	size_t getCapacity()
	{
		return this->m_capacity;
	}
	bool isEmpty()
	{
		return (m_cur == 0);
	}
private:
	bool __equal(const Array& _array )
	{
		return true;
	}



private:
	Array() :m_cur(0), m_capacity(DEFAULT_NUM)
	{
		m_container = (Type**)malloc(sizeof(Type*) * DEFAULT_NUM);
	}
	Array(size_t _capacity) :m_cur(0), m_capacity(_capacity)
	{
		m_container = (Type**)malloc(sizeof(Type*) * _capacity);
	}
	~Array()
	{
		free(m_container); // Type objs will be freed by pool
	}
private:
	size_t m_cur;
	size_t m_capacity;
	Type**  m_container;
};

#endif /* __ARRAY_H__ */
