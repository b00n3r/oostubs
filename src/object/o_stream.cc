/*****************************************************************************
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                            O _ S T R E A M                                *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#include "object/o_stream.h"

O_Stream::O_Stream() {
    base = dec;
}

O_Stream::~O_Stream() {
}

O_Stream& O_Stream::operator << (char value) {
    put(value);
  
    return *this;
}

O_Stream& O_Stream::operator << (unsigned char value) {
    put(value);

    return *this;
}

O_Stream& O_Stream::operator << (char* value) {
    while (*value != 0)
    	put(*value++);
  
    return *this;
}

O_Stream& O_Stream::operator << (const char* value) {
    *this << const_cast<char*> (value);
    
    return *this;
}

O_Stream& O_Stream::operator << (unsigned short value) {
    *this << static_cast<unsigned long>(value);
    
    return *this;
}

O_Stream& O_Stream::operator << (short value) {
    *this << static_cast<long>(value);
    
    return *this;
}

O_Stream& O_Stream::operator << (unsigned int value) {
    *this << static_cast<unsigned long>(value);
    
    return *this;
}

O_Stream& O_Stream::operator << (int value) {
    *this << static_cast<long>(value);
    
    return *this;
}

/**
 * \todo Remove Recursion
 */
O_Stream& O_Stream::operator << (unsigned long value) {
    if (value < base) {
        if (value < 10) {
            put( (char) ('0' + value) );
        } else {
            put( (char) ('A' + value - 10) );
        }
    } else {
        *this << (unsigned long) (value / base);
        *this << (unsigned long) (value % base);
    }
    
    return *this;
}

O_Stream& O_Stream::operator << (long value) {
    if (value < 0) {
        *this << '-';
        value *= -1;
    }
    
    *this << (unsigned long) value;
    
    return *this;
}

O_Stream& O_Stream::operator << (void* value) {
    Base tmp = base;
    base = hex;
    
    *this << (unsigned long) value;
    
    base = tmp;

    return *this;
}

O_Stream& O_Stream::operator << (O_Stream& (*f) (O_Stream&)) {
    return (*f)(*this);
}

O_Stream& endl(O_Stream &out) {
    out << '\n';
    
    return out;
}
 
O_Stream& bin(O_Stream &out) {
    out.base = O_Stream::bin;
    return out;
}
 
O_Stream& oct(O_Stream &out) {
    out.base = O_Stream::oct;
    return out;
}

O_Stream& dec(O_Stream &out) {
    out.base = O_Stream::dec;
    return out;
}

O_Stream& hex(O_Stream &out) {
    out.base = O_Stream::hex;
    return out;
}
