#ifndef __CULCOMMON_H__
#define __CULCOMMON_H__



extern int asc_to_bcd ( unsigned char* ascii_buf , unsigned char* bcd_buf , int conv_len ,unsigned char type );
extern int bcd_to_asc (unsigned char* bcd_buf  ,unsigned char* ascii_buf , int conv_len ,unsigned char type );
extern S32 cul_trim(S8* pInData,S32 nInLen,S8* pOutData,S32* nOutLen,S8* pTrimList,S32 nTrimLen);
extern int is_digit(char* str,int len);
extern int is_str(char* str,int len);
extern int get_card_number(char* str,char* out_number);
extern int is_track2(char* str);
extern int str_to_chinese(char* str,char* chinese);
extern int str_to_amount(char* in_amount_str,char* out_amount);
extern int cul_itoa(int value, char *str);
extern int get_current_year(char* year);
extern int get_current_datetime(char *strTime );
extern int get_current_yyyymmdd(char *strTime );
extern int get_current_mmdd(char *strTime );
extern int replace_byte(char* req,char src,char dst,int len);
extern int get_current_time(char *strTime );
#define SET_REG_BIT(reg, bit) do { (reg |= (1 << (bit))); } while (0)

#endif
