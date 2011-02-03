#ifndef __task6_header__
#define __task6_header__

#include "user/task5.h"
#include "object/string.h"

class Task6 : public Task5{

enum Parameters
{
	cmdX = 0,
	cmdY = 20
};

class Cmd : public Application{
	enum Parameters{
		bufferSize=128,
		appNum=3
	};

	unsigned short x,y;
	char *buffer;
	StaticString inputBuffer;
	Application* apps[3];
	const char* appNames[3];
	bool running[3];
	
	void clearBuffer();
	void parseBuffer();
	void putChar(char c);
	void startApp(unsigned int i);
	void stopApp(unsigned int i);

public:
	Cmd(void* tos, unsigned short x, unsigned short y,
		Application& app0, const char* app0Name,
		Application& app1, const char* app1Name,
		Application& app2, const char* app2Name);
	virtual void action();
};

Cmd cmd;

static unsigned int space;
static unsigned char cmdStack[stackSize];

public:
	Task6();
	virtual void action();
};

#endif
