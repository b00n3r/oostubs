#include "object/string.h"

/*not yet tested*/
StringBase::ReturnValues StringBase::cmpFunc(const char* b1, unsigned char b1Length, const char *b2, unsigned char b2Length){
	while(b1Length&&b2Length)
	{
		if(*b1<*b2)
			return smaller;
		if(*b1>*b2)
			return bigger;
		b1Length--;
		b2Length--;
		b1++;
		b2++;
	}

	if(b1Length)
		return bigger;
	if(b2Length)
		return smaller;

	return equal;
}

short StringBase::appendChar(char* b1, unsigned char index, unsigned char maxLength, char c){
	if(c=='\b'&&index>0)
		return -1;
	if(c=='\b'&&index==0)
		return 0;
	if(index==maxLength)
		return 0;
	b1[index]=c;
	return 1;
}

/* not yet tested */
short StringBase::appendFunc(char* b1, unsigned char b1Size, const char *b2, unsigned char b2Length){
	short appended=0;

	while(b2Length && b1Size>appended)
	{
		appended+=appendChar(b1, appended, b1Size, *b2);

		b2++;
		b2Length--;
	}

	return appended;
}

short StaticString::find(const char *string, unsigned short indexA){
	unsigned short pos=0;
	unsigned short indexB=0;
	for(;indexA<index;indexA++)
	{
		if(buffer[indexA]==string[indexB])
			indexB++;
		else
			pos++;
		if(string[indexB]=='\0')
			return pos;
	}
	return -1;
}

unsigned int StringBase::strlen(const char* string)
{
	unsigned int i=0;
	while(string[i]!='\0')
		i++;
	return i;
}

O_Stream& operator<<(O_Stream& out, const StaticString& s){
	for(unsigned char i=0;i<s.length();i++)
		out << s[i];
	return out;
}
