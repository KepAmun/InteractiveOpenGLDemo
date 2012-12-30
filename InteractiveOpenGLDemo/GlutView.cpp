

#include "GlutView.h"


GlutView* GlutView::m_instance;


GlutView::GlutView()
{
    m_title = "";
}


void GlutView::Show(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
	int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowPosition((screenWidth - 658 - 440)/2, (screenHeight - 685)/2);
	glutInitWindowSize(640, 640);

    m_windowId = glutCreateWindow(m_title.c_str());

    glutIdleFunc(idleRelay);
	glutDisplayFunc(displayRelay);
	glutReshapeFunc(reshapeRelay);
	glutKeyboardFunc(keyboardRelay);
	glutMouseFunc(mouseDownRelay);
	glutMotionFunc(mouseMoveRelay);
}

GlutView::~GlutView(void)
{
}

void GlutView::idleRelay()
{
	m_instance->Idle();
}

void GlutView::timerRelay(int value)
{
    m_instance->Timer(value);
}

void GlutView::displayRelay()
{
	m_instance->Display();
}

void GlutView::reshapeRelay(int width, int height)
{
	m_instance->Reshape(width, height);
}

void GlutView::keyboardRelay(unsigned char key, int x, int y)
{
	m_instance->Keyboard(key, x, y);
}

void GlutView::mouseDownRelay(int button, int state, int x, int y)
{
	m_instance->MouseDown(button, state, x, y);
}

void GlutView::mouseMoveRelay(int x, int y)
{
	m_instance->MouseMove(x, y);
}


void GlutView::Idle()
{

}

void GlutView::Timer(int value)
{

}

void GlutView::Display()
{

}

void GlutView::Reshape(int width, int height)
{

}

void GlutView::Keyboard(unsigned char key, int x, int y)
{

}

void GlutView::MouseDown(int button, int state, int x, int y)
{

}

void GlutView::MouseMove(int x, int y)
{

}
