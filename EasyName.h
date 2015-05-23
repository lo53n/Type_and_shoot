#ifndef EasyName
#define EasyName

#include "Modifier.h"

//ConcreteDecorator

class Easy_name : public Modifier {

public:

	Easy_name(Enemy_name *tmp) : Modifier(tmp) {}
	~Easy_name(){}

	void setName(string name);
	string addName();
};
#endif // !EasyName