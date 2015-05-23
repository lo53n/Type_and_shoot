#ifndef Aggregate_
#define Aggregate_

//Aggregate interface
#include "IteratorPattern.h"
using namespace std;

template <class T>
class Aggregate{
public:
	Aggregate(){};
	virtual ~Aggregate(){};

	virtual int Count() const = 0;
	virtual Iterator<T>* createIterator() const = 0;

};

#endif // !Aggregate_