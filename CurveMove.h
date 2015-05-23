#ifndef Curvemove
#define Curvemove

#include "MoveStrategy.h"

class CurveMove :public MoveStrategy{
private:
	bool first;
	Vector2f normalized;
	float max_lenght;
	float part_dist;
	int part_number;
	int actual_path;
	Vector2f enemy_pos;
	Vector2f path[6];
	int odl;
public:

	CurveMove(Vector2f pos) :
		enemy_pos(pos),
		first(true),
		part_number(10),
		actual_path(0),
		odl(10)
	{
		normalize(pos, Vector2f(400, 320));
		normalize(pos, path[0]);
	}
	~CurveMove(){}

	void normalize(Vector2f, Vector2f);
	Vector2f makeMove(const double, float, Vector2f);



};

#endif // !Curvemove

