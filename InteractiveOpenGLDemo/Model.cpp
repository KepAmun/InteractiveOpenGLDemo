

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <GL/gl.h>
#include "Model.h"

using namespace std;

Model::Model()
{
}

void Model::LoadObjFile(string filepath)
{
	ifstream inFile;

	inFile.open(filepath.c_str(), ifstream::in);

	if (inFile.is_open())
	{
		bool foundV = false;
		bool foundF = false;

		char* line = new char[256];

		while (!inFile.eof())
		{
			char c = inFile.peek();

			switch (c)
			{
			case 'v':

				if (foundF)
				{
					cout << "ERROR: vertex found after faces.";
					break;
				}

				if (!foundV)
				{
					foundV = true;
					LoadVertices(inFile);
				}

				break;

			case 'f':

				if (!foundV)
				{
					cout << "ERROR: face found without vertices.";
					break;
				}

				if (!foundF)
				{
					foundF = true;
					LoadFaces(inFile);
				}

				break;

			default:

				inFile.getline(line, 256, '\n');
				inFile >> ws;
				break;
			}

		}
	}

	inFile.close();
}

void Model::LoadVertices(ifstream &inFile)
{
	m_minX = 0x7FFFFFFF;
	m_maxX = -0x7FFFFFFF;
	m_minY = 0x7FFFFFFF;
	m_maxY = -0x7FFFFFFF;
	m_minZ = 0x7FFFFFFF;
	m_maxZ = -0x7FFFFFFF;

	while (!inFile.eof())
	{
		char c = inFile.peek();

		if (c == 'v')
		{
			float x, y, z;
			inFile >> c >> x >> y >> z >> ws;
			//cout << c << " " << x << " " << y << " " << z << " " << endl;

			if (x < m_minX)
				m_minX = x;
			if (x > m_maxX)
				m_maxX = x;

			if (y < m_minY)
				m_minY = y;
			if (y > m_maxY)
				m_maxY = y;

			if (z < m_minZ)
				m_minZ = z;
			if (z > m_maxZ)
				m_maxZ = z;

			m_vertices.push_back(Vertex(x, y, z));
		}
		else if (c == 'f')
		{
			break;
		}

	}

	float centerX, centerY, centerZ;
	centerX = (m_minX + m_maxX) / 2;
	centerY = (m_minY + m_maxY) / 2;
	centerZ = (m_minZ + m_maxZ) / 2;

	for (unsigned int i = 0; i < m_vertices.size(); i++)
	{
		m_vertices[i].Offset(-centerX, -centerY, -centerZ);

        float v[3];
        v[0] = m_vertices[i].GetX();
        v[1] = m_vertices[i].GetY();
        v[2] = m_vertices[i].GetZ();
        
        float ln = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);

        v[0] /= ln;
        v[1] /= ln;
        v[2] /= ln;

        float PI = 2*acos(0.0);

        float s = asin(v[0])/PI+0.5;
        float t = asin(v[2])/PI+0.5;

        m_vertices[i].SetTexCoord(s,t);
	}

	m_minX -= centerX;
	m_maxX -= centerX;

	m_minY -= centerY;
	m_maxY -= centerY;

	m_minZ -= centerZ;
	m_maxZ -= centerZ;

}

void Model::LoadFaces(ifstream &inFile)
{
	while (!inFile.eof())
	{
		char c = inFile.peek();

		if (c == 'f')
		{
			int i1, i2, i3;
			inFile >> c >> i1 >> i2 >> i3 >> ws;

			Vertex* v1 = &m_vertices[i1-1];
			Vertex* v2 = &m_vertices[i2-1];
			Vertex* v3 = &m_vertices[i3-1];

			m_faces.push_back(Face(v1, v2, v3));

		}
		else
		{
			break;
		}

	}
}



void Model::Init()
{
    TgaTextureLoader::LoadTgaTexture(&m_textureImage,"cow-tex-fin.tga");
}

void Model::Render()
{
    glBindTexture(GL_TEXTURE_2D, m_textureImage.texID);

	for (unsigned int i = 0; i < m_faces.size(); i++)
	{
		Vertex** vertices = m_faces[i].GetVertices();

		glBegin(GL_TRIANGLES);

        glNormal3fv(m_faces[i].GetNormal3fv());

		for (int c = 0; c < 3; c++)
		{
            glTexCoord2fv(vertices[c]->GetTexCoord2fv());
            glVertex3fv(vertices[c]->GetCoord3fv());
		}

		glEnd();
	}
}

float Model::GetDepth()
{
	return m_maxZ - m_minZ;
}
