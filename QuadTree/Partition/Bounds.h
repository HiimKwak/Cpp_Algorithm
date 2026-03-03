#pragma once

class Bounds
{
public:
	Bounds(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

	bool Intersects(const Bounds& other) const;

	inline int X() const { return x; }
	inline int Y() const { return y; }
	inline int Width() const { return width; }
	inline int Height() const { return height; }
	inline int MaxX() const { return x + width; }
	inline int MaxY() const { return y + height; }

private:
	int x = 0, y = 0;
	int width = 1, height = 1;
};

