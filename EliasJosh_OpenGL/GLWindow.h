#ifndef _GL_WINDOW_H
#define _GL_WINDOW_H

class GLWindow
{
public:
	static GLWindow& Instance() { static GLWindow glWin; return glWin; }

	void Initialize(int,int);

private:
	GLWindow();

};

#endif