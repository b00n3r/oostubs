/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                                  P I T                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#include "machine/pit.h"
#include "machine/io_port.h"

PIT::PIT (unsigned short us) {
  interval(us);
}

unsigned short PIT::interval () {
  return interv;
}

void PIT::interval(unsigned short us) {
  IO_Port controlp (0x43);
  IO_Port rwport (0x40);
  
  interv = us/838 * 1000;
  
  /*
      0: binäre Zählung von 16 Bit
    1-3: Modus 2
    4-5: niederwertiges, anschließend höherwertiges Zählerbyte
    6-7: Zähler 0
  
    7 6 5 4 3 2 1 0
    0 0 1 1 0 1 0 0 = 52 = 0x34
  */
  controlp.outb(0x34);
  
  // low
  rwport.outb(us & 0xff);
  // high
  rwport.outb(us >> 8);
}
