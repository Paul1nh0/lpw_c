#ifndef __ENCODER_H__
#define __ENCODER_H__

typedef unsigned short UINT16;  
typedef unsigned char UINT8;  


int UTF8toUCS2Code(const UINT8* utf8_code, UINT16* ucs2_code);
UINT8 UCS2toUTF8Code(UINT16 ucs2_code, UINT8* utf8_code);

#endif

