/*****************************************************************************
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                       S T R I N G B U F F E R                             *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#include "object/strbuf.h"

/* ToDo: insert sourcecode */


Stringbuffer::Stringbuffer() {
    length = 0;
}

Stringbuffer::~Stringbuffer() {
}

void Stringbuffer::put(char c) {
    buffer[length++] = c;
    
    if (length == max || c == '\n')
      flush();
}
