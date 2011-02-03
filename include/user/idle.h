#ifndef __idle_header__
#define __idle_header__

#include "user/appl.h"
#include "machine/cpu.h"

extern CPU cpu;

/** \brief idle application
 *
 * Halt until interrupted.
 **/
class Idle : public Application {
protected:
    /** \brief size of the stack **/
    const static unsigned int stackSize=1024;
    /** \brief stack for the application **/
    unsigned char stack[stackSize];

public:
    /** \brief Default Constructor **/
	Idle() : Application(stack+stackSize) {}

    /** \brief halt until interrupted **/
	virtual void action() {
	  while (true) {
	    cpu.enable_int();
	    cpu.halt();
	  }
	}
};

#endif
