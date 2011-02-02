#include "thread/organizer.h"

void Organizer::block(Waitingroom& waitingroom) {
  (*active()).waiting_in(&waitingroom);
  waitingroom.enqueue(active());
  
  Entrant* ent = (Entrant*) queue.dequeue();
  
  if(ent){
    dispatch(*ent);
  }
}

void Organizer::wakeup(Customer& customer) {
  (*customer.waiting_in()).remove(customer);
  customer.waiting_in(0);
  ready(customer);
}

void Organizer::kill(Customer& that) {
  Waitingroom* wr = that.waiting_in();

  if (wr) {
    (*wr).remove(that);
  } else {
    Scheduler::kill(&that);
  }
}
