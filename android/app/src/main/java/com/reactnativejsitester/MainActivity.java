package com.reactnativejsitester;

import android.os.Bundle;

import com.aniu.jsilib.NativeFunCallUtils;
import com.facebook.react.NativeModuleRegistryBuilder;
import com.facebook.react.ReactActivity;

public class MainActivity extends ReactActivity {

  // Used to load the 'native-lib' library on application startup.
  static {
    System.loadLibrary("native-lib");
  }


  /**
   * Returns the name of the main component registered from JavaScript. This is used to schedule
   * rendering of the component.
   */
  @Override
  protected String getMainComponentName() {
    return "ReactNativeJSITester";
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    System.out.println(NativeFunCallUtils.stringFromJNI());
  }
}
