package com.ndktesti.zero.ndktest;

/**
 * Created by Zero on 2017/7/31.
 */
public class JniUtil {
    static {
        System.loadLibrary("JniUtil");
    }

    public static native String getJniString();

    public static native int getJniAdd(int a, int b);
}
