#ifndef NameModifier
#define NameModifier

#include <fstream>
#include <vector>
#include "EnemyName.h"

//Abstract class - DECORATOR

class Modifier : public Enemy_name {

private:
	Enemy_name *enemy;
public:

	Modifier(Enemy_name *tmp) : enemy(tmp) {}
	virtual ~Modifier(){}

	/* virtual */
	void setName(string name){ enemy->setName(name); }
	string addName();
};
#endif // !NameModifier