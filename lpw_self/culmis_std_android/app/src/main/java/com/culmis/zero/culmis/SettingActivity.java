package com.culmis.zero.culmis;

import java.lang.String;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;

public class SettingActivity extends AppCompatActivity {

    EditText[] editText = new EditText[9];

    JniInterface jniInterface = new JniInterface();
    protected String addSpace(String str,int len){
        int spaceNum = 0;
        spaceNum = len-str.getBytes().length;
        for(int i=0;i<spaceNum;i++){
            str += " ";
        }
        return str;
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_setting);
        String strCfg = jniInterface.GetCfg();
        for(int i =0;i<9;i++)
        {
            editText[i] =(EditText)findViewById(R.id.idet0MchtNo+i);
        }
        String string1 = strCfg.replaceAll("\\s{1,}", " ");
        String spliteS[] = string1.split(" ");
        for(int i = 0;i<9;i++)
        {
            editText[i].setText(spliteS[i]);
        }
        Button btnCertain = (Button)findViewById(R.id.idbCertain);
        assert btnCertain != null;
        btnCertain.setOnClickListener(new View.OnClickListener() {
            //重载
            public void onClick(View v) {
                int result = -1;
                String strReq[] = new String[9];
                String strRequest ="";
                for(int i = 0;i<9;i++)
                {
                    strReq[i] = "";
                    strReq[i] += editText[i].getText();
                }
                strReq[0]=addSpace(strReq[0],8);
                strReq[1]=addSpace(strReq[1],15);
                strReq[2]=addSpace(strReq[2],15);
                strReq[3]=addSpace(strReq[3],5);
                strReq[4]=addSpace(strReq[4],10);
                strReq[5]=addSpace(strReq[5],3);

                strReq[6]=addSpace(strReq[6],1);
                strReq[7]=addSpace(strReq[7],6);
                strReq[8]=addSpace(strReq[8],99);
                for(int j= 0;j<9;j++)
                {
                    strRequest += strReq[j];
                    strRequest += " ";
                }
                //  jniInterface.culinterface("12345678");
                result = jniInterface.SetCfg(strRequest);
                finish();
            }
        });
        Button btnGiveup = (Button)findViewById(R.id.idbGiveup);
        assert btnGiveup != null;
        btnGiveup.setOnClickListener(new View.OnClickListener() {
            //重载
            public void onClick(View v) {
                finish();
            }
        });
    }


}
