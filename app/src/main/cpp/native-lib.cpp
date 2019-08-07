#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <iostream>
#include <string>
#include <android/log.h>

#include <stdio.h>
#include <dirent.h>

#define LIB_PATH "lib-BinderInterfaceFuzzPlug.so"

//std::function<void()> setup;
//std::function<void()> random_call_collect;
//std::function<void()> simple_random_call_collect;

typedef void (*fptr)();

fptr setup;
fptr random_call_collect;
fptr simple_random_call_collect;

#define TAG "native-lib"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_cts_androiddriverfuzzer_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_cts_androiddriverfuzzer_MainActivity_simpleRandomCallCollect(
        JNIEnv *env,
        jobject ){
    simple_random_call_collect();
}

extern "C" JNIEXPORT void JNICALL
Java_com_cts_androiddriverfuzzer_MainActivity_randomCallCollect(
        JNIEnv *env,
        jobject ){
    random_call_collect();
}

extern "C" JNIEXPORT void JNICALL
Java_com_cts_androiddriverfuzzer_MainActivity_test(
        JNIEnv *env,
        jobject ) {
    LOGD("start jni layer test");
    void *libHandle = dlopen(LIB_PATH, RTLD_NOW | RTLD_LOCAL);

    if (libHandle) {
        setup = (fptr)dlsym(libHandle, "setup");
        if(!setup){
            LOGE("get function setup fail");
        }
        setup();
        random_call_collect = (fptr) dlsym(libHandle, "random_call_collect");
        if(!random_call_collect){
            LOGE("get function random_call_collect fail");
        }
        simple_random_call_collect=(fptr)dlsym(libHandle, "simple_random_call_collect");
        if(!simple_random_call_collect){
            LOGE("get function simple_random_call_collect fail");
        }
    }
    else{
        LOGE("dl open fail");
    }
}
