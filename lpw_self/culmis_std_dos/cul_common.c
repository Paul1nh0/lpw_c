#include "cul_macro.h"
#include "cul_common.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"

int replace_byte(char* req,char src,char dst,int len)
{
    int i = 0;
    for(i=0;i<len;i++)
    {
        if(req[i]==src)
            req[i]=dst;
    }
    return 0;
}

int get_current_year(char* strYear)
{
    time_t cur_time = time(NULL);

    struct tm* t = localtime(&cur_time);

    if (t == NULL)
    {
        return -1;
    }

    if (strftime(strYear, 5, "%Y", t) == 0)
    {
        return -2;
    }

    return 0;
}


int get_current_mmdd(char *strTime )
{
    time_t cur_time = time(NULL);

    struct tm* t = localtime(&cur_time);

    if (t == NULL)
    {
        return -1;
    }

    if (strftime(strTime, 5, "%m%d", t) == 0)
    {
        return -2;
    }

    return 0;
}

int get_current_datetime(char *strTime )
{
    time_t cur_time = time(NULL);

    struct tm* t = localtime(&cur_time);

    if (t == NULL)
    {
        return -1;
    }

    if (strftime(strTime, 21, "%Y-%m-%d %H:%M:%S", t) == 0)
    {
        return -2;
    }

    return 0;
}



S32 cul_trim(S8* pInData,S32 nInLen,S8* pOutData,S32* nOutLen,S8* pTrimList,S32 nTrimLen)
{
	S32 i = 0; /*for nInLen*/
	S32 j = 0; /*for nOutLen*/
	S32 k = 0; /*for strTrimList*/
	S8 charTrimFlag = 0;
	S8* pInTmp = pInData;
	S8* pOutTmp = pOutData;
	for(i=0;i<nInLen;i++)
	{
		charTrimFlag = 0;
		for(k=0;k<nTrimLen;k++)
		{
			if(pInTmp[i] == pTrimList[k])
			{
				charTrimFlag = 1;
				break;
			}
			else
			{
				continue;
			}
		}
		if(!charTrimFlag)
		{
			pOutTmp[j]=pInTmp[i];
			j++;
		}
	}
	*nOutLen = j;
	return j;
}


int all_trim(char* in_str,int in_len,char* out_str,int* out_len)
{
    int i = 0;
    int j = 0;
    char* in_tmp_str = in_str;
    char* out_tmp_str = out_str;
    for(i=0;i<in_len;i++)
    {
#if 1
        if(in_tmp_str[i] == 0x20 /*space*/
         ||in_tmp_str[i] == 0x09 /*tab*/
         ||in_tmp_str[i] == 0x0d /*return*/
         ||in_tmp_str[i] == 0x0a /*carriage*/
         ||in_tmp_str[i] == 0x00) /*'\0'*/
#else
            if(in_tmp_str[i]<0x21 || in_tmp_str[i] > 0x7E) //过滤掉不能正常输出的字符以及空格
#endif
        {
            continue;
        }
        else
        {
            out_tmp_str[j]=in_tmp_str[i];
            j++;
        }
    }
    *out_len = j;
    return j;
}


int check_medium_info(char* mediumInfo)
{
	int i=0;
	int len=strlen(mediumInfo);
	if(len<13||len>37)
	{
		return -1;
	}
	for(i=0;i<len;i++)
	{
		if((mediumInfo[i]>'9'||mediumInfo[i]<'0')&&mediumInfo[i]!='=')
		{
			return -1;
		}
	}
	return 0;
}



int is_digit(char* str,int len)
{
    int i=0;
    for(i=0;i<len;i++)
    {
        if(str[i]>'9'||str[i]<'0')
        {
            return -1;
        }
    }
    return 0;
}

int get_card_number(char* str,char* out_number)
{
    int i = 0;
	int len = strlen(str);
    for(i=0;i<len;i++)
    {
		if(i>19)
		{
			return -1;
		}
        if(str[i]<0x3A && str[i]>0x2F) /*'0'~'9'*/
        {
            out_number[i]=str[i];
        }
        else
        {
            return 0;
        }
    }
    return -1;
}

int is_track2(char* str)
{
    int i = 0;
	int len = strlen(str);
    for(i=0;i<len;i++)
    {
        if(str[i]=='=')
            return 0;
    }
    return -1;
}

int is_str(char* str,int len)
{
    int i = 0;
    for(i=0;i<len;i++)
    {
        if(str[i]>0x7e||str[i]<0x20)
        {
            return -1;
        }
    }
    return 0;
}

int is_hex(char* str,int len)
{
    int i = 0;
    for(i=0;i<len;i++)
    {
        if(str[i]>'9'||str[i]<'0')
        {
            return -1;
        }
    }
    return 0;
}

int cul_check_date(char* date)
{
	int year = 0;
	int month = 0;
	int day = 0;
	char tmp[5]={0x00};
	memcpy(tmp,date,4);
	year = atoi(tmp);
	
	memset(tmp,0x00,5);
	memcpy(tmp,date+4,2);
	month = atoi(tmp);
	if(month<1||month>12)
	{
		return -1;
	}
	memset(tmp,0x00,5);
	memcpy(tmp,date+6,2);
	day = atoi(tmp);
	if(day<1||day>31)
	{
		return -1;
	}

	if(month==4||month==6||month==9||month==11)
	{
		if(day<1||day>30)
		{
			return -1;
		}
	}
	if(month==2)
	{
		if((year%4==0&&year%100!=0)||year%400==0)
		{
			if(day<1||day>29)
			{
				return -1;
			}
		}
		else
		{
			if(day<1||day>28)
			{
				return -1;
			}
		}
	}
	return 0;
	
}

#if 1
int cul_itoa(int value, char *str)
{
    int i,j;
    if (value < 0) /*如果是负数,则str[0]='-',并把value取反(变成正整数)*/
    {
        str[0] = '-';
        value = 0-value;
    }

    for(i=1; value > 0; i++,value/=10) /*从value[1]开始存放value的数字字符，不过是逆序，等下再反序过来*/

        str[i] = value%10+'0'; /*将数字加上0的ASCII值(即'0')就得到该数字的ASCII值*/

    for(j=i-1,i=1; j-i>=1; j--,i++) /*将数字字符反序存放*/

    {
        str[i] = str[i]^str[j];
        str[j] = str[i]^str[j];
        str[i] = str[i]^str[j];
    }
    if(str[0] != '-') /*如果不是负数，则需要把数字字符下标左移一位，即减1*/
    {
        for(i=0; str[i+1]!='\0'; i++)
            str[i] = str[i+1];
        str[i] = '\0';
    }
    return 0;
}
#endif

#if 0
int str_to_chinese(char* str,char* chinese)
{
    int i = atoi(str);
    switch(i)
    {
        case 1:
            memcpy(chinese,"消费",4);
            break;
        case 2:
            memcpy(chinese,"消费撤销",8);
            break;
        case 3:
            memcpy(chinese,"查余",4);
            break;
        case 4:
            break;
        case 5:
            memcpy(chinese,"退货",4);
            break;
        case 7:
            //	memcpy(chinese,"")
            break;
        case 11:
            memcpy(chinese,"条码消费",8);
            break;
        case 12:
            memcpy(chinese,"条码撤销",8);
            break;
        case 13:
            memcpy(chinese,"条码退货",8);
            break;
        case 21:
            memcpy(chinese,"激活",4);
            break;
        case 22:
            memcpy(chinese,"激活撤销",8);
            break;
        case 23:
            memcpy(chinese,"卡状态查询",10);
            break;
        default:
            break;
    }
    return 0;
}

int str_to_amount(char* in_amount_str,char* out_amount)
{
    int n_amount = 0;
    n_amount = atoi(in_amount_str);
    sprintf(out_amount,"%0.2f",(double)n_amount/100);
    return 0;
}
#endif

