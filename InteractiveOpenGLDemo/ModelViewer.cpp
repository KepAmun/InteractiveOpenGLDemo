

#include <iostream>
#include <GL/glui.h>
#include "Model.h"
#include "ModelViewer.h"

const float PI = 2*acos(0.0f);
const float WHITE[4] = {1,1,1,1};
const float BLACK[4] = {0,0,0,0};
        
ModelViewer* ModelViewer::GetInstance()
{
    if(m_instance==NULL)
        m_instance = new ModelViewer();
    return (ModelViewer*)m_instance;
}

ModelViewer::ModelViewer()
{
	m_instance = this;
    
    m_title = "OpenGL Demo";

    m_quad = gluNewQuadric();

    m_polygonMode = 2; // GL_FILL

	m_translateX = 0;
	m_translateY = 0;
	m_translateZ = 0;

	m_rotateX = 0;
	m_rotateY = 0;
	m_rotateZ = 0;

	m_leftButtonDown = false;
    m_rightButtonDown = false;
	m_mouseDownX = -1;
	m_mouseDownY = -1;

	m_mouseX = -1;
	m_mouseY = -1;

    m_lightingOn = 1;
    
    m_lightAmbient[0] = 0.2;
    m_lightAmbient[1] = 0.2;
    m_lightAmbient[2] = 0.2;
    m_lightAmbient[3] = 1.0;

    m_lightDiffuse[0] = 0.6;
    m_lightDiffuse[1] = 0.6;
    m_lightDiffuse[2] = 0.6;
    m_lightDiffuse[3] = 1.0;

    m_lightSpecular[0] = 1.0;
    m_lightSpecular[1] = 1.0;
    m_lightSpecular[2] = 1.0;
    m_lightSpecular[3] = 1.0;
    
    m_matAmbient[0] = 1.0;
    m_matAmbient[1] = 1.0;
    m_matAmbient[2] = 1.0;
    m_matAmbient[3] = 1.0;
    
    m_matDiffuse[0] = 1.0;
    m_matDiffuse[1] = 1.0;
    m_matDiffuse[2] = 1.0;
    m_matDiffuse[3] = 1.0;
    
    m_matSpecular[0] = 1.0;
    m_matSpecular[1] = 1.0;
    m_matSpecular[2] = 1.0;
    m_matSpecular[3] = 1.0;

    m_matShininess = 25;
    
    m_camTheta = 5*PI/16;
    m_camPhi = PI/8;
}


void ModelViewer::MouseDown(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (m_leftButtonDown == false)
			{
				m_leftButtonDown = true;
				glutSetCursor(GLUT_CURSOR_NONE);

				m_mouseDownX = x;
				m_mouseDownY = y;

				m_mouseX = x;
				m_mouseY = y;
			}
		}
		else
		{
			m_leftButtonDown = false;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
	}
    else if(button == GLUT_RIGHT_BUTTON)
    {
		if (state == GLUT_DOWN)
		{
            if (m_rightButtonDown == false)
			{
				m_rightButtonDown = true;
				glutSetCursor(GLUT_CURSOR_NONE);

				m_mouseDownX = x;
				m_mouseDownY = y;

				m_mouseX = x;
				m_mouseY = y;
			}
		}
		else
		{
			m_rightButtonDown = false;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
	}
}

void ModelViewer::MouseMove(int x, int y)
{
	if (m_leftButtonDown)
	{
		m_camTheta += (x - m_mouseX) * 0.01;
		m_camPhi += (y - m_mouseY) * 0.01;

        if(m_camTheta > 2*PI)
            m_camTheta -= 2*PI;

        if(m_camTheta < 0)
            m_camTheta += 2*PI;
        
        if(m_camPhi > PI/2 - 0.1)
            m_camPhi = PI/2 - 0.1;

        if(m_camPhi < -PI/2 + 0.1)
            m_camPhi = -PI/2 + 0.1;
        

	    m_mouseX = x;
	    m_mouseY = y;

	    glutPostRedisplay();
	}
    else if(m_rightButtonDown)
    {
        m_camDistance += (y - m_mouseY) * 0.05;
        m_zoomSpinner->set_float_val(m_camDistance);

	    m_mouseX = x;
	    m_mouseY = y;

	    glutPostRedisplay();
    }
}

void ModelViewer::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, PolygonModes[m_polygonMode]);

	SetPerspective();
	PositionCamera();

	glMatrixMode(GL_MODELVIEW);

    float lightPosType[4] = {-1,1,1,0};

    if(m_lightingOn)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glLightfv(GL_LIGHT0,GL_POSITION,lightPosType);
        
        glLightfv(GL_LIGHT0,GL_AMBIENT,m_lightAmbient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,m_lightDiffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,m_lightSpecular);
        
        if(m_ambientOn)
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_matAmbient);
        else
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BLACK);

        if(m_diffuseOn)
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_matDiffuse);
        else
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLACK);

        if(m_specularOn)
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_matSpecular);
        else
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, BLACK);

        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_matShininess);

    }
    else
    {
        glDisable(GL_LIGHTING);
        glColor3fv(BLACK);
    }

    if(m_textureOn)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);


    glPushMatrix();

	glRotatef(m_rotateX, 1, 0, 0);
	glRotatef(m_rotateY, 0, 1, 0);
	glRotatef(m_rotateZ, 0, 0, 1);
	glTranslatef(m_translateX, m_translateY, m_translateZ);

	m_model.Render();


    glPopMatrix();
    
    
    glPushMatrix();
    glScalef(3.5f,3.5f,3.5f);
    

    // Render sphere to show light source direction
    glPushMatrix();
    glTranslatef(lightPosType[0],lightPosType[1],lightPosType[2]);
    gluSphere(m_quad,0.05,20,20);
    glPopMatrix();

    // Render framing box
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_LIGHTING);

    glBegin(GL_QUADS);
    {
        glColor3f(0.8,0.8,0.8);
        
        glVertex3f(1,1,1);
        glVertex3f(1,1,-1);
        glVertex3f(-1,1,-1);
        glVertex3f(-1,1,1);
        
        glVertex3f(1,-1,1);
        glVertex3f(1,-1,-1);
        glVertex3f(-1,-1,-1);
        glVertex3f(-1,-1,1);

        glVertex3f(1,1,1);
        glVertex3f(1,1,-1);
        glVertex3f(1,-1,-1);
        glVertex3f(1,-1,1);

        glVertex3f(-1,-1,-1);
        glVertex3f(-1,-1,1);
        glVertex3f(-1,1,1);
        glVertex3f(-1,1,-1);
    }
    glEnd();


    // Render x,y,z axes
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_LINES);
    {
        glColor3f(1,0,0); // x is red
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);

        glColor3f(0,1,0); // y is blue
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);

        glColor3f(0,0,1); // z is green
        glVertex3f(0,0,0);
        glVertex3f(0,0,1);
    }
    glEnd();

    glPopMatrix();
    glEnable(GL_DEPTH_TEST);


	glutSwapBuffers();
}

void ModelViewer::Reshape(int width, int height)
{
	m_aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}


void ModelViewer::Init()
{
	glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
    
    glClearColor(0.3,0.6,0.8,1.0);

    glEnable(GL_LIGHTING);

    glShadeModel(GL_FLAT);

	glEnable(GL_DEPTH_TEST);
    
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);

    m_model.Init();

	SetPerspective();
	PositionCamera();
}


void ModelViewer::SetPerspective()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    float DToR = 2*acos(0.0)/180;

    glFrustum(
        -m_nearPlane * sin((m_fovH/2)*DToR),
        m_nearPlane * sin((m_fovH/2)*DToR),
        -m_nearPlane * sin((m_fovV/2)*DToR),
        m_nearPlane * sin((m_fovV/2)*DToR),
        m_nearPlane,
        m_farPlane);
}


void ModelViewer::PositionCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
        m_camDistance * cos(m_camTheta) * cos(m_camPhi),
        m_camDistance * sin(m_camPhi),
        m_camDistance * sin(m_camTheta) * cos(m_camPhi),
        0, 0, 0, // looking at (0,0,0)
        0, 1, 0); // Up is (0,1,0)
}


void ModelViewer::Show(int argc, char **argv, string filePath)
{
    GlutView::Show(argc,argv);

    m_model = Model();
	m_model.LoadObjFile(filePath);

	float modelDepth = m_model.GetDepth();

	m_camDistance = modelDepth * 5;
    
	m_fovH = 40;
	m_fovV = 40;
	m_aspectRatio = 1;
	m_nearPlane = modelDepth * 2;
	m_farPlane = modelDepth * 10;

	int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	GLUI *glui = GLUI_Master.create_glui("OpenGL Demo Controls", 0,(screenWidth - 658-440)/2+640+20,(screenHeight - 768)/2);
    
    GLUI_Panel* group1 = new GLUI_Panel(glui,"",GLUI_PANEL_NONE);
    {
        GLUI_Panel* translationsPanel = new GLUI_Panel(group1,"Translations");
        {
            GLUI_Spinner* transXSpinner = new GLUI_Spinner(translationsPanel,"X",&m_translateX);
            transXSpinner->set_float_limits(-100,100);
            transXSpinner->set_speed(0.1);
            GLUI_Spinner* transYSpinner = new GLUI_Spinner(translationsPanel,"Y",&m_translateY);
            transYSpinner->set_float_limits(-100,100);
            transYSpinner->set_speed(0.1);
            GLUI_Spinner* transZSpinner = new GLUI_Spinner(translationsPanel,"Z",&m_translateZ);
            transZSpinner->set_float_limits(-100,100);
            transZSpinner->set_speed(0.1);
        }

        glui->add_column_to_panel(group1,false);

        GLUI_Panel* rotaionsPanel = new GLUI_Panel(group1,"Rotaions");
        {
            GLUI_Spinner* rotXSpinner = new GLUI_Spinner(rotaionsPanel,"X",&m_rotateX);
            rotXSpinner->set_float_limits(0,360,GLUI_LIMIT_WRAP);
            rotXSpinner->set_speed(0.5);
            GLUI_Spinner* rotYSpinner = new GLUI_Spinner(rotaionsPanel,"Y",&m_rotateY);
            rotYSpinner->set_float_limits(0,360,GLUI_LIMIT_WRAP);
            rotYSpinner->set_speed(0.5);
            GLUI_Spinner* rotZSpinner = new GLUI_Spinner(rotaionsPanel,"Z",&m_rotateZ);
            rotZSpinner->set_float_limits(0,360,GLUI_LIMIT_WRAP);
            rotZSpinner->set_speed(0.5);
        }
    }
    
    GLUI_Panel* group2 = new GLUI_Panel(glui,"",GLUI_PANEL_NONE);
    {
        GLUI_Panel* polygonModePanel = new GLUI_Panel(group2,"Polygon Mode");
        {
            GLUI_RadioGroup* polygonModeGroup = new GLUI_RadioGroup(polygonModePanel, &m_polygonMode);
            new GLUI_RadioButton(polygonModeGroup,"Points");
            new GLUI_RadioButton(polygonModeGroup,"Wireframe");
            new GLUI_RadioButton(polygonModeGroup,"Surface");
        }

        new GLUI_Checkbox(group2,"Textures On",&m_textureOn);

        glui->add_column_to_panel(group2,false);

        GLUI_Panel* cameraPanel = new GLUI_Panel(group2,"Camera");
        {   
            //GLUI_Spinner*
            m_zoomSpinner = new GLUI_Spinner(cameraPanel,"Zoom",&m_camDistance);
            m_zoomSpinner->set_float_limits(0,100);
            m_zoomSpinner->set_speed(-0.1);
        
            GLUI_Spinner* nearSpinner = new GLUI_Spinner(cameraPanel,"Near Plane",&m_nearPlane);
            nearSpinner->set_float_limits(0,100);
            nearSpinner->set_speed(0.1);

            GLUI_Spinner* farSpinner = new GLUI_Spinner(cameraPanel,"Far Plane",&m_farPlane);
            farSpinner->set_float_limits(0,100);
            farSpinner->set_speed(0.1);

            GLUI_Spinner* fovHSpinner = new GLUI_Spinner(cameraPanel,"FOV H",&m_fovH);
            fovHSpinner->set_float_limits(1,180);
            fovHSpinner->set_speed(0.5);

            GLUI_Spinner* fovVSpinner = new GLUI_Spinner(cameraPanel,"FOV V",&m_fovV);
            fovVSpinner->set_float_limits(1,180);
            fovVSpinner->set_speed(0.5);

        }
    }

    GLUI_Panel* lightingPanel = new GLUI_Panel(glui,"Lighting");
    {
        new GLUI_Checkbox(lightingPanel,"On",&m_lightingOn);

        GLUI_Panel* groupPanel = new GLUI_Panel(lightingPanel,"",GLUI_PANEL_NONE);
        {
            GLUI_Panel* lightPanel = new GLUI_Panel(groupPanel,"Light");
            {
                GLUI_Panel* ambientPanel = new GLUI_Panel(lightPanel,"Ambient");
                {
                    GLUI_Spinner* redSpinner = new GLUI_Spinner(ambientPanel,"Red",&m_lightAmbient[0]);
                    redSpinner->set_float_limits(0,1);
                    GLUI_Spinner* greenSpinner = new GLUI_Spinner(ambientPanel,"Green",&m_lightAmbient[1]);
                    greenSpinner->set_float_limits(0,1);
                    GLUI_Spinner* blueSpinner = new GLUI_Spinner(ambientPanel,"Blue",&m_lightAmbient[2]);
                    blueSpinner->set_float_limits(0,1);
                    //GLUI_Spinner* alphaSpinner = new GLUI_Spinner(ambientPanel,"Alpha",&m_lightAmbient[3]);
                    //alphaSpinner->set_float_limits(0,1);
                }

                GLUI_Panel* diffusePanel = new GLUI_Panel(lightPanel,"Diffuse");
                {
                    GLUI_Spinner* redSpinner = new GLUI_Spinner(diffusePanel,"Red",&m_lightDiffuse[0]);
                    redSpinner->set_float_limits(0,1);
                    GLUI_Spinner* greenSpinner = new GLUI_Spinner(diffusePanel,"Green",&m_lightDiffuse[1]);
                    greenSpinner->set_float_limits(0,1);
                    GLUI_Spinner* blueSpinner = new GLUI_Spinner(diffusePanel,"Blue",&m_lightDiffuse[2]);
                    blueSpinner->set_float_limits(0,1);
                    //GLUI_Spinner* alphaSpinner = new GLUI_Spinner(diffusePanel,"Alpha",&m_lightDiffuse[3]);
                    //alphaSpinner->set_float_limits(0,1);
                }

                GLUI_Panel* specularPanel = new GLUI_Panel(lightPanel,"Specular");
                {
                    GLUI_Spinner* redSpinner = new GLUI_Spinner(specularPanel,"Red",&m_lightSpecular[0]);
                    redSpinner->set_float_limits(0,1);
                    GLUI_Spinner* greenSpinner = new GLUI_Spinner(specularPanel,"Green",&m_lightSpecular[1]);
                    greenSpinner->set_float_limits(0,1);
                    GLUI_Spinner* blueSpinner = new GLUI_Spinner(specularPanel,"Blue",&m_lightSpecular[2]);
                    blueSpinner->set_float_limits(0,1);
                    //GLUI_Spinner* alphaSpinner = new GLUI_Spinner(specularPanel,"Alpha",&m_lightSpecular[3]);
                    //alphaSpinner->set_float_limits(0,1);
                }
            }

            glui->add_column_to_panel(groupPanel,false);
            
            GLUI_Panel* materialPanel = new GLUI_Panel(groupPanel,"Material");
            {
                GLUI_Panel* ambientPanel = new GLUI_Panel(materialPanel,"Ambient");
                {
                    new GLUI_Checkbox(ambientPanel,"On",&m_ambientOn);
                    GLUI_Spinner* redSpinner = new GLUI_Spinner(ambientPanel,"Red",&m_matAmbient[0]);
                    redSpinner->set_float_limits(0,1);
                    GLUI_Spinner* greenSpinner = new GLUI_Spinner(ambientPanel,"Green",&m_matAmbient[1]);
                    greenSpinner->set_float_limits(0,1);
                    GLUI_Spinner* blueSpinner = new GLUI_Spinner(ambientPanel,"Blue",&m_matAmbient[2]);
                    blueSpinner->set_float_limits(0,1);
                    //GLUI_Spinner* alphaSpinner = new GLUI_Spinner(ambientPanel,"Alpha",&m_matAmbient[3]);
                    //alphaSpinner->set_float_limits(0,1);
                }

                GLUI_Panel* diffusePanel = new GLUI_Panel(materialPanel,"Diffuse");
                {
                    new GLUI_Checkbox(diffusePanel,"On",&m_diffuseOn);
                    GLUI_Spinner* redSpinner = new GLUI_Spinner(diffusePanel,"Red",&m_matDiffuse[0]);
                    redSpinner->set_float_limits(0,1);
                    GLUI_Spinner* greenSpinner = new GLUI_Spinner(diffusePanel,"Green",&m_matDiffuse[1]);
                    greenSpinner->set_float_limits(0,1);
                    GLUI_Spinner* blueSpinner = new GLUI_Spinner(diffusePanel,"Blue",&m_matDiffuse[2]);
                    blueSpinner->set_float_limits(0,1);
                    //GLUI_Spinner* alphaSpinner = new GLUI_Spinner(diffusePanel,"Alpha",&m_matDiffuse[3]);
                    //alphaSpinner->set_float_limits(0,1);
                }

                GLUI_Panel* specularPanel = new GLUI_Panel(materialPanel,"Specular");
                {
                    new GLUI_Checkbox(specularPanel,"On",&m_specularOn);
                    GLUI_Spinner* redSpinner = new GLUI_Spinner(specularPanel,"Red",&m_matSpecular[0]);
                    redSpinner->set_float_limits(0,1);
                    GLUI_Spinner* greenSpinner = new GLUI_Spinner(specularPanel,"Green",&m_matSpecular[1]);
                    greenSpinner->set_float_limits(0,1);
                    GLUI_Spinner* blueSpinner = new GLUI_Spinner(specularPanel,"Blue",&m_matSpecular[2]);
                    blueSpinner->set_float_limits(0,1);
                    //GLUI_Spinner* alphaSpinner = new GLUI_Spinner(specularPanel,"Alpha",&m_matSpecular[3]);
                    //alphaSpinner->set_float_limits(0,1);

                    GLUI_Spinner* shinySpinner = new GLUI_Spinner(specularPanel,"Shininess",&m_matShininess);
                    shinySpinner->set_float_limits(0,255);
                }
                

            }
        
        }
        
    }


    glui->set_main_gfx_window( m_windowId );

	Init();

	glutMainLoop();
}

