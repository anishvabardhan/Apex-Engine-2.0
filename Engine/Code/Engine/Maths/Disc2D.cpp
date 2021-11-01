#include "Disc2D.h"

#include <iostream>
#include <cmath>

Disc2D::Disc2D(Vec2 center, float radius)
	:m_Center(center), m_Radius(radius)
{

}

Disc2D::~Disc2D()
{
}

bool Disc2D::CheckCollision(Disc2D* obj1, Disc2D* obj2)
{
	if(obj1 != nullptr && obj2 != nullptr)
		if ((float)((obj1->m_Center.m_X - obj2->m_Center.m_X) * (obj1->m_Center.m_X - obj2->m_Center.m_X)) +
			((obj1->m_Center.m_Y - obj2->m_Center.m_Y) * (obj1->m_Center.m_Y - obj2->m_Center.m_Y)) <=
			((obj1->m_Radius + obj2->m_Radius) * (obj1->m_Radius + obj2->m_Radius)))
			return true;

	return false;
}