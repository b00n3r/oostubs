#ifndef __waitingroom_header__
#define __waitingroom_header__

#include "object/queue.h"
#include "thread/customer.h"

/**\brief Base class of all waiting rooms
 *
 * Every class implementing a ressource on which access blocking is possible
 * should inherit from this class.  This class contains the necessary
 * functionality to kill currently blocked Customers and to wake up all
 * Customers on destruction of the ressource.
 **/
class Waitingroom : public Queue { public:

		/**\brief virtual destructor
		 *
		 * Wake up all the currently blocked Customers of this %Waitingroom.
		 **/
		virtual ~Waitingroom();

		/**\brief remove a customer from the blocked queue
		 *
		 * \param that the Customer to be removed
		 **/
		virtual void remove(Customer& that);
};

#endif
