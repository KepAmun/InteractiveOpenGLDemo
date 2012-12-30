
#ifndef FACE_H_
#define FACE_H_

class Face
{
private:
	float m_normal3fv[3];
	Vertex* m_vertices[3];

public:
	Face(Vertex* v1,Vertex* v2,Vertex* v3);
	Face(Vertex* vertices[]);
	Vertex** GetVertices();
	Vertex GetVertex(int i);
	float* GetNormal3fv();

	static float* CalculateNormal(float v1[],float v2[],float v3[]);
};


#endif /* FACE_H_ */
