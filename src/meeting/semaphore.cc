#include "meeting/semaphore.h"
#include "syscall/guarded_scheduler.h"

extern Guarded_Scheduler scheduler;

Semaphore::Semaphore(unsigned int value) {
  counter = value;
}

void Semaphore::p() {
  if (counter > 0) {
    counter--;
  } else {
    scheduler.block((Waitingroom&) *this);
  }
}

void Semaphore::v() {
  if (counter < 1) {
    Customer* customer = (Customer*) dequeue();

    if (customer) {
      scheduler.wakeup(*customer);
    }
  } else {
    counter++;
  }
}
