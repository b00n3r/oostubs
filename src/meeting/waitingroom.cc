#include "meeting/waitingroom.h"
#include "syscall/guarded_scheduler.h"

extern Guarded_Scheduler scheduler;

Waitingroom::~Waitingroom() {
  Customer* customer = (Customer*) dequeue();
  
  if (customer) {
    scheduler.wakeup(*customer);
  }
}

void Waitingroom::remove(Customer& that) {
  Queue::remove(&that);
}
