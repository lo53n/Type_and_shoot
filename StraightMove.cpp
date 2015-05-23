#include "StraightMove.h"

Vector2f StraightMove::makeMove(const double time_elapsed, float speed, Vector2f pos){
	Vector2f p_pos(400, 320);
	Vector2f result;
	float odl = 10;
	if (pos.x >= p_pos.x - odl && pos.x <= p_pos.x + odl && pos.y >= p_pos.y - odl && pos.y <= p_pos.y + odl){
		result.x = 0.0f;
		result.y = 0.0f;
		return result;
	}

	result.x = (float)time_elapsed*normalized.x*speed;
	result.y = (float)time_elapsed*normalized.y*speed;

	return result;
}

void StraightMove::normalize(Vector2f enemy_pos, Vector2f dest){

	Vector2f _normalized = dest - enemy_pos;

	float lenght = sqrt(pow(_normalized.x, 2) + pow(_normalized.y, 2));

	normalized.x = _normalized.x / lenght;
	normalized.y = _normalized.y / lenght;
}