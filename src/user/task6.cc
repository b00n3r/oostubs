#include "user/task6.h"
#include "device/cgastr.h"
#include "syscall/guarded_scheduler.h"
#include "syscall/guarded_keyboard.h"

extern CGA_Stream kout;
extern Guarded_Scheduler scheduler;
extern Guarded_Keyboard keyboard;

unsigned char Task6::cmdStack[];

Task6::Cmd::Cmd(void* tos,
				unsigned short x,
				unsigned short y,
				Application& app0,
				const char* app0Name,
				Application& app1,
				const char* app1Name,
				Application& app2,
				const char* app2Name) 
				: Application(tos), inputBuffer(buffer, bufferSize){
	this->x=x;
	this->y=y;
	this->apps[0]=&app0;
	this->apps[1]=&app1;
	this->apps[2]=&app2;
	this->appNames[0]=app0Name;
	this->appNames[1]=app1Name;
	this->appNames[2]=app2Name;
	for(unsigned int i=0;i<appNum;i++)
		this->running[i]=false;
}

void Task6::Cmd::clearBuffer(){
	Secure s;
	kout.flush();
	kout.setpos(x,y);
	for(unsigned int i=0;i<inputBuffer.length();i++)
		kout << ' ';
	kout.flush();
	kout.setpos(x,y);
	inputBuffer="";
}

void Task6::Cmd::parseBuffer(){
	
	unsigned int i;
	short pos;

	{
		Secure s;
		kout.setpos(0,y+2);
		for(unsigned int i=0;i<80;i++)
			kout << ' ';
		kout.flush();
	}

	if(inputBuffer.find("tasks")>=0)
	{
		Secure s;
		kout.setpos(0,y+2);
		kout << "Available tasks: ";
		for(unsigned short i=0;i<appNum;i++)
			kout << appNames[i] << ' ';
		kout.flush();
		return;
	}

	if((pos=inputBuffer.find("start"))>=0)
	{
		for(i=0;i<appNum;i++)
			if(inputBuffer.find(appNames[i], pos+6)>=0)
			{
				if(!running[i])
				{
					scheduler.ready(*apps[i]);
					running[i]=true;
				}
				else
				{
					Secure s;
					kout.setpos(0,y+2);
					kout << "Task already running!";
					kout.flush();
				}
				return;
			}
	}

	if((pos=inputBuffer.find("stop"))>=0)
	{
		for(i=0;i<appNum;i++)
			if(inputBuffer.find(appNames[i], pos+5)>=0)
			{
				if(running[i])
				{
					scheduler.kill(*apps[i]);
					running[i]=false;
				}
				else
				{
					Secure s;
					kout.setpos(0,y+2);
					kout << "Task not running!";
					kout.flush();
				}
				return;
			}
	}

	Secure s;
	kout.setpos(0,y+2);
	kout << "commands: start stop tasks";
	kout.flush();

}

void Task6::Cmd::startApp(unsigned int i){
	if(!running[i])
		scheduler.ready(*apps[i]);
}

void Task6::Cmd::stopApp(unsigned int i){
	if(running[i])
		scheduler.kill(*apps[i]);
}

void Task6::Cmd::putChar(char c){
	inputBuffer+=c;

	Secure s;
	kout.flush();
	kout.setpos(x,y);
	kout << inputBuffer;
	if(c=='\b')
		kout << ' ';
	kout.flush();
}

void Task6::Cmd::action(){
	{
	Secure s;
	kout.flush();
	kout.setpos(x, y);
	kout << "oostubs:$ ";
	kout.flush();
	kout.getpos(x,y);
	for(unsigned int i=0;i<bufferSize;i++)
		kout << ' ';
	kout.flush();
	kout.setpos(x, y);
	}
	while(true)
	{
		char c=keyboard.getkey().ascii();
		if(c=='\n')
		{
			parseBuffer();
			clearBuffer();
		}
		else
			putChar(c);
	}
}

Task6::Task6() : Task5(), cmd(cmdStack+stackSize, cmdX, cmdY,
							  counter1, "counter1",
							  counter2, "counter2",
							  rotCursor, "rotatingCursor"){
	kout.clear();
	kout.setpos(31,1);
	kout << "OOStuBs - Task 6" << endl << endl;
}

void Task6::action(){
	scheduler.ready(cmd);
}
