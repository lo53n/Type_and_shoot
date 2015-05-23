#ifndef StringIterator
#define StringIterator

#include <string>
#include "IteratorPattern.h"
#include "StringAggregate.h"


class Stringiterator : public Iterator<string>{

private:
	int index;
protected:
	const StringAg *str;
public:
	Stringiterator(const StringAg *tmp) : str(tmp), index(0) {}
	~Stringiterator(){}

	void first();
	void next();
	bool isDone();
	string currentItem();
	string getRest();

};

#endif // !StringIterator