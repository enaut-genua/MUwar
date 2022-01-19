#include "kalkuloak.h"

void kalkulatu_isometriko(Bekt2D* iso_pos, float x, float y)
{
	iso_pos->x = (int)(x - y);
	iso_pos->y = (int)((x + y) * 0.5);
}

void kalkulatu_kartesiarrak(Bekt2D* kartes_pos, int x, int y)
{
	kartes_pos->x = (int)((2 * y + x) / 2);
	kartes_pos->y = (int)((2 * y - x) / 2);
}