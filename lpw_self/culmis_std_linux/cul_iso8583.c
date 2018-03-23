#include "cul_macro.h"
#include "cul_iso8583.h"
#include "cul_log.h"
#include "stdlib.h"
#include "string.h"



const FieldDsc fd_list[FIELDS]=
{   
    {LEN_TYPE,          0,    DATA_TYPE_BIN,     0,    8}, /*  1 bitmap */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_BCD_L, 0, 19}, /*  2 accNo*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 6}, /*  3 procCode*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 12}, /*  4 amount*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 12}, /*  5 amount settlement*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 12}, /*  6 amount billing*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 10}, /*  7 date&time mmddhhmmss */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /*  8 fee Amount  */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /*  9 amount  rate settle*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /* 10 amount  rate*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 6}, /* 11 sysTrace*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 6}, /* 12 time     */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 13 date     */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 14 expDate */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 15 settlement date */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 16 date */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 17 date */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 18 merchant Type */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 3}, /* 19 acquiring Country Code */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 3}, /* 20 can country code */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 3}, /* 21 forwarding Country code */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 3}, /* 22 pOSentry*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_R, 0, 3}, /* 23 application Pan */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,   0, 3}, /* 24 II wangsx2    ISO8583type_BCD*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 2}, /* 25 pOScond */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 2}, /* 26 pOScond */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 1}, /* 27 response len */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /* 28 fee amount */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /* 29 settlement fee amount */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /* 30 trans Processing Fee Amount */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /* 31 settle Processing Fee Amount */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_BCD_L, 0, 11}, /* 32 acquiring ID */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_BCD_L, 0, 11}, /* 33 forwarding ID */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_BCD_L, 0, 11}, /* 34 account Num extended */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_BCD_L, 0, 37}, /* 35 track2  */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_BCD_L, 0, 104}, /* 36 track3 */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    12}, /* 37 retRefNo*/
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    6}, /* 38 authID  */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    2}, /* 39 response*/
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    3}, /* 40 service Code */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    8}, /* 41 tID     */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    15}, /* 42 mAccID  */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    40}, /* 43 mAccName*/
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 25}, /* 44 addResp */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 25}, /* 45 track1  */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 25}, /* 46 additional Data    */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 25}, /* 47 additional Data    */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 322}, /* 48 dditional Data  */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    3}, /* 49 currency Code    Transaction */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    3}, /* 50 currency Code    Settlement    */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    3}, /* 51 currency Code    billing     */
    {LEN_TYPE,          0,    DATA_TYPE_BIN,     0,    8}, /* 52 pINData */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0,    16}, /* 53 security Data */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 20}, /* 54 addAmnts */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 255}, /* 55 CC info */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 99}, /* 56 reserved */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 99}, /* 57 reserved */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 100}, /* 58 reserved */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0,    4}, /* 59 reserved */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_BCD_L, 0, 14}, /* 60 reserved*/
    {LEN_TYPE_BCD,      3,    DATA_TYPE_BCD_L, 0, 29}, /* 61 reserved*/
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 999}, /* 62 reserved*/
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 999}, /* 63 reserved*/
    {LEN_TYPE,          0,    DATA_TYPE_ASC,   0, 8},  /* 64 MAC data*/
#if 0
    {LEN_TYPE,          0,    DATA_TYPE_BIN,     0,    8}, /*  65 bitmap */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_BCD_L, 0, 19}, /*  66 accNo*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 6}, /*  67 procCode*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 12}, /*  68 amount*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 12}, /*  69 amount settlement*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 12}, /*  70 amount billing*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 10}, /*  71 date&time mmddhhmmss */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /*  72 fee Amount  */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /*  73 amount  rate settle*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /* 74 amount  rate*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 6}, /* 75 sysTrace*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 6}, /* 76 time     */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 77 date     */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 78 expDate */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 79 settlement date */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 80 date */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 81 date */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 4}, /* 82 merchant Type */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 3}, /* 83 acquiring Country Code */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 3}, /* 84 can country code */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 3}, /* 85 forwarding Country code */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 3}, /* 86 pOSentry*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_R, 0, 3}, /* 87 application Pan */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,   0, 3}, /* 88 II wangsx2    ISO8583type_BCD*/
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 2}, /* 89 pOScond */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 2}, /* 90 pOScond */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 1}, /* 91 response len */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /* 92 fee amount */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /* 93 settlement fee amount */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /* 94 trans Processing Fee Amount */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0, 8}, /* 95 settle Processing Fee Amount */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_BCD_L, 0, 11}, /* 96 acquiring ID */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_BCD_L, 0, 11}, /* 97 forwarding ID */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_BCD_L, 0, 11}, /* 98 account Num extended */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_BCD_L, 0, 37}, /* 99 track2  */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_BCD_L, 0, 104}, /* 100 track3 */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    12}, /* 101 retRefNo*/
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    6}, /* 102 authID  */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    2}, /* 103 response*/
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    3}, /* 104 service Code */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    8}, /* 105 tID     */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    15}, /* 106 mAccID  */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    40}, /* 107 mAccName*/
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 25}, /* 108 addResp */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 25}, /* 109 track1  */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 25}, /* 110 additional Data    */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 25}, /* 111 additional Data    */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 322}, /* 112 dditional Data  */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    3}, /* 113 currency Code    Transaction */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    3}, /* 114 currency Code    Settlement    */
    {LEN_TYPE,          0,    DATA_TYPE_ASC,     0,    3}, /* 115 currency Code    billing     */
    {LEN_TYPE,          0,    DATA_TYPE_BIN,     0,    8}, /* 116 pINData */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0,    16}, /* 117 security Data */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 20}, /* 118 addAmnts */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 255}, /* 119 CC info */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 99}, /* 120 reserved */
    {LEN_TYPE_BCD,      2,    DATA_TYPE_ASC,   0, 99}, /* 121 reserved */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 100}, /* 122 reserved */
    {LEN_TYPE,          0,    DATA_TYPE_BCD_L, 0,    4}, /* 123 reserved */
    {LEN_TYPE_BCD,      3,    DATA_TYPE_BCD_L, 0, 14}, /* 124 reserved*/
    {LEN_TYPE_BCD,      3,    DATA_TYPE_BCD_L, 0, 29}, /* 125 reserved*/
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 999}, /* 126 reserved*/
    {LEN_TYPE_BCD,      3,    DATA_TYPE_ASC,   0, 999}, /* 127 reserved*/
    {LEN_TYPE,          0,    DATA_TYPE_ASC,   0, 8}  /* 128 MAC data*/
#endif
};

int asc_to_bcd ( unsigned char* ascii_buf , unsigned char* bcd_buf , int conv_len ,unsigned char type )
{
    int         cnt ;
    char        ch , ch1 ;

    if ( conv_len & 0x01 && type )
        ch1 = 0 ;
    else
        ch1 = 0x55 ;

    for ( cnt = 0 ; cnt < conv_len ; ascii_buf ++ , cnt ++ )
    {
        if ( *ascii_buf >= 'a' )
            ch = *ascii_buf - 'a' + 10 ;
        else if ( *ascii_buf >= 'A' )
            ch = *ascii_buf- 'A' + 10 ;
        else if ( *ascii_buf >= '0' )
            ch = *ascii_buf-'0' ;
        else
            ch = 0;

        if ( ch1 == 0x55 )
        {
            ch1 = ch ;
        }
        else
        {
            *bcd_buf ++ = ch1 << 4 | ch ;
            ch1 = 0x55 ;
        }
    }
    if ( ch1 != 0x55 )
        *bcd_buf = ch1 << 4 ;

    return 0;
}


int bcd_to_asc (unsigned char* bcd_buf ,unsigned char* ascii_buf , int conv_len ,unsigned char type )
{
    int cnt ;

    if ( conv_len & 0x01 && type )
    {
        cnt = 1 ;
        conv_len ++ ;
    }
    else
        cnt = 0 ;
    for ( ; cnt < conv_len ; cnt ++ , ascii_buf ++ )
    {
        *ascii_buf = ( ( cnt & 0x01 ) ? ( *bcd_buf ++ & 0x0f ) : ( *bcd_buf >> 4 ) ) ;
        *ascii_buf += ( ( *ascii_buf > 9 ) ? ( 'A' - 10 ) : '0' ) ;
    }

    return 0;
}


int iso8583_atoi(char* c,int n)
{
    int i = 0;
    int nReturn = 0;
    int desc = 1;
    for(i=0;i<n;i++)
    {
        nReturn += (c[n-i-1]-0x30)*desc;
        desc *= 10;
    }
    return nReturn;
}

int iso8583_itoa(char* src,int len, int n)
{
    if(n==2)
    {
        src[0] = len/10 + 0x30;
        src[1] = len%10 + 0x30;
    }
    else if(n==4)
    {
        src[0] = len/1000 + 0x30;
        src[1] = len%1000 / 100 + 0x30;
        src[2] = len%100 / 10 +0x30;
        src[3] = len %10+ 0x30;
    }
    else if(n == 3)
    {
        src[0] = len/100 +0x30;
        src[1] = len%100 /10 +0x30;
        src[2] = len%10 + 0x30;
    }
    else if(n == 1)
    {
        src[0] = len + 0x30;
    }
    else
    {
        return -1;
    }
    return n;
}



int bcd_to_len(char* bcd,int len)
{
    int i = 0;
    char temp[10]={0x00};
    /*iso8583_itoa()*/
    bcd_to_asc(bcd,temp,len,1);
    i = atoi(temp);
    return i;
}

int len_to_bcd(char* bcd,int len,int asc_len)
{
    int n_len = 0;
    char temp[10] = {0x00};
    iso8583_itoa(temp,len,asc_len);
    asc_to_bcd(temp,bcd,asc_len,1);
    return 0;
}

int cul_iso8583_init(IsoData* iso_data,int buf_len)
{
    if(iso_data == PNULL)
    {
        return -1;
    }
    memset(iso_data,0x00,sizeof(IsoData));
    iso_data->iso_field_data = (char*)malloc(buf_len);
    if(iso_data->iso_field_data == PNULL)
    {
        return -1;
    }
    return 0;
}

int cul_iso8583_exit(IsoData* iso_data)
{
    if(iso_data == PNULL)
    {
        return -1;
    }
    DELETE_POINTER(iso_data->iso_field_data);
    return 0;
}

int convert_data_to_iso(char* in_stream,char* out_stream,int in_stream_len,const FieldDsc* field_dsc)
{
    int n_len = 0;
    int data_len = 0;
    char bcd_len[5] = {0x00};
    
    if(field_dsc->len_type == LEN_TYPE)
    {
        if(in_stream_len != field_dsc->size)
        {
            return -1;
        }
        n_len = 0;    
    }
    else if(field_dsc->len_type == LEN_TYPE_BCD)
    {
        n_len = (field_dsc->len_size+1)>>1;
        len_to_bcd(bcd_len,in_stream_len,field_dsc->len_size);
        memcpy(out_stream,bcd_len,n_len);
        out_stream += n_len;
    }
    else
    {
        return -1;
    }

    if(field_dsc->data_type == DATA_TYPE_ASC||field_dsc->data_type == DATA_TYPE_BIN)
    {
        memcpy(out_stream,in_stream,in_stream_len);
        return in_stream_len+n_len;
    }
    else if(field_dsc->data_type == DATA_TYPE_BCD_L)
    {
        asc_to_bcd(in_stream,out_stream,in_stream_len,0);
        return ((in_stream_len+1)>>1)+n_len;
    }
    else if(field_dsc->data_type == DATA_TYPE_BCD_R)
    {
        asc_to_bcd(in_stream,out_stream,in_stream_len,1);
        return ((in_stream_len+1)>>1)+n_len;
    }
    else
    {
        return -1;
    }
    
}


int convert_iso_to_data(char* in_stream,char* out_stream,int* out_stream_len,const FieldDsc* field_dsc)
{
    int n_len = 0;
    int n_return = 0;
    char* asc_len[5] = {0x00};
    if(field_dsc->len_type == LEN_TYPE)
    {
        n_len = field_dsc->size;
        if(field_dsc->data_type == DATA_TYPE_ASC ||field_dsc->data_type == DATA_TYPE_BIN)
        {
            memcpy(out_stream,in_stream,n_len);
            n_return = n_len;
            
        }
        else if(field_dsc->data_type == DATA_TYPE_BCD_L)
        {
            bcd_to_asc(in_stream,out_stream,n_len,0);
            n_return = (n_len+1)>>1;
            
        }
        else if(field_dsc->data_type == DATA_TYPE_BCD_R)
        {
            bcd_to_asc(in_stream,out_stream,n_len,1);
            n_return = (n_len+1)>>1;
        }
        else
        {
            return -1;
        }
        *out_stream_len = n_len;
    }
    else if(field_dsc->len_type == LEN_TYPE_BCD)
    {
        n_len =bcd_to_len(in_stream,field_dsc->len_size);/* (field_dsc->len_size+1)>>1; */
        in_stream += (field_dsc->len_size+1)>>1;
        if(field_dsc->data_type == DATA_TYPE_ASC||field_dsc->data_type == DATA_TYPE_BIN)
        {
            memcpy(out_stream,in_stream,n_len);
            n_return = n_len+((field_dsc->len_size+1)>>1);
        }
        else if(field_dsc->data_type == DATA_TYPE_BCD_L)
        {
            bcd_to_asc(in_stream,out_stream,n_len,0);
            n_return = ((n_len+1)>>1)+((field_dsc->len_size+1)>>1);
        }
        else if(field_dsc->data_type == DATA_TYPE_BCD_R)
        {
            bcd_to_asc(in_stream,out_stream,n_len,1);
            n_return = ((n_len+1)>>1)+((field_dsc->len_size+1)>>1);
        }
        else
        {
            return -1;
        }
        *out_stream_len = n_len;
    }
    else
    {
        return -1;
    }
    return n_return;
    
    
}

int iso8583_set_bit_on(IsoData* iso_data ,int n)
{
    int i = n>>3; /* /8   */
    int j = (n+1)&7;  /* %8    */
    if(n<1 || n>64)
        return -1;
    if(j == 0)
    {
        iso_data->bit_map[i] |= 0x01;    
    }
    else
    {
        iso_data->bit_map[i] |= (0x01)<<(8-j);
    }
    return 0;
}

int iso8583_set_bit_off(IsoData* iso_data,int n)
{
    int i = (n+1)>>3; /* /8 */
    int j = (n+1)&7;     /* %8 */
    if(n<1 || n>64)
        return -1;
    iso_data->bit_map[i] &= ~((0x01)<<(8-j));
    return 0;
}

int iso8583_get_bit(IsoData* iso_data,int n)
{
    int i = (n-1)>>3;    /* /8   */
    int j = (n-1)&7;     /* %8   */
    if(n<1 || n>64)
        return 0;
    return iso_data->bit_map[i]&((0x80)>>(j));
}

int iso8583_set_isofield(IsoData* iso_data)
{
    int i =0;
    for(i=1;i<64;i++)
    {
        if(iso8583_get_bit(iso_data,i))
        {
            iso_data->iso_field[i-1].bit_on_off = 1;
        }
    }
    return 0;
}


int cul_iso8583_set_field(IsoData* iso_data,int n_field,char* content,int field_len)
{
    cul_log_string(LOG_8583,"field%d=%s",n_field,content);
    iso_data->iso_field[n_field-1].bit_on_off = 1;
    iso_data->iso_field[n_field-1].addr_offset = iso_data->curr_offset;
    iso_data->iso_field[n_field-1].len = field_len;
    memcpy(iso_data->iso_field_data+iso_data->curr_offset,content,field_len);
    iso_data->curr_offset += field_len;
    return 0;
}

int cul_iso8583_get_field(IsoData* iso_data,int n_field,char* content)
{
    int len = iso_data->iso_field[n_field-1].len;
    if(iso_data->iso_field[n_field-1].bit_on_off)
    {
        memcpy(content,&(iso_data->iso_field_data[iso_data->iso_field[n_field-1].addr_offset]),len);
        return len;
    }
    else
    {
        return 0;
    }

}

int cul_iso8583_pack(IsoData* iso_data,char* OUT iso_stream,int* OUT len)
{
    int i = 0;
    char* bit_map = 0;
    char* p_iso_stream = iso_stream;
    char* p_iso_buffer = 0;
    int field_type = 0;
    int field_size = 0;
    
    asc_to_bcd(iso_data->pos_tpdu,p_iso_stream,10,0);
    p_iso_stream += 5;
    asc_to_bcd(iso_data->package_head,p_iso_stream,12,0);
    p_iso_stream += 6;
    asc_to_bcd(iso_data->msg_type,p_iso_stream,4,0);
    p_iso_stream += 2;
    bit_map = p_iso_stream; 
    p_iso_stream += 8;
    for(i=1;i<FIELDS;i++) 
    {
        if(iso_data->iso_field[i].bit_on_off)
        {
            iso8583_set_bit_on(iso_data,i);
            p_iso_buffer = &(iso_data->iso_field_data[iso_data->iso_field[i].addr_offset]);
            
            p_iso_stream += convert_data_to_iso(p_iso_buffer,p_iso_stream,iso_data->iso_field[i].len,&fd_list[i]);
        }
    }
    memcpy(bit_map,iso_data->bit_map,FIELDS>>3);
    *len = p_iso_stream - iso_stream;
    return 0;
}

int cul_iso8583_unpack(IsoData* iso_data,const char* IN iso_stream)
{
    int i = 0;
    short len = 0;
    int field_type = 0;
    int field_size = 0;
    char* p_iso_stream = (char*)iso_stream;
    char* p_field_data = iso_data->iso_field_data;
/*    p_socket_buffer += 13; 5+6+2 TPUD head messagetype */
    bcd_to_asc(p_iso_stream,iso_data->pos_tpdu,10,0);
    p_iso_stream += 5;
    bcd_to_asc(p_iso_stream,iso_data->package_head,12,0);
    p_iso_stream += 6;
    bcd_to_asc(p_iso_stream,iso_data->msg_type,4,0);
    p_iso_stream += 2;


    memcpy(iso_data->bit_map,p_iso_stream,FIELDS>>3);
    iso8583_set_isofield(iso_data);
    p_iso_stream += FIELDS>>3;

    for(i=1;i<FIELDS;i++)
    {
        if(iso_data->iso_field[i].bit_on_off)
        {            
            p_iso_stream += convert_iso_to_data(p_iso_stream,p_field_data,&(iso_data->iso_field[i].len),&fd_list[i]);            
            iso_data->iso_field[i].addr_offset=p_field_data-iso_data->iso_field_data;
            p_field_data += iso_data->iso_field[i].len;            
        }
    }
    return 0;
}

