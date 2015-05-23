#ifndef HardName
#define HardName

#include "Modifier.h"

//ConcreteDecorator

class Hard_name : public Modifier {

public:

	Hard_name(Enemy_name *tmp) : Modifier(tmp) {}
	~Hard_name(){}

	void setName(string name);

	string addName();
};
#endif // !HardName