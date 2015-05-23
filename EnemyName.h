#ifndef EnemyName
#define EnemyName

#include <string>
#include <iostream>

using namespace std;

//abstract class - COMPONENT

class Enemy_name {

public:

	Enemy_name(){}
	virtual ~Enemy_name(){}

	virtual void setName(string name) = 0;
};

#endif // !EnemyName