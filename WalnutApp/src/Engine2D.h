#pragma once

#include "math.h"

#define WIDTH 960
#define HEIGHT 540

namespace Engine
{
	static double Distance(double x1, double y1, double x2, double y2)
	{
		return sqrt(pow(x1 - x2, (double)2) + pow(y1 - y2, (double)2));
	}

	// position in world space
	struct Position 
	{
		double x;
		double y;
	};

	class Transform
	{
	public:
		Position position;
		//rotation
	};

	class Object
	{
	public:
		Transform m_Transform;

		bool fixed = true;

		Object()
		{

		}
	};

	class Circle : Object
	{
	public:
		double Radius;

	};

}