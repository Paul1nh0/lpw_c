#ifndef __CULADAPTOR_H__
#define __CULADAPTOR_H__

#include "cul_macro.h"

typedef struct
{
	S8 TranType[2+1];
	S8 StoreNo[15+1];
	S8 CashNo[15+1];
	S8 ReceiverNo[15+1];
	S8 OrderNo[30+1];
	S8 OrderAmount[12+1];
	S8 MediumInfo[37+1];
	S8 PassWord[6+1];
	S8 OrgTrace[6+1];
	S8 OrgRef[12+1];
	S8 OrgDate[8+1];
	S8 ManageCardNo[37+1];
	S8 ManageCardPwd[6+1];	
	S8 ActiveInfo[999+1];
	S8* exReqInfo;
}CulAdaptorReqST;

typedef struct
{
	S8 TranType[2+1];
	S8 RespCode[2+1];
	S8 RespInfo[40+1];
	S8 Channel[15+1];
	S8 TranDate[4+1];
	S8 TranTime[6+1];
	S8 CardNo[19+1];
	S8 CardAccount[99+1];
	S8 CardName[20+1];
	S8 SpeDay[16+1];
	S8 Balance[12+1];
	S8 expr[4+1];
	S8 TermNo[8+1];
	S8 MchtNo[15+1];
	S8 MchtName[99+1];
	S8 BatchNo[6+1];
	S8 TraceNo[6+1];
	S8 RefNo[12+1];
	S8 TranAmount[12+1];
	S8 ChannelSaleAmount[12+1];
	S8 MchtSaleAmount[12+1];
	S8 CardDetail[999+1];
	S8 RedeemCount[12+1];
	S8 RedeemAmount[12+1];
	S8 VoidCount[12+1];
	S8 VoidAmount[12+1];
	S8 RefundCount[12+1];
	S8 RefundAmount[12+1];
	S8 ActiveCount[12+1];
	S8 ActiveAmount[12+1];
	S8 ActiveVoidCounts[12+1];
	S8 ActiveVoidAmount[12+1];
	S8* exRspInfo;
}CulAdaptorRspST;

typedef struct
{
	S32 redeem_times;
	S32 redeem_amounts;
	S32 redeem_void_times;
	S32 redeem_void_amounts;
	S32 refund_times;
	S32 refund_amounts;

	S32 active_times;
	S32 active_amounts;
	S32 active_void_times;
	S32 active_void_amounts;
}CulSettleInfoST;

S32 cul_adaptor_interface(S8* strIn,S8* strOut);

#endif
