#include "thread/organizer.h"
#include "guard/guard.h"

extern Guard guard;

void Organizer::block(Waitingroom& waitingroom) {  
  Entrant* ent;

  (*active()).waiting_in(&waitingroom);
  waitingroom.enqueue(active());

  do {
    guard.leave();
    guard.enter();
    ent = (Entrant*) queue.dequeue();
  } while (ent == 0);

  dispatch(*ent);
}

void Organizer::wakeup(Customer& customer) {
  (*customer.waiting_in()).remove(customer);
  customer.waiting_in(0);
  ready(customer);
}

void Organizer::kill(Customer& that) {
  Waitingroom* waitingroom = that.waiting_in();

  if (waitingroom) {
    (*waitingroom).remove(that);
  } else {
    Scheduler::kill(&that);
  }
}
