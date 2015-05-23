#include "StringAggregate.h"
#include "StringIterator.h"

int StringAg::Count()const {
	return StringAg::result.length();
}

Iterator<string> *StringAg::createIterator() const{
	return new Stringiterator(this);
}
