#ifndef __organizer_header__
#define __organizer_header__

#include "thread/scheduler.h"
#include "thread/customer.h"
#include "meeting/waitingroom.h"

/**\brief Organization of waiting Customers
 *
 * This class handles the blocking and the wakeup of Customers.
 **/
class Organizer : public Scheduler
{
public:
	/**\brief blocks the currently active Customer
	 *
	 * The Customer will be put in the supplied Waitingroom to wait for a
	 * condition dependant on the Waitingroom
	 *
	 * \todo write implementation
	 *
	 * \param waitingroom the waitingroom to wait in
	 **/
	void block(Waitingroom& waitingroom);

	/**\brief wakes the supplied Customer up
	 *
	 * The supplied Customer will be put to the end of the ready queue of the scheduler.
	 *
	 * \todo write implementation
	 *
	 * \param customer The Customer to be woken up
	 **/
	void wakeup(Customer& customer);

	/**\brief kill a Customer
	 *
	 * This method removes the supplied Customer from either the ready queue or
	 * the waitingroom queue he is currently waiting in.
	 *
	 * \todo write implementation
	 *
	 * \param that The Customer to kill
	 **/
	void kill(Customer& that);

	/**\brief return the currently active Customer
	 *
	 * \return the currently active Customer
	 **/
    Customer* active() const{
		return static_cast<Customer*>(Scheduler::active());
    }
};

#endif
