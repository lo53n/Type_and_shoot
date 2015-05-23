#ifndef VectorAggregate
#define VectorAggregate

//Aggregate interface

#include <vector>
#include "Aggregate_.h"
#include "VectorIterator.h"

template <class T>
class VectorAg : public Aggregate<T>{

public:
	template <typename T>
	friend class Vectoriterator;

	vector<T> &result;
	VectorAg(vector<T> &tmp) :result(tmp){}
	~VectorAg(){}

	int Count() const{
		return result.size();
	}

	Iterator<T> *createIterator() const{
		return new Vectoriterator<T>(this);
	}

};
#endif // !VectorAggregate