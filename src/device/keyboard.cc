/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                            K E Y B O A R D                                *
 *                                                                           *
 *---------------------------------------------------------------------------*/

/* INCLUDES */
#include "device/keyboard.h"
#include "machine/io_port.h"
#include "device/cgastr.h"
#include "machine/pic.h"
#include "machine/plugbox.h"

/* GLOBAL VARIABLS */
extern CGA_Stream kout;
extern PIC pic;
extern Plugbox plugbox;

/* METHODS */
void Keyboard::plugin () {
    keyCount = 0;
    
    plugbox.assign(Plugbox::keyboard, *this);
	pic.allow(PIC::keyboard);
}

bool Keyboard::prologue () {
    Key k = key_hit();
    
    if(k.valid()){
        if (k.alt() && k.ctrl() && k.scancode()==83) {
            reboot();
        } else {
            if (keyCount != 1023) {
                tmpKey[keyCount++] = k;
            }
        }
	}
	
	return k.valid();
}

void Keyboard::epilogue() {
	semaphore.signal();
}

Key Keyboard::getkey() {
    semaphore.wait();
    
    return tmpKey[--keyCount];
} 
