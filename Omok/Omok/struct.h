#pragma once

struct Vec2
{
	float x;
	float y;

public:
	Vec2()
		: x(0)
		, y(0)
	{}

	Vec2(float _f)
	{
		x = _f;
		y = _f;
	}

	Vec2(float _fx, float _fy)
	{
		x = _fx;
		y = _fy;
	}

	void operator += (float _f)
	{
		x += _f;
		y += _f;
	}

	void operator -= (float _f)
	{
		x -= _f;
		y -= _f;
	}
};

