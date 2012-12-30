
#ifndef MODELVIEWER_H_
#define MODELVIEWER_H_

#include <GL/glut.h>
#include <GL/glui.h>
#include "GlutView.h"
#include "Model.h"
#include "Vertex.h"

using namespace std;

const int PolygonModes[3] = {GL_POINT, GL_LINE, GL_FILL};

class ModelViewer: public GlutView
{
private:
	ModelViewer();

	Model m_model;

    GLUquadric* m_quad;
    
	int m_polygonMode;

	float m_rotateX;
	float m_rotateY;
	float m_rotateZ;

	float m_translateX;
	float m_translateY;
	float m_translateZ;

	float m_camDistance;
	float m_camTheta;
	float m_camPhi;
    
	float m_fovH;
	float m_fovV;
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;
    
	bool m_leftButtonDown;
	bool m_rightButtonDown;
	int m_mouseDownX;
	int m_mouseDownY;
	int m_mouseX;
	int m_mouseY;

    int m_textureOn;

    int m_lightingOn;
    float m_lightAmbient[4];
    float m_lightDiffuse[4];
    float m_lightSpecular[4];
    
    int m_ambientOn;
    float m_matAmbient[4];
    int m_diffuseOn;
    float m_matDiffuse[4];
    int m_specularOn;
    float m_matSpecular[4];
    float m_matShininess;

	void SetPerspective();
	void PositionCamera();

    GLUI_Spinner* m_zoomSpinner;

public:
    static ModelViewer* GetInstance();
	void Show(int argc, char **argv, string filePath);

	void Display();
	void Reshape(int width, int height);
	void MouseDown(int button, int state, int x, int y);
	void MouseMove(int x, int y);

	void Init();
};

#endif /* MODELVIEWER_H_ */
