
#include "encoder.h"

int UTF8toUCS2Code(const UINT8* utf8_code, UINT16* ucs2_code)  
{  
     UINT16 temp1, temp2;  
     int is_unrecognized = 0 ;  
     UINT16 * in = utf8_code;  
       
     if(!utf8_code || !ucs2_code)  
     {  
        return is_unrecognized;  
     }  
     if(0x00 == (*in & 0x80))  
     {  
         /* 1 byte UTF-8 Charater.*/  
         *ucs2_code= (UINT16)*in;  
         is_unrecognized = 1;  
     }  
     else if(0xc0 == (*in & 0xe0) &&  
            0x80 == (*(in + 1) & 0xc0))  
     {  
         /* 2 bytes UTF-8 Charater.*/  
         temp1 = (UINT16)(*in & 0x1f);  
         temp1 <<= 6;  
         temp1 |= (UINT16)(*(in + 1) & 0x3f);  
         *ucs2_code = temp1;  
         is_unrecognized = 1;  
     }  
     else if( 0xe0 == (*in & 0xf0) &&  
            0x80 == (*(in +1) & 0xc0) &&  
            0x80 == (*(in + 2) & 0xc0))  
     {  
         /* 3bytes UTF-8 Charater.*/  
         temp1 = (UINT16)(*in &0x0f);  
         temp1 <<= 12;  
         temp2 = (UINT16)(*(in+1) & 0x3F);  
         temp2 <<= 6;  
         temp1 = temp1 | temp2 | (UINT16)(*(in+2) & 0x3F);  
         *ucs2_code = temp1;  
         is_unrecognized = 1;  
    }  
    else  
    {  
         /* unrecognize byte. */  
         *ucs2_code = 0x22e0;  
         is_unrecognized = 0;  
     }  
       
    return is_unrecognized;  
      
}  


UINT8 UCS2toUTF8Code(UINT16 ucs2_code, UINT8* utf8_code)  
{  
     int length = 0;  
     UINT8* out = utf8_code;  
     if(!utf8_code)  
     {  
        return length;  
     }  
     if(0x0080 > ucs2_code)  
     {  
         /* 1 byte UTF-8 Character.*/  
         *out = (UINT8)ucs2_code;  
         length++;  
     }  
     else if(0x0800 > ucs2_code)  
     {  
         /*2 bytes UTF-8 Character.*/  
         *out = ((UINT8)(ucs2_code >> 6)) | 0xc0;  
         *(out+1) = ((UINT8)(ucs2_code & 0x003F)) | 0x80;  
         length += 2;  
     }  
     else  
     {  
         /* 3 bytes UTF-8 Character .*/  
         *out = ((UINT8)(ucs2_code >> 12)) | 0xE0;  
         *(out+1) = ((UINT8)((ucs2_code & 0x0FC0)>> 6)) | 0x80;  
         *(out+2) = ((UINT8)(ucs2_code & 0x003F)) | 0x80;  
         length += 3;  
     }  
     return length;  
}  

