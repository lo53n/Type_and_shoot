#ifndef FastEnemy
#define FastEnemy

#include "EnemyName.h"

//ConcreteComponent

class Fast_enemy : public Enemy_name {

private:
	float& speed;
	string& name_;
public:

	Fast_enemy(string& tmp, float& tmp2) : name_(tmp), speed(tmp2) {}
	virtual ~Fast_enemy(){}

	void setName(string name);
};
#endif // !FastEnemy