/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                             C G A _ S C R E E N                           *
 *                                                                           *
 *---------------------------------------------------------------------------*/
 
#include "machine/cgascr.h"
#include "machine/io_port.h"

unsigned char* ausgabe;
static IO_Port cga_index(0x3d4);
static IO_Port cga_data(0x3d5);

CGA_Screen::CGA_Screen() {
    ausgabe = (unsigned char*) 0xB8000;
    clear();
}

CGA_Screen::~CGA_Screen() {
}

void CGA_Screen::setpos(unsigned short x, unsigned short y) {
    if (x >= 80 || y >= 25) {
        y += (int) (x / 80);
        x = x % 80;
        
        if (y >= 25) {
          for (unsigned int i = 0; i <= y % 25; i++) {
            scrollup();
          }
        
          y = 24;
        }
    }
    
    cga_index.outb(14);
    cga_data.outb(x);

    cga_index.outb(15);
    cga_data.outb(y);
}

void CGA_Screen::getpos(unsigned short& x, unsigned short& y) const {
    // high
    cga_index.outb(14);
    x = cga_data.inb();
    
    // low
    cga_index.outb(15);
    y = cga_data.inb();
}

void CGA_Screen::show(unsigned short x, unsigned short y, char c, unsigned char attrib) {
    if (x < 80 && y < 25) {
        unsigned short p = 2 * x + 160 * y;
    
        ausgabe[p] = c;
        ausgabe[p+1] = attrib;
    }
}

void CGA_Screen::print(const char* string, unsigned int n, unsigned char attrib) {
    unsigned short x;
    unsigned short y;
        
    getpos(x, y);
    
    for (unsigned int i = 0; i < n; i++) {
        if (string[i] == '\n') {
           setpos(0, y+1);
        } else {
            show(x, y, string[i], attrib);
            setpos(++x, y);
            getpos(x, y);
        }
    }
}

void CGA_Screen::scrollup() {
    for (unsigned int i = 80; i < 80*25*2; i = i + 2) {
        ausgabe[i-160] = ausgabe[i];
        ausgabe[i-160+1] = ausgabe[i+1];
    }
    
    for (unsigned int i = 80*24*2; i < 80*25*2; i++) {
        ausgabe[i] = 0;
    }
    
    unsigned short x;
    unsigned short y;
        
    getpos(x, y);
    
    if (y != 0) setpos(x, y-1);
}

void CGA_Screen::clear() {
    for (unsigned int i = 0; i < 80*25*2; i++) {
        ausgabe[i] = 0;
    }
    
    setpos(0, 0);
}
