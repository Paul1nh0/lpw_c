package com.culmis.zero.culmis;

/**
 * Created by Zero on 2016/5/5.
 */
public class JniInterface {

        static{
            System.loadLibrary("CulInterface");
        }
        public native String CulInterface(String strTranInfo); 
        public native String GetCfg();
        public native int SetCfg(String strCfg);

}
