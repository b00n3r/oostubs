/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                                G U A R D                                  *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __Guard_include__
#define __Guard_include__

#include "guard/locker.h"
#include "guard/gate.h"
#include "object/queue.h"
#include "object/chain.h"

/** \brief Interrupt synchronisation handler
 *
 * Guard enables the operating system to synchroniste actions of interrupt 
 * handlers for critical sections that are secured using the lock of the 
 * Guard object.
 */
class Guard : public Locker {
  /** \brief queue of waiting epilogues **/
   Queue queue;

  /** \brief remove a queued epilogue from the queue
   *
   * This method has to be called secured to ensure that the structure of the
   * queue stays consistent.
   *
   * @return a pointer to the Gate object implementing the next epilogue, or
   * NULL if queue is empty.
   */
	Gate* remove_epilogue();

public:
  /** \brief leave the critical section
   *
   * Waiting epilogues can be processed now.
   **/ 
	void leave();

  /** \brief try to execute epilogue
   *
   * If possible the epilogue is processed right away but if the critical
   * section used for the epilogue is locked the epilogue has to be queued for
   * later processing.
   *
   * @param item pointer to the Gate object implementing the epilogue.
   **/
	void relay(Gate* item);
};

#endif
