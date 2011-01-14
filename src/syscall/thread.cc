/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                             T H R E A D                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#include "syscall/thread.h"
#include "thread/scheduler.h"

extern Scheduler scheduler;

void Thread::resume() {
  scheduler.resume();
}

void Thread::exit() {
  scheduler.exit();
}
