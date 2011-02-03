#include "meeting/semaphore.h"
#include "thread/organizer.h"

extern Organizer scheduler;

Semaphore::Semaphore(unsigned int value) {
  counter = value;
}

// wait
void Semaphore::p() {
  counter--;

  if (counter <= 0) {
    scheduler.block(*this);
  }
}

// signal
void Semaphore::v() {
  if (counter < 0) {
    Customer* customer = (Customer*) dequeue();

    if (customer) {
      scheduler.wakeup(*customer);
    } else {
      counter++;
    }
  } else {
    counter++;
  }
}
