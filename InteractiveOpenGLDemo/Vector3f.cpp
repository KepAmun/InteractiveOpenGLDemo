#include "Vector3f.h"


Vector3f::Vector3f(void)
{
    m_x = m_y = m_z = 0;
}

Vector3f::Vector3f(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

Vector3f::Vector3f(Vector3f* v)
{
    m_x = v->m_x;
    m_y = v->m_y;
    m_z = v->m_z;
}

Vector3f::~Vector3f(void)
{
}

float* Vector3f::Get3fv()
{
    float v[3] = {m_x, m_y, m_z};
    return v;
}

float Vector3f::GetX()
{
    return m_x;
}

float Vector3f::GetY()
{
    return m_y;
}

float Vector3f::GetZ()
{
    return m_z;
}

float* Vector3f::GetXRef()
{
    return &m_x;
}

float* Vector3f::GetYRef()
{
    return &m_y;
}

float* Vector3f::GetZRef()
{
    return &m_z;
}


Vector3f Vector3f::operator + (const Vector3f& v)
{
    Vector3f result = Vector3f(this);
    
    return result += v;
}

Vector3f Vector3f::operator += (const Vector3f& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;

    return *this;
}

Vector3f Vector3f::operator * (const float& f)
{
    Vector3f result = Vector3f(this);
    
    result.m_x *= f;
    result.m_y *= f;
    result.m_z *= f;

    return result;
}

Vector3f Vector3f::operator *= (const Vector3f& v)
{
    m_x *= v.m_x;
    m_y *= v.m_y;
    m_z *= v.m_z;

    return *this;
}
