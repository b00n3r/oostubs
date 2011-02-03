#include "meeting/waitingroom.h"
#include "thread/organizer.h"

extern Organizer scheduler;

Waitingroom::~Waitingroom() {
  Customer* customer = (Customer*) dequeue();
  
  if (customer) {
    scheduler.wakeup(*customer);
  }
}

void Waitingroom::remove(Customer& that) {
  Queue::remove(&that);
}
