

#include <iostream>
#include <math.h>
#include <GL\gl.h>
#include "Vertex.h"
#include "Face.h"

Face::Face(Vertex* va, Vertex* vb, Vertex* vc)
{
	m_vertices[0] = va;
	m_vertices[1] = vb;
	m_vertices[2] = vc;

    float* n = CalculateNormal(vb->GetCoord3fv(),va->GetCoord3fv(),vc->GetCoord3fv());

    m_normal3fv[0] = n[0];
    m_normal3fv[1] = n[1];
    m_normal3fv[2] = n[2];

/*	for (int i = 0; i < 3; i++)
	{
		std::cout << " x:" << m_vertices[i]->Get3fv()[0] << " y:"
				<< m_vertices[i]->Get3fv()[1] << " z:"
				<< m_vertices[i]->Get3fv()[2] << endl;

		flush(cout);
	}*/
}

Face::Face(Vertex* vertices[])
{
	for (int i = 0; i < 3; i++)
	{
		m_vertices[i] = vertices[i];

/*		std::cout << " x:" << m_vertices[i]->Get3fv()[0] << " y:"
				<< m_vertices[i]->Get3fv()[1] << " z:"
				<< m_vertices[i]->Get3fv()[2] << endl;

		flush(cout);*/
	}
}

Vertex** Face::GetVertices()
{
	return m_vertices;
}

Vertex Face::GetVertex(int i)
{
	return *m_vertices[i];
}

float* Face::GetNormal3fv()
{
    return m_normal3fv;
}

float* Face::CalculateNormal(float v1[],float v2[],float v3[])
{
    float *n = new float[3];

	GLfloat Qx, Qy, Qz, Px, Py, Pz;

	Qx = v2[0] - v1[0];
	Qy = v2[1] - v1[1];
	Qz = v2[2] - v1[2];
	Px = v3[0] - v1[0];
	Py = v3[1] - v1[1];
	Pz = v3[2] - v1[2];
    
	n[0] = Py * Qz - Pz * Qy;
	n[1] = Pz * Qx - Px * Qz;
	n[2] = Px * Qy - Py * Qx;

    float ln = sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
    
    n[0] /= ln;
    n[1] /= ln;
    n[2] /= ln;

    return n;
}
