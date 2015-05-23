#ifndef Movestrategy
#define Movestrategy

#include <math.h>
#include <SFML/Graphics.hpp>
// Abstract class - STRATEGY
using namespace sf;

class MoveStrategy{

public:

	MoveStrategy(){};
	virtual ~MoveStrategy(){}

	virtual void normalize(Vector2f, Vector2f) = 0;
	virtual Vector2f makeMove(const double, float, Vector2f) = 0;

};


#endif // !Movestrategy