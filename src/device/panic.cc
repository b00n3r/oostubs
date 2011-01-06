/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                                 P A N I C                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*/

/* INCLUDES */
#include "device/panic.h"
#include "machine/cpu.h"
#include "device/cgastr.h"

/* GLOBAL VARIABLES */
extern CPU cpu;
extern CGA_Stream kout;

bool Panic::prologue () {
    cpu.disable_int();

    kout << "kernel panic" << endl;

	cpu.halt();
	
	return false;
}

void Panic::epilogue() {
    kout << "\"never called\" you noob" << endl;
}
