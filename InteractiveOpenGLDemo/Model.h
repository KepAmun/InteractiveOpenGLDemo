
#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include "Vertex.h"
#include "Face.h"
#include "TgaTextureLoader.h"

using namespace std;

class Model
{
private:
	vector<Vertex> m_vertices;
	vector<Face> m_faces;
	float m_minX, m_maxX, m_minY, m_maxY, m_minZ, m_maxZ;

    TextureImage m_textureImage;

	void LoadVertices(ifstream &inFile);
	void LoadFaces(ifstream &inFile);

public:
	Model();
	void LoadObjFile(string filepath);
    void Init();
	void Render();
	float GetDepth();
};

#endif /* MODEL_H_ */
