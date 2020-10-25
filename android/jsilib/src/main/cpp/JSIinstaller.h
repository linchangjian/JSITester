#pragma once
//
// Created by Aniu on 2020/10/25.
//

#ifndef REACTNATIVEJSITESTER_JSIINSTALLER_H
#define REACTNATIVEJSITESTER_JSIINSTALLER_H

//
#include <jni.h>
#include "../../../../../node_modules/react-native/ReactCommon/jsi/jsi/jsi.h"
#include <string>
#include <android/log.h>
using namespace facebook;


class JSIinstaller : public jsi::HostObject{
public:
    JSIinstaller();
    static void install(jsi::Runtime &runtime,
            const std::shared_ptr<JSIinstaller> jsiInstaller);

    jsi::Value get(jsi::Runtime &runtime, const jsi::PropNameID &name) override ;


private:
    JNIEnv jniEnv_;
};


#endif //REACTNATIVEJSITESTER_JSIINSTALLER_H
