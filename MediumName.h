#ifndef MediumName
#define MediumName

#include "Modifier.h"

//ConcreteDecorator

class Medium_name : public Modifier {

public:

	Medium_name(Enemy_name *tmp) : Modifier(tmp) {}
	~Medium_name(){}

	void setName(string name);
	string addName();
};
#endif // !MediumName