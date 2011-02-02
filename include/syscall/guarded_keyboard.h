#ifndef __guarded_keyboard__
#define __guarded_keyboard__

#include "device/keyboard.h"
#include "guard/secure.h"
#include "machine/multiboot.h"

/** \brief Extended Keyboard Driver
 *
 * This class provides a secure Interface to the Keyboard Driver, that provides
 * keys to the Userspace Application.
 *
 **/
class Guarded_Keyboard : protected Keyboard{
public:
	/** \brief get a new Key from the keyboard
	 *
	 * If there are no new keys, the method will block the currently active
	 * Customer until one is available.
	 *
	 * \todo write implementation
	 *
	 * \return the next key, the user has hit
	 **/
	Key getkey(){
	  Secure secure;
	  return Keyboard::getkey();
	}

	/** \brief register the Keyboard for interrupt handling
	 *
	 * This method should only be called by kernel.
	 *
	 * \todo write implementation
	 **/
	void plugin(){
	  Secure secure;
	  Keyboard::plugin();
	}
};

#endif
