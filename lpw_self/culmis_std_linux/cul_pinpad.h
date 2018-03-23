#ifndef __CULPINPAD_H__
#define __CULPINPAD_H__


extern S32 cul_get_masterkey(S8* masterkey,S8* mkindex);
extern S32 soft_check_key(S8* master_key,S8 * key_field);
extern S32 soft_calc_mac(S8* master_key,S8*mac_key,S8 *in_data, S32 len,S8 *out_mac_data);
extern S32 soft_get_pin(S8* master_key,S8* pin_key,S8 *in_card_no, S8 *in_pwd, U8* out_pin_block);
S32 des(U8 key[],U8 input[],U8 output[]);
S32 dedes(U8 key[],U8 input[],U8 output[]);

#endif

