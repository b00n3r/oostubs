#include "thread/kickoff.h"
#include "guard/guard.h"

extern Guard guard;

void kickoff(Coroutine* object) {
    guard.leave();
    ((Coroutine*)object)->action();
}
