package com.culmis.zero.culmis;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;

import java.io.UnsupportedEncodingException;

public class ApiActivity extends Activity {
//    public static final int FLAG_HOMEKEY_DISPATCHED = 0x80000000;
    private String ReqString;
    private String RspString;
    private String ReqType;
    private String TranType;

    private String StoreNo;
    private String CashNo;
    private String OrderNo;
    private String ReceiverNo;
    private String ComInfo;
    private String OrderAmount;
    private String Track2;
    private String PassWord;
    private String VerifyCode;
    private String OrgTrace;
    private String OrgBatch;
    private String OrgReference;
    private String OrgDate;
    private String CheckInfo;

    private String RespCode;
    private String RespInfo;
    private String TranDate;
    private String TranTime;
    private String CardNo;
    private String Expr;
    private String CardType;
    private String ZrCard;
    private String JtCard;
    private String SaleStoreNo;
    private String TermNo;
    private String MchtNo;
    private String BatchNo;
    private String TraceNo;
    private String ReferenceNo;
    private String TranAmount;
    private String Balance;
    private String DetailInfo;

    JniInterface jniInterface = new JniInterface();
    protected String addZero(String str,int len)
    {
        String result = str;
        if(str == null)
        {
            if(len == 6) {
                result = "      ";
            }
            else if(len == 12)
            {
                result ="            ";
            }
        }
        while(result.length()<len)
        {
            result="0"+result;
        }
        return result;
    }
    protected String addSpace(String str,int len){
        int spaceNum = 0;
        if(str == null)
        {
            spaceNum = len;
            str = "";
        }
        else {
            try {
                spaceNum = len - str.getBytes("GBK").length;
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
            }
        }
        for(int i=0;i<spaceNum;i++){
            str += " ";
        }
        return str;
    }

    protected int getReqString(Bundle bd){
        ReqString = bd.getString("ReqString");
        return 0;
    }

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
 //       this.getWindow().setFlags(FLAG_HOMEKEY_DISPATCHED, FLAG_HOMEKEY_DISPATCHED);
        setContentView(R.layout.activity_api);
        Intent it = getIntent();
        Bundle bd = it.getExtras();
        getReqString(bd);

        RspString = jniInterface.CulInterface(ReqString);


        Intent testApi = new Intent();
        Bundle bdTestApi = new Bundle();
        bdTestApi.putString("RspString", RspString);

        testApi.putExtras(bdTestApi);
        setResult(RESULT_OK, testApi);
        finish();

    }


    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

       /*
        if(keyCode == KeyEvent.KEYCODE_BACK ||keyCode == KeyEvent.KEYCODE_HOME){
            return true;
        }
        */

        return true;
    }
    public void onBackPressed() {
    //    setResult(Const.LIVE_OK);
        super.onBackPressed();
    }
//    public void onAttachedToWindow() {
    //      this.getWindow().setType(WindowManager.LayoutParams.TYPE_KEYGUARD_DIALOG);
    //     super.onAttachedToWindow();
    //   }
}