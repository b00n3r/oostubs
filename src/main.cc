/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                              M A I N                                      *
 *                                                                           *
 *---------------------------------------------------------------------------*/

/* INCLUDES */

#include "machine/multiboot.h"
#include "guard/guard.h"
#include "device/cgastr.h"
#include "machine/pic.h"
#include "machine/cpu.h"
#include "machine/plugbox.h"
#include "device/keyboard.h"
#include "syscall/guarded_scheduler.h"
#include "device/watch.h"

#include "user/task5.h"

/* GLOBAL OBJECTS */

Guard guard;
CGA_Stream kout;
PIC pic;
CPU cpu;
Plugbox plugbox;
Keyboard keyboard;
Guarded_Scheduler scheduler;
Watch watch(12000); // ca 100 Hz (1/100 * 10^9 / 838)

/* METHODS  */

extern "C" void kernel(uint32_t magic, const Multiboot_Info* addr);

/** \brief kernel entry point
 *
 * This is the entry point of the operating system.  If this function returns
 * all interrupts will be disabled and the cpu will be halted.
 *
 * \param magic bootloader magic value
 * \param addr address of multiboot info structure
 **/

void kernel(uint32_t magic, const Multiboot_Info* addr){
    kout.clear();

    Task5 task;
    
    keyboard.plugin();
    watch.windup();
    
    scheduler.ready(task);

    scheduler.schedule();
}
