#include "CurveMove.h"

Vector2f CurveMove::makeMove(const double time_elapsed, float speed, Vector2f pos){
	Vector2f result;

	Vector2f dest = path[actual_path];
	if (pos.x >= dest.x - odl && pos.x <= dest.x + odl && pos.y >= dest.y - odl && pos.y <= dest.y + odl){
		if (actual_path == 5)
			actual_path = 5;
		else
			actual_path++;
		normalize(pos, path[actual_path]);
	}
	result.x = (float)time_elapsed*normalized.x*speed * 2;
	result.y = (float)time_elapsed*normalized.y*speed * 2;

	return result;
}

void CurveMove::normalize(Vector2f enemy_pos, Vector2f dest){
	Vector2f _normalized = dest - enemy_pos;

	float lenght = sqrt(pow(_normalized.x, 2) + pow(_normalized.y, 2));

	if (first){
		max_lenght = lenght;
		part_dist = max_lenght / part_number;

		int change_x = 1, change_y = 1;
		if (enemy_pos.x >= 800)
			change_x = -1;
		else if (enemy_pos.x <= 0)
			change_x = 1;
		if (enemy_pos.y >= 640)
			change_y = -1;
		else if (enemy_pos.y <= 0)
			change_y = 1;

		int amp = 80;
		if (enemy_pos.x >= 800 || enemy_pos.x <= 0){
			path[0].x = enemy_pos.x + part_dist * change_x;
			path[0].y = enemy_pos.y - amp;
			path[1].x = enemy_pos.x + part_dist * 3 * change_x;
			path[1].y = enemy_pos.y + amp;
			path[2].x = enemy_pos.x + part_dist * 5 * change_x;
			path[2].y = enemy_pos.y - amp;
			path[3].x = enemy_pos.x + part_dist * 7 * change_x;
			path[3].y = enemy_pos.y + amp;
			path[4].x = enemy_pos.x + part_dist * 9 * change_x;
			path[4].y = enemy_pos.y - amp;
		}
		else if (enemy_pos.y >= 640 || enemy_pos.y <= 0){
			path[0].x = enemy_pos.x - amp;
			path[0].y = enemy_pos.y + part_dist * change_y;
			path[1].x = enemy_pos.x + amp;
			path[1].y = enemy_pos.y + part_dist * 3 * change_y;
			path[2].x = enemy_pos.x - amp;
			path[2].y = enemy_pos.y + part_dist * 5 * change_y;
			path[3].x = enemy_pos.x + amp;
			path[3].y = enemy_pos.y + part_dist * 7 * change_y;
			path[4].x = enemy_pos.x - amp;
			path[4].y = enemy_pos.y + part_dist * 9 * change_y;
		}

		path[5].x = dest.x;
		path[5].y = dest.y;
		first = false;
	}

	normalized.x = _normalized.x / lenght;
	normalized.y = _normalized.y / lenght;
}