
#ifndef FACE_H_
#define FACE_H_

class Face
{
private:
    float m_normal3fv[3];
    Vertex* m_vertices[3];
    
    void CalculateNormal();

public:
    Face(Vertex* v1,Vertex* v2,Vertex* v3);
    Face(Vertex* vertices[]);
    
    Vertex** GetVertices();
    Vertex GetVertex(int i);
    float* GetNormal3fv();
};


#endif /* FACE_H_ */
