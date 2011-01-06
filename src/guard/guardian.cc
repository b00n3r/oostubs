/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                              G U A R D I A N                              *
 *                                                                           *
 *---------------------------------------------------------------------------*/

/* INCLUDES */
#include "machine/pic.h"
#include "machine/plugbox.h"
#include "guard/guard.h"
#include "machine/cpu.h"

extern PIC pic;
extern Plugbox plugbox;
extern Guard guard;
extern CPU cpu;

/* METHODS  */
extern "C" void guardian (unsigned short slot);

/** \brief Entry point for interrupts
 *
 * @param slot number of occurred interrupt
 */
void guardian (unsigned short slot) {
  if (slot < 256) {
    Gate *g = &plugbox.report(slot);
	
    if (g->prologue()) {
      guard.relay(g);
    }
	
    pic.ack();
  }
}
