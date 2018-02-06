package com.culmis.zero.culmis;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

public class MainActivity extends AppCompatActivity {

    protected void delete_file(String srcFileName) {
        File file = null;
        boolean result = false;
        try {
            file = new File(srcFileName);
            if (file.exists()) {
                result  = file.delete();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    protected void makeDir(String srcFilePath) {
        File file = null;
        try {
            file = new File(srcFilePath);
            if (!file.exists()) {
                file.mkdir();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    protected void copyFile(String srcFileName,String dstFileName) throws IOException {
        InputStream is = null;
        try {
            is = getResources().getAssets().open(srcFileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
        File saveFile = new File(dstFileName);
        if(saveFile.exists()==true){
            is.close();
            return;
        }
        OutputStream os = null;
        try {
            os = new FileOutputStream(saveFile);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        byte[] buf = new byte[1024000];
        int red = -1;
        try {
            while((red=is.read(buf))!=-1){
                os.write(buf);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        is.close();
        os.close();

    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        makeDir("/data/data/com.culmis.zero.culmis/cul/");
        makeDir("/data/data/com.culmis.zero.culmis/cul_log/");
    //    makeDir("/mnt/sdcard/cul_receipt/");
        try {
            copyFile("cul_pos.ini","/data/data/com.culmis.zero.culmis/cul_pos.ini");
        } catch (IOException e) {
            e.printStackTrace();
        }

        Button btnSetting = (Button)findViewById(R.id.idbSetting);
        assert btnSetting != null;
        btnSetting.setOnClickListener(new View.OnClickListener() {
            //重载
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, SettingActivity.class);
                startActivity(intent);
            }
        });
        Button btnLog = (Button)findViewById(R.id.idbRecovery);
        assert btnLog != null;
        btnLog.setOnClickListener(new View.OnClickListener() {
            //重载
            public void onClick(View v) {
                delete_file("/data/data/com.culmis.zero.culmis/cul_pos.ini");
                try {
                    copyFile("cul_pos.ini","/data/data/com.culmis.zero.culmis/cul_pos.ini");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
