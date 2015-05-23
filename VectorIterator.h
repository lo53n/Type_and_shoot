#ifndef VectorIterator
#define VectorIterator

#include <vector>
#include "IteratorPattern.h"

template <class T>
class Vectoriterator : public Iterator<T>{

private:
	int index;
public:
	template <typename T>
	friend class VectorAg;
	const VectorAg<T> *vec;
	Vectoriterator(const VectorAg<T> *tmp) : vec(tmp), index(0) {}
	~Vectoriterator(){}

	void first(){
		index = 0;
	}

	void next(){
		if (!isDone())
			index++;
	}

	bool isDone(){
		if (index > vec->Count())
			index = vec->Count();
		return index >= vec->Count();
	}

	T currentItem(){
		if (isDone())
			return NULL;
		return vec->result[index];
	}

	T getRest(){
		return NULL;
	}



};

#endif // !VectorIterator