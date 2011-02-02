#ifndef __semaphore_header__
#define __semaphore_header__

#include "meeting/semaphore.h"
#include "meeting/waitingroom.h"

/**\brief Counting semaphore representation
 *
 * This class represents a counting semaphore. It is initialized with a certain
 * value and provides operations to aquire and release ressources. If all
 * ressources are aquired any additional aquiring will block the currently
 * active Customer until ressources are released.
 **/
class Semaphore : public Waitingroom
{
	private:
		/** \brief internal representation of the semaphore counter
		 *
		 * \todo write declaration
		 **/
		int counter;

	public:
		/**\brief Construct a new semaphore with initial value
		 *
		 * \todo write implementation
		 *
		 * \param value initial value of the semaphore
		 **/
		Semaphore(unsigned int value);

		/**\brief virtual destructor to wake up blocked Customers**/
		virtual ~Semaphore(){}

		/**\brief aquire a ressource from this semaphore
		 *
		 * This method can block if no more free ressources are available.  The
		 * currently active Customer will be suspended until a ressource is
		 * freed by the signal() or v() call.
		 *
		 * \todo write implementation
		 **/
		void p();

		/**\brief release a ressource from this semaphore
		 *
		 * This method readies a Customer if there is one currently waiting for
		 * this semaphore.
		 *
		 * \todo write implementation
		 **/
		void v();

		/**\copydoc p()**/
		void wait(){p();}

		/**\copydoc v()**/
		void signal(){v();}
};

#endif
