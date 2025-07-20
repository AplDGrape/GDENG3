#pragma once
class Point
{
public:
	Point()
	{
		this->x = 0;
		this->y = 0;
	}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	Point(const Point& point)
	{
		this->x = point.x;
		this->y = point.y;
	}
	~Point()
	{

	}

public:
	int x = 0, y = 0;
};

