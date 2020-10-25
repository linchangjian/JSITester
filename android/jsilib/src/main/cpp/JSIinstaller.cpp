//
// Created by Aniu on 2020/10/25.
//


#include "JSIinstaller.h"
using namespace facebook;

JavaVM *jvm;

static jobject globalJObject;

static jclass globalClazz;

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
                    auto str = (jstring)env->CallStaticObjectMethod(globalClazz, runTest);

                    const char *cStr = env->GetStringUTFChars(str, nullptr);

                    return jsi::String::createFromAscii(runtime, cStr);
                });
    }



    return jsi::Value::undefined();
}