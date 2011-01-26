#ifndef __customer_header__
#define __customer_header__

#include "thread/entrant.h"

/* Forward declaration to avoid circular dependancies**/
class Waitingroom;

/**\brief Extension of a Thread
 *
 * This extension of Thread can be put in a blocking state, where operating is suspended until a certain condition is met.
 **/
class Customer : public Entrant
{
	private:
		/**\brief Waitingroom, the customer is currently waiting in
		 *
		 * if the Customer is not waiting, this field should contain NULL
		 **/
		Waitingroom* room;

	public:
		/**\brief Constructor passing top of stack pointer
		 *
		 * \param tos the top of stack, the Customer should use
		 **/
		Customer(void* tos) : Entrant(tos), room(0){}

	private:
		/**\brief set the Waitingroom the %Customer is waiting in
		 *
		 * \param room the Waitingroom to wait in
		 **/
		void waiting_in(Waitingroom *room){
			this->room=room;
		}
	
	public:
		/**\brief get the Waitingroom the %Customer is waiting in
		 *
		 * \return the actual Waitingroom
		 **/
		Waitingroom* waiting_in() const{
			return room;
		}

	/* friend declaration to access the room variable from the organizer */
	friend class Organizer;
};

#endif
