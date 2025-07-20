#pragma once

class Point
{
public:
	Point() : m_x(0), m_y(0)
	{
		/*this->x = 0;
		this->y = 0;*/
	}
	Point(int x, int y) :m_x(x), m_y(y)
	{
		/*this->x = x;
		this->y = y;*/
	}
	Point(const Point& point) : m_x(point.m_x), m_y(point.m_y)
	{
		/*this->x = point.x;
		this->y = point.y;*/
	}
	~Point()
	{

	}
public:
	int m_x = 0;
	int m_y = 0;
};