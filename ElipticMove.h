#ifndef Elipticmove
#define Elipticmove

#include "MoveStrategy.h"

class ElipticMove : public MoveStrategy{
private:
	Vector2f normalized;
	float radius;
	Vector2f center;
	double change;
	double angle;
public:

	ElipticMove(Vector2f pos, float speed){
		normalize(pos, Vector2f(400, 320));
		change = (double) .0014*speed / 100;
	}
	~ElipticMove(){}

	void normalize(Vector2f, Vector2f);
	Vector2f makeMove(const double, float, Vector2f);

};
 
#endif