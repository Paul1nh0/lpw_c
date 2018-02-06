package com.culmis.zero.culmis;

/**
 * Created by Zero on 2016/5/5.
 */
public class JniInterface {

        static{ //载入名为“CulInterface”的C++库
            System.loadLibrary("CulInterface");
        }
        public native String CulInterface(String strTranInfo); //调用库里的方法“cul_interface”
        public native String GetCfg();
        public native int SetCfg(String strCfg);

}
