//
// Created by Aniu on 2020/10/25.
//


#include "JSIinstaller.h"
using namespace facebook;

JavaVM *jvm;
static jobject globalJObject;

static jclass globalClazz;

class dynamic;

extern "C" JNIEXPORT jstring JNICALL
Java_com_aniu_jsilib_NativeFunCallUtils_stringFromJNI(
        JNIEnv* env,
        jobject) {
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}

JSIinstaller::JSIinstaller() {

}



//
extern "C"
JNIEXPORT void JNICALL
Java_com_aniu_jsilib_NativeFunCallUtils_installJSI(JNIEnv *env, jclass thiz,
                                                   jlong java_script_context_holder) {
    // TODO: implement installJSI()

    auto &runtiem = *(jsi::Runtime *)java_script_context_holder;
    auto jsiBinding = std::make_shared<JSIinstaller>();
    JSIinstaller::install(runtiem,jsiBinding);

    env->GetJavaVM(&jvm);

    globalJObject = env->NewGlobalRef(thiz);

    auto clazz = env->FindClass("com/aniu/jsilib/NativeFunCallUtils");

    globalClazz = (jclass)env->NewGlobalRef(clazz);

}


void JSIinstaller::install(
        jsi::Runtime &runtime,
        const std::shared_ptr<JSIinstaller> jsiInstaller) {
    auto logModuleName = "ztlong";
    auto object = jsi::Object::createFromHostObject(runtime, jsiInstaller);

    runtime.global().setProperty(runtime,logModuleName, std::move(object));
}


JNIEnv *attachCurrentThread()
{
    JavaVMAttachArgs args{JNI_VERSION_1_6, nullptr, nullptr};
    JNIEnv *env = nullptr;
    auto result = jvm->AttachCurrentThread(&env, &args);
    return env;
}


jsi::Value JSIinstaller::get(
        jsi::Runtime &runtime,
        const jsi::PropNameID &name)
{
    auto methodName = name.utf8(runtime);

    if (methodName == "getStaticField")
    {
        return jsi::Function::createFromHostFunction(
                runtime,
                name,
                0,
                [](
                        jsi::Runtime &runtime,
                        const jsi::Value &thisValue,
                        const jsi::Value *arguments,
                        size_t count) -> jsi::Value {
                    auto env = attachCurrentThread();
                    auto runTest = env->GetStaticMethodID(globalClazz, "runTest", "()Ljava/lang/String;");
                    const jsi::String &arg0 = arguments[0].getString(runtime);
                    const jsi::String &arg1 = arguments[1].getString(runtime);
                    __android_log_print(ANDROID_LOG_INFO,"linchangjian","arguments[0] %s ,arguments[1] %s",arg0.utf8(runtime).c_str(),arg1.utf8(runtime).c_str());
                    auto str = (jstring)env->CallStaticObjectMethod(globalClazz, runTest);
                    auto runTest2 = env->GetStaticMethodID(globalClazz, "runTest2",
                                                           "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
                    auto str2 = (jstring)env->CallStaticObjectMethod(globalClazz,runTest2,env->NewStringUTF(arg0.utf8(runtime).c_str()),env->NewStringUTF(arg1.utf8(runtime).c_str()));
                    const char *cStr = env->GetStringUTFChars(str2, nullptr);
                    return jsi::String::createFromAscii(runtime, cStr);
                });
    }

    return jsi::Value::undefined();
}