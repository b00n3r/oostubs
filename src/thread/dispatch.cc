/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                          D I S P A T C H E R                              *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#include "thread/dispatch.h"

Dispatcher::Dispatcher() {
  c_active = 0;
}

void Dispatcher::go(Entrant& first) {
  if(!c_active) {
    *c_active = first;
    toc_go(&(first.savregs));
  }
}

void Dispatcher::dispatch(Entrant& next) {
  Entrant *running = c_active;
  *c_active = next;
  toc_switch(&((*running).savregs), &(next.savregs));
}

Entrant* Dispatcher::active() const {
  return c_active;
}
