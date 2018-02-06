package com.culmis.zero.culmis;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;

public class TraceActivity extends AppCompatActivity {

    private Spinner spCity = null;
    private ArrayAdapter<CharSequence> adapterCity = null;
    private static String[] cityInfo={"所有交易类型","签到","结算","查询","消费","消费撤销","退货","退货撤销"};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_trace);

//初始化函数中代码如下
        this.spCity = (Spinner) super.findViewById(R.id.spinnerCity);
//将数据cityInfo填充到适配器adapterCity中
        this.adapterCity = new ArrayAdapter<CharSequence>(this,
                android.R.layout.simple_spinner_dropdown_item, cityInfo);
//设置下拉框的数据适配器adapterCity
        this.spCity.setAdapter(adapterCity);
        spCity.setSelection(0);
        Button btnVoid = (Button)findViewById(R.id.idbVoid);
        assert btnVoid != null;
        btnVoid.setOnClickListener(new View.OnClickListener() {
            //重载
            public void onClick(View v) {
                finish();
            }
        });
        Button btnSure = (Button)findViewById(R.id.idbInquire);
        assert btnSure != null;
        btnSure.setOnClickListener(new View.OnClickListener() {
            //重载
            public void onClick(View v) {

            }
        });
    }

}
