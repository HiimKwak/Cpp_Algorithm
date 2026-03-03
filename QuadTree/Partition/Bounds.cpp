#include "Bounds.h"

bool Bounds::Intersects(const Bounds& other) const
{
	if (other.x > MaxX() || other.MaxX() < x || other.y > MaxY() || other.MaxY() < y)
		return false;

	return true;
}
