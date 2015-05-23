#ifndef Straightmove
#define Straightmove

#include "MoveStrategy.h"

class StraightMove :public MoveStrategy {
private:
	Vector2f normalized;
	float length;
public:

	StraightMove(Vector2f pos){
		normalize(pos, Vector2f(400, 320));
	}
	~StraightMove(){}

	void normalize(Vector2f, Vector2f);
	Vector2f makeMove(const double, float, Vector2f);


};

#endif // !Straightmove

