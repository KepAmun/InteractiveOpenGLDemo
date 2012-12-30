#pragma once

#include <string>
#include <GL/glut.h>

using namespace std;

class GlutView
{
protected:
	static GlutView* m_instance;
    static GlutView* GetInstance();

    int m_windowId;
    string m_title;
    
    GlutView();

public:
	void Show(int argc, char **argv);
    
	static void idleRelay();
	static void timerRelay(int value);
	static void displayRelay();
	static void reshapeRelay(int width, int height);
	static void keyboardRelay(unsigned char key, int x, int y);
	static void mouseDownRelay(int button, int state, int x, int y);
	static void mouseMoveRelay(int x, int y);

	virtual void Idle();
	virtual void Timer(int value);
	virtual void Display();
	virtual void Reshape(int width, int height);
	virtual void Keyboard(unsigned char key, int x, int y);
	virtual void MouseDown(int button, int state, int x, int y);
	virtual void MouseMove(int x, int y);

    ~GlutView(void);
};
