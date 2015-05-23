#ifndef StringAggregate
#define StringAggregate

//Aggregate interface

#include <string>
#include "Aggregate_.h"


class StringAg :public Aggregate<std::string>{

public:
	friend class Stringiterator;

	string &result;
	StringAg(string &tmp) :result(tmp){}
	~StringAg(){}

	int Count() const;
	Iterator<string> *createIterator() const;

};
#endif // !StringAggregate