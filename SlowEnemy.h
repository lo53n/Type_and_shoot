#ifndef SlowEnemy
#define SlowEnemy

#include "EnemyName.h"

//ConcreteComponent

class Slow_enemy : public Enemy_name {

private:
	float& speed;
	string& name_;
public:

	Slow_enemy(string& tmp, float& tmp2) : name_(tmp), speed(tmp2) {}
	virtual ~Slow_enemy(){}

	void setName(string name);
};
#endif // !SlowEnemy