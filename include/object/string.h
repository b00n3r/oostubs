#ifndef __string_header__
#define __string_header__

#include "object/o_stream.h"

class StringBase{
public:
	enum ReturnValues{
		smaller,
		equal,
		bigger
	};
protected:
	static ReturnValues cmpFunc(const char* b1, unsigned char b1Length, const char *b2, unsigned char b2Length=0);

	static short appendChar(char* b1, unsigned char index, unsigned char maxLength, char c);

	static short appendFunc(char* b1, unsigned char b1Size, const char *b2, unsigned char b2Length=0);

public:
	static unsigned int strlen(const char* string);
};

class StaticString : public StringBase
{
	private:
		char* buffer;
		unsigned short index;

	public:
		const unsigned int maxLength;

		StaticString(char* buffer, unsigned char maxLength) : buffer(buffer), index(0), maxLength(maxLength){}

		StaticString& operator=(const char* string){
			index=appendFunc(buffer, maxLength, string);
			return *this;
		}

		unsigned char length() const{
			return index;
		};


		StaticString& operator+=(const char* b){
			index+=appendFunc(&buffer[index], maxLength-index, b);
			return *this;
		}

		StaticString& operator+=(StaticString& b){
			index+=appendFunc(&buffer[index], maxLength-index, b.buffer, b.index);
			return *this;
		}

		StaticString& operator+=(char c){
			index+=appendChar(buffer, index, maxLength, c);
			return *this;
		}

		bool operator==(const char* b) const{
			return (equal==cmpFunc(buffer, index, b));
		}

		bool operator<(const char* b) const{
			return (smaller==cmpFunc(buffer, index, b));
		}

		bool operator>(const char* b) const{
			return (bigger==cmpFunc(buffer, index, b));
		}

		bool operator<=(const char* b) const{
			ReturnValues ret=cmpFunc(buffer, index, b);
			return (ret==equal||ret==smaller);
		}

		bool operator>=(const char* b) const{
			ReturnValues ret=cmpFunc(buffer, index, b);
			return (ret==equal||ret==bigger);
		}

		bool operator==(const StaticString& b) const{
			return (equal==cmpFunc(buffer, index, b.buffer, b.index));
		}

		bool operator<(const StaticString& b) const{
			return (equal==cmpFunc(buffer, index, b.buffer, b.index));
		}

		bool operator>(const StaticString& b) const{
			return (equal==cmpFunc(buffer, index, b.buffer, b.index));
		}

		bool operator<=(const StaticString& b) const{
			ReturnValues ret=cmpFunc(buffer, index, b.buffer, b.index);
			return (ret==equal||ret==smaller);
		}

		bool operator>=(const StaticString& b) const{
			ReturnValues ret=cmpFunc(buffer, index, b.buffer, b.index);
			return (ret==equal||ret==bigger);
		}

		char operator[](unsigned char i) const{
			return buffer[i];
		}

		char& operator[](unsigned char i){
			return buffer[i];
		}

		short find(const char* string, unsigned short start=0);
};

O_Stream& operator<<(O_Stream& out, const StaticString& s);

#endif
