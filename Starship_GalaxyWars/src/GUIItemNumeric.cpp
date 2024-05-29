#include "GUIItemNumeric.h"
#include "stdint.h"
#include "TextTextures.h"

GUIItemNumeric::GUIItemNumeric(uint8_t srcNum)
	: GUIItem(&kTextTextureNum0)
{
	uint8_t numDigits = 0;
	if (srcNum >= 100) {numDigits = 3;}
	else if(srcNum >= 10) {numDigits = 2;}
	else {numDigits = 1;}

	
}