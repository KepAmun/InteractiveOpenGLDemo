
#include <iostream>
#include "Vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(float v[])
{
	m_coord3fv[0] = v[0];
	m_coord3fv[1] = v[1];
	m_coord3fv[2] = v[2];
}

Vertex::Vertex(double x, double y, double z)
{
	SetCoords(x, y, z);
}

void Vertex::SetCoords(double x, double y, double z)
{
	m_coord3fv[0] = x;
	m_coord3fv[1] = y;
	m_coord3fv[2] = z;
}

void Vertex::SetTexCoord(float s, float t)
{
    m_texCoord2fv[0] = s;
    m_texCoord2fv[1] = t;
}

float* Vertex::GetCoord3fv()
{
	return m_coord3fv;
}

float* Vertex::GetTexCoord2fv()
{
    return m_texCoord2fv;
}

float Vertex::GetX()
{
	return m_coord3fv[0];
}

float Vertex::GetY()
{
	return m_coord3fv[1];
}

float Vertex::GetZ()
{
	return m_coord3fv[2];
}

void Vertex::Offset(float dx,float dy,float dz)
{
	m_coord3fv[0] +=dx;
	m_coord3fv[1] +=dy;
	m_coord3fv[2] +=dz;
}
