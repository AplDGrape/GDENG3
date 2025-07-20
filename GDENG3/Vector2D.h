#pragma once
class Vector2D
{
public:
	Vector2D()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Vector2D(const Vector2D& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
	}
	Vector2D operator* (float num)
	{
		return Vector2D(this->x * num, this->y * num);
	}
	Vector2D operator+ (Vector2D vec)
	{
		return Vector2D(this->x + vec.x, this->y + vec.y);
	}
	Vector2D operator- (Vector2D vec)
	{
		return Vector2D(this->x - vec.x, this->y - vec.y);
	}
	Vector2D operator/ (Vector2D vec)
	{
		return Vector2D(this->x / vec.x, this->y / vec.y);
	}
	float getX()
	{
		return this->x;
	}
	float getY()
	{
		return this->y;
	}
	~Vector2D()
	{

	}

private:
	float x, y;
};

