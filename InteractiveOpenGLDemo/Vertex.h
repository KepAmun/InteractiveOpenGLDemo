
#ifndef VERTEX_H_
#define VERTEX_H_

using namespace std;

class Vertex
{
private:
	float* m_coord3fv;
	float* m_texCoord2fv;

public:
	Vertex();
	Vertex(float* fv);
	Vertex(double x, double y, double z);
	void SetCoords(double x, double y, double z);
	void SetTexCoord(float s, float t);
	float* GetCoord3fv();
	float* GetTexCoord2fv();
	float GetX();
	float GetY();
	float GetZ();
	void Offset(float dx, float dy, float dz);
};

#endif /* VERTEX_H_ */
