#include "ElipticMove.h"
#define _USE_MATH_DEFINES
#include <math.h>

Vector2f ElipticMove::makeMove(const double time_elapsed, float speed, Vector2f pos){
	Vector2f p_pos(400, 320);
	Vector2f result;

	result.x = (float)time_elapsed*normalized.x;
	result.y = (float)time_elapsed*normalized.y;

	int odl = 10;
	if (pos.x >= p_pos.x - odl && pos.x <= p_pos.x + odl && pos.y >= p_pos.y - odl && pos.y <= p_pos.y + odl){
		result.x = 0.0f;
		result.y = 0.0f;
		return result;
	}
	result.x = (float)cos(angle + 90 * M_PI / 180) * radius;
	result.y = (float)sin(angle + 90 * M_PI / 180) * radius;
	angle += change;


	result.x = result.x * (float)change;
	result.y = result.y * (float)change;
	return result;
}

void ElipticMove::normalize(Vector2f enemy_pos, Vector2f dest){

	Vector2f _normalized = dest - enemy_pos;

	float lenght = sqrt(pow(_normalized.x, 2) + pow(_normalized.y, 2));
	radius = lenght / 2;
	angle = atan2(enemy_pos.y - 320, enemy_pos.x - 400);

	normalized.x = _normalized.x / lenght;
	normalized.y = _normalized.y / lenght;

}