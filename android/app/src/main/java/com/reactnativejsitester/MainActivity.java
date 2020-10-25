package com.reactnativejsitester;

import android.os.Bundle;

import com.aniu.jsilib.NativeFunCallUtils;
import com.facebook.react.NativeModuleRegistryBuilder;
import com.facebook.react.ReactActivity;
import com.facebook.react.ReactInstanceManager;
import com.facebook.react.bridge.ReactContext;

public class MainActivity extends ReactActivity implements ReactInstanceManager.ReactInstanceEventListener {

  // Used to load the 'native-lib' library on application startup.
  static {
    System.loadLibrary("jsi-lib");
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

  @Override
  protected void onPause() {
    super.onPause();
    getReactInstanceManager().addReactInstanceEventListener(this);
  }

  @Override
  protected void onResume() {
    super.onResume();
    getReactInstanceManager().addReactInstanceEventListener(this);
  }

  @Override
  public void onReactContextInitialized(ReactContext context) {
    NativeFunCallUtils.installJSI(context.getJavaScriptContextHolder().get());
  }

  @Override
  public void onPointerCaptureChanged(boolean hasCapture) {

  }
}
