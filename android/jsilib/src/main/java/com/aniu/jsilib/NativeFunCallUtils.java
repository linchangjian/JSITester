package com.aniu.jsilib;

public class NativeFunCallUtils {

    public static native String stringFromJNI();

    public static native void installJSI(long javaScriptContextHolder);

    public static String runTest() {
        return "linchangjian string from jsi ";
    }
}
