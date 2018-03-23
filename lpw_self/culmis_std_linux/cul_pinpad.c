#include "cul_macro.h"
#include "cul_pinpad.h"
#include "cul_common.h"
#include "string.h"
#include "cul_log.h"

S8 sbox1[]=
  {14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
    0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
    4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
   15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13
  };
S8 sbox2[]=
  {15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
    3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
    0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
   13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9
  };
S8 sbox3[]=
  {10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
   13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
   13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
    1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12
  };
S8 sbox4[]=
  { 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
   13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
   10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
    3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14
  };
S8 sbox5[]=
  { 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
   14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
    4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
   11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3
  };
S8 sbox6[]=
  {12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
   10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
    9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
    4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13
  };
S8 sbox7[]=
  { 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
   13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
    1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
    6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12
  };
S8 sbox8[]=
  {13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
    1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
    7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
    2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11
  };
S8 *sbox[]={sbox1,sbox2,sbox3,sbox4,sbox5,sbox6,sbox7,sbox8};
S8 table1[]= /* for initial permutation */
    {58,50,42,34,26,18,10, 2,60,52,44,36,28,20,12, 4,
     62,54,46,38,30,22,14, 6,64,56,48,40,32,24,16, 8,
     57,49,41,33,25,17, 9, 1,59,51,43,35,27,19,11, 3,
     61,53,45,37,29,21,13, 5,63,55,47,39,31,23,15, 7
    };
S8 table2[]= /* for permutation choice 1 */
    {57,49,41,33,25,17, 9,    1,58,50,42,34,26,18,
     10, 2,59,51,43,35,27,   19,11, 3,60,52,44,36,
     63,55,47,39,31,23,15,    7,62,54,46,38,30,22,
     14, 6,61,53,45,37,29,   21,13, 5,28,20,12, 4
    };
S8 table3[]= /* for expansion function */
    {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9,10,11,
     12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,
     22,23,24,25,24,25,26,27,28,29,28,29,30,31,32, 1
    };
S8 table4[]= /* for permutation choice 2 */
    {14,17,11,24, 1, 5, 3,28,15, 6,21,10,23,19,12, 4,
     26, 8,16, 7,27,20,13, 2,41,52,31,37,47,55,30,40,
     51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32
    };
S8 table5[]= /* for inverse of initial permutation */
    {40, 8,48,16,56,24,64,32,39, 7,47,15,55,23,63,31,
     38, 6,46,14,54,22,62,30,37, 5,45,13,53,21,61,29,
     36, 4,44,12,52,20,60,28,35, 3,43,11,51,19,59,27,
     34, 2,42,10,50,18,58,26,33, 1,41, 9,49,17,57,25
    };
S8 table6[]= /* for permutation function P */
    {16, 7,20,21,29,12,28,17, 1,15,23,26, 5,18,31,10,
      2, 8,24,14,32,27, 3, 9,19,13,30, 6,22,11, 4,25
    };
S8 table7[]= /* for selection function */
    { 1, 6, 2,1, 7,12, 8,5,13,18,14,9,19,24,20,13,
     25,30,26,17,31,36,32,21,37,42,38,25,43,48,44,29
    };
S8 table8[]= /* for shift left 1 */
    { 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,
     18,19,20,21,22,23,24,25,26,27,28, 1,30,31,32,33,
     34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,
     50,51,52,53,54,55,56,29
    };
S8 table9[]= /* for shift left 2 */
    { 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,
     19,20,21,22,23,24,25,26,27,28, 1, 2,31,32,33,34,
     35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,
     51,52,53,54,55,56,29,30
    };
S8 table10[]= /* for shift right 1 */
    {28, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
     16,17,18,19,20,21,22,23,24,25,26,27,56,29,30,31,
     32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
     48,49,50,51,52,53,54,55,
    };
S8 table11[]= /* for shift right 2 */
    {27,28, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
     15,16,17,18,19,20,21,22,23,24,25,26,55,56,29,30,
     31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,
     47,48,49,50,51,52,53,54
    };
S8 *table[]=
    {table1,table2,table3,table4,table5,table6,
     table7,table8,table9,table10,table11
    };

/* content is table index,total count */
U8 initial_permutation[]={0,64};
U8 permutation_c1[]={1,56};
U8 expansion_function[]={2,48};
U8 permutation_c2[]={3,48};
U8 inverse_ip[]={4,64};
U8 permutation_fp[]={5,32};
U8 shift_left1[]={7,56};
U8 shift_left2[]={8,56};
U8 shift_right1[]={9,56};
U8 shift_right2[]={10,56};
U8 x64[8],i64[8],k64[8],k56[7],k48[6],l32[4],r48[6],r32[4];

void transdata(U8 input[],U8 output[],U8 function[])
  {register S32 i;
   U8 out[8];
   for (i=0;i<function[1]>>3;i++)
     out[i]=0;               /* initial value with 0 */
   for (i=0;i<function[1];i++)
     out[i>>3] |= (( input[(table[function[0]][i]-1) >> 3]
                     & (0x80>>(table[function[0]][i]-1 & 0x7)))
                     << (table[function[0]][i]-1 & 0x7)) >> (i & 0x7);
   for (i=0;i<function[1]>>3;i++)
     output[i]=out[i];          /* initial value with 0 */
   return;
  }
void desselect(U8 input[],U8 output[])
  {S32 idx,i,j,k,cnt;
   for (i=0;i<4;i++)
     output[i]=0;               /* initial value with 0 */
   cnt=0;
   for (i=0;i<8;i++)
     {
      for (j=5,k=0,idx=0;j>=0;j--)
        {idx+=((input[(table7[cnt]-1+k)>>3] & (0x80>>(table7[cnt]-1+k & 0x7)))
                ? 1 <<j : 0);
         if (j>3)
            cnt++;
         else
           k++;
        }
      cnt++;
      for (j=0;j<4;j++)
        output[(table7[cnt]+j-1) >> 3] |= ((sbox[i][idx] & (0x08 >> j)) << (4+j))
                                        >> (table7[cnt]+j-1 & 0x7);
      cnt++;
     }
     return;
  }
void fnct(U8 io[],U8 input[])
  /* io->r32 input->k56 */
  {U8 k48[6],r48[6],s32[4];
   register S32 i;
   transdata(input,k48,permutation_c2); /* 28+28 to 48 */
   transdata(io,r48,expansion_function); /* 32 to 48 */
   for (i=0;i<6;i++)    /* expn xor key */
     r48[i] ^=k48[i];
   desselect(r48,s32);
   transdata(s32,io,permutation_fp);
   return ;
  }
S32 des(U8 key[],U8 input[],U8 output[])
/* input->x64 key->k64 output->i64 */
  {U8 i64[8],k56[7],t32[4];
   transdata(input,i64,initial_permutation);
   transdata(key,k56,permutation_c1);
/*****shift left 1 ****/
   transdata(k56,k56,shift_left1);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 1 ****/
   transdata(k56,k56,shift_left1);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 1 ****/
   transdata(k56,k56,shift_left1);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 2 ****/
   transdata(k56,k56,shift_left2);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/*****shift left 1 ****/
   transdata(k56,k56,shift_left1);
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   fnct(i64+4,k56);
   i64[4] ^= i64[0]; i64[5] ^= i64[1]; i64[6] ^= i64[2]; i64[7] ^= i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
/* substitute */
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   i64[4]=i64[0]; i64[5]=i64[1]; i64[6]=i64[2]; i64[7]=i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
   transdata(i64,output,inverse_ip);
   return 0;
  }
S32 dedes(U8 key[],U8 input[],U8 output[])
/* input->x64 key->k64 output->i64 */
  {U8 i64[8],k56[7],t32[4];
   transdata(input,i64,initial_permutation);
/* substitute */
   t32[0]=i64[4]; t32[1]=i64[5]; t32[2]=i64[6]; t32[3]=i64[7];
   i64[4]=i64[0]; i64[5]=i64[1]; i64[6]=i64[2]; i64[7]=i64[3];
   i64[0]=t32[0]; i64[1]=t32[1]; i64[2]=t32[2]; i64[3]=t32[3];
   transdata(key,k56,permutation_c1);
/*****shift right 1 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right1);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 1 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right1);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 2 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right2);
/*****shift right 1 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right1);
/*****shift right 1 ****/
   t32[0]=i64[0]; t32[1]=i64[1]; t32[2]=i64[2]; t32[3]=i64[3];
   fnct(i64,k56);
   i64[0] ^= i64[4]; i64[1] ^= i64[5]; i64[2] ^= i64[6]; i64[3] ^= i64[7];
   i64[4]=t32[0]; i64[5]=t32[1]; i64[6]=t32[2]; i64[7]=t32[3];
   transdata(k56,k56,shift_right1);
/* substitute */
   transdata(i64,output,inverse_ip);
   return 0;

}


/*static U8 MasterKey[8] = {0x06,0x64,0xFC,0xB6,0xB4,0x56,0xF1,0xA5};*/
static U8 MasterKey301[8] ={0x03,0x20,0x40,0x28,0x00,0x51,0x93,0x71};
static U8 MasterKey311[8] ={0x84,0xAB,0x93,0x27,0x78,0xDE,0xF2,0x6D};
static U8 MasterKey334[8]={0x73,0xAB,0x9C,0x2C,0x3F,0x10,0xC6,0x71};
static U8 MasterKey013[8]={0x87,0x65,0x43,0x21,0x87,0x65,0x43,0x21};
static U8 MasterKey312[8]={0x30,0x72,0x29,0xA4,0x73,0x96,0x10,0x9E};
static U8 MasterKey336[8] ={0x06,0x64,0xFC,0xB6,0xB4,0x56,0xF1,0xA5};
static U8 MasterKey324[8]={0xA3,0x29,0x17,0xE4,0xC6,0x4E,0xAA,0x61};

S32 cul_get_masterkey(S8* masterkey,S8* mkindex)
{
    if(memcmp(mkindex,"013",3)==0)
    {
        memcpy(masterkey,MasterKey013,8);
    }
    else if(memcmp(mkindex,"301",3)==0)
    {
        memcpy(masterkey,MasterKey301,8);
    }
    else if(memcmp(mkindex,"311",3)==0)
    {
        memcpy(masterkey,MasterKey311,8);
    }
    else if(memcmp(mkindex,"334",3)==0)
    {
        memcpy(masterkey,MasterKey334,8);
    }
    else if(memcmp(mkindex,"312",3)==0)
    {
        memcpy(masterkey,MasterKey312,8);
    }
    else if(memcmp(mkindex,"336",3)==0)
    {
        memcpy(masterkey,MasterKey336,8);
    }
    else if(memcmp(mkindex,"324",3)==0)
    {
        memcpy(masterkey,MasterKey324,8);
    }
    else
    {
        memcpy(masterkey,MasterKey013,8);
    }
    return 0;
}

S32 soft_check_key(S8* master_key,S8 * key_field)
{
    U8 soft_master_key[8];
    U8 plain_text[16];  
    U8 cipher_mac_key[8];
    U8 cipher_pin_key[8];
    U8 mac_key_check_value[4];
    U8 pin_key_check_value[4];
    U8 check_zero[16];
    U8 check_value[16];

    long nReturn = 0;
    S32 i;

    if(master_key == 0 || master_key == 0)
    {
        return -1;
    }
    memset(check_zero,0x00,16);
    memset(check_value,0x00,16);
    memset(plain_text,0x00,16);
    memcpy(soft_master_key, master_key, 8);

    memcpy(cipher_pin_key,key_field,8);
    memcpy(pin_key_check_value,key_field+8,4);
    memcpy(cipher_mac_key,key_field+12,8);
    memcpy(mac_key_check_value,key_field+20,4);

    nReturn = dedes(soft_master_key, cipher_pin_key, plain_text);

    nReturn = des(plain_text, check_zero, check_value);
    for (i = 0; i < 4; i++)
    {
        if (check_value[i] != pin_key_check_value[i])
        {
            return -2;
        }
    }

    memset(plain_text, 0, sizeof(plain_text));
    nReturn = dedes(soft_master_key, cipher_mac_key, plain_text);
    nReturn = des(plain_text, check_zero, check_value);
    for (i = 0; i < 4; i++)
    {
        if (check_value[i] != mac_key_check_value[i])
        {
            return -3;
        }
    }
    return 0;
}

S32 soft_calc_mac(S8* master_key,S8*mac_key,S8 *in_data, S32 len,S8 *out_mac_data)
{
    S32 nReturn = 0;
    S32 i, j, l, nLen;
    U8 Buf[9];
    U8 szData[4096];
    U8 AscBuf[20];
    U8 BufA[8];
    U8 BufB[8];
    U8 MacBuf[9];
    U8 Dest[16];
    U8 soft_master_key[8];
    U8 plain_mac_key[16];  
    U8 cipher_mac_key[8];
    U8 MacKey[8];
    memset(Buf, 0, sizeof(Buf));
    memset(szData, 0, sizeof(szData));
    memset(AscBuf, 0, sizeof(AscBuf));
    memset(BufA, 0, sizeof(BufA));
    memset(BufB, 0, sizeof(BufB));
    memset(MacBuf, 0, sizeof(MacBuf));
    memset(Dest, 0, sizeof(Dest));


    in_data[5+6+2+7] |= 0x01;/*置位图64域*/
    nLen = len - 11;
    /*从交易类型开始算mac*/
    memcpy(szData, in_data+11, len-11);
    memcpy(soft_master_key, master_key, 8);
    memcpy(cipher_mac_key,mac_key,8);
    memset(plain_mac_key,0x00,16);
    nReturn = dedes(soft_master_key, cipher_mac_key, plain_mac_key);

    memcpy(MacKey, plain_mac_key, 8);
    l = nLen/8;

    if (nLen != l * 8) l++;

    for (i = 0; i < l; i++)
    {
        for (j=0; j<8; j++)
        {
            if (i*8 +j > nLen -1)
                Buf[j] = Buf[j] ^ 0;
            else
                Buf[j] = Buf[j] ^ szData[i*8 +j];
        }
    }
    bcd_to_asc(Buf,AscBuf, 16,0);

    memcpy(BufA, AscBuf, 8);
    memcpy(BufB, AscBuf+8, 8);

    nReturn = des(MacKey, BufA, Dest);
    for (i=0; i<=7; i++)
    {
        Dest[i] = Dest[i] ^ BufB[i];
    }

    memcpy(BufA, Dest, 8);
    nReturn = des(MacKey, BufA, Dest);
    memset(AscBuf, 0, sizeof(AscBuf));
    bcd_to_asc(Dest,AscBuf,16,0);
    memcpy(MacBuf, AscBuf, 8);


    memcpy(out_mac_data, MacBuf, 8);

    return 0;
}

S32 soft_get_pin(S8* master_key,S8* pin_key,S8 *in_card_no, S8 *in_pwd, U8* out_pin_block)
{
    U8 PinCardNumber[20];
    U8 CardNumber[20];
    U8 BcdCardNumber[20];
    S8 tmp[20];
    long nReturn;
    U8 buf[8] ={0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    S32 nPinLen =6;
    S32 i;
    S32 card_len = 0;
    U8 BcdPin[7];
    U8 szPinBlock[20];
    U8 pan[16];
/*    S32 nBeginPosition; */
    U8 soft_master_key[8];
    U8 plain_pin_key[16];  
    U8 cipher_pin_key[8];
/*    U8 PinKey[8]; */

    memset(pan,0x30,16);
    memset(PinCardNumber, 0, sizeof(PinCardNumber));
    memset(CardNumber, 0, sizeof(CardNumber));
    memset(BcdCardNumber, 0, sizeof(BcdCardNumber));
    memset(szPinBlock, 0, sizeof(szPinBlock));
    memset(tmp, 0, sizeof(tmp));

    card_len = strlen(in_card_no);
    memcpy(pan+4,in_card_no+card_len-13,12);
    
    asc_to_bcd((U8 *)pan, BcdCardNumber, 16,0);

    buf[0] = 0x06; 

    asc_to_bcd((U8 *)in_pwd, BcdPin, 6,0);


    for (i=0; i<=2; i++)
    {
        buf[i +1] = BcdPin[i];
    }

    for (i=0; i<=7; i++)
    {
        BcdCardNumber[i] = BcdCardNumber[i] ^ buf[i];
    }

    memcpy(soft_master_key, master_key, 8);
    memcpy(cipher_pin_key,pin_key,8);
    memset(plain_pin_key,0x00,16);
    nReturn = dedes(soft_master_key, cipher_pin_key, plain_pin_key);

/*    memcpy(PinKey, plain_pin_key, 8); */
    nReturn = des(plain_pin_key, BcdCardNumber, szPinBlock);

    memcpy(out_pin_block, szPinBlock, 8);/*PinBcd*/

    return 0;
}

S32 string_process(U8* str,S32 len)
{
    S32 i = 0;
    U8 ch1 = 0;
    U8 ch2 = 0;
    for(i=0;i<len;i++)
    {
        ch1 = (str[i]&0x3F)<<2;
        ch2 = (str[i]&0xC0)>>6;
        str[i] = ch1|ch2;
        str[i] = str[i]^0xAB;
        ch1 = (str[i]&0x03)<<6;
        ch2 = (str[i]&0xFC)>>2;
        str[i] = ch1|ch2;
    }
    return 0;
}
