package com.aniu.jsilib;

public class NativeFunCallUtils {

    public static native String stringFromJNI();

    public static native void installJSI(long javaScriptContextHolder);

    public static String runTest() {
        return "linchangjian string from jsi ";
    }

    public static String runTest2(String module, String msg) {
        return "linchangjian string from jsi "+module+":"+msg;
    }
}
