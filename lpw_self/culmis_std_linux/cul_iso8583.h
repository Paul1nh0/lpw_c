#ifndef __ISO8583_H__
#define __ISO8583_H__


#define FIELDS 64
#define ISO_BUF_LEN 4096


typedef int (*(converters[2])) ();  /* a pair or pointers to functions */

#define ISO8583type_ASC 0
#define ISO8583type_BCD 1
#define ISO8583type_V_ASC 2
#define ISO8583type_V_BCD 3
#define ISO8583type_V2_BCD 4 /* 62��� */


#define LEN_TYPE 0
#define LEN_TYPE_ASC 1
#define LEN_TYPE_BCD 2

#define DATA_TYPE_ASC 0
#define DATA_TYPE_BCD_L 1
#define DATA_TYPE_BCD_R 2
#define DATA_TYPE_BIN 3

typedef struct
{
  unsigned char len_type; /*0:�̶����� 1:asc��ʾ���� 2:bcd��ʾ����*/
  unsigned char len_size; /*�����ֽڱ�ʾ����*/
  unsigned char data_type;/*0:asc,bin 1:bcd�� 2:bcd�ҿ�*/
  unsigned char no_defined; /*û��ʵ������,ֻΪ4�ֽڶ���*/
  int size; /*�̶����ȱ�ʾ���� ������MAX_LEN*/
}FieldDsc;



typedef struct
{
	unsigned int bit_on_off;
	int len;
	int addr_offset; /*address offset in iso_field_data*/
}IsoField;

typedef struct
{
	char* iso_field_data; 
	IsoField iso_field[FIELDS];
	char pos_tpdu[11]; /*asc tpdu*/
	char package_head[13]; /*asc head*/
	char msg_type[5];
	char bit_map[FIELDS>>3]; /*FIELDS/8 64/8*/
	int curr_offset; /*current offset in iso_data*/
}IsoData;

extern int iso8583_set_bit_on(IsoData* iso_data ,int n);
extern int iso8583_set_bit_off(IsoData* iso_data ,int n);
extern int cul_iso8583_init(IsoData* iso_data,int len);
extern int cul_iso8583_exit(IsoData* iso_data);

extern int cul_iso8583_set_field(IsoData* iso_data,int n_field,char* content,int field_len);
extern int cul_iso8583_get_field(IsoData* iso_data,int n_field,char* content);
extern int cul_iso8583_pack(IsoData* iso_data,char* OUT iso_stream,int* OUT len);
extern int cul_iso8583_unpack(IsoData* iso_data,const char* IN iso_stream);

#endif

