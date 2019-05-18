#include <jni.h>
#include <android/log.h>

#include "android/asset_manager.h"
#include <android/asset_manager_jni.h>
#include "ramses-capu/os/File.h"
#include "NativeGameLifecycle.h"


extern "C"
JNIEXPORT void JNICALL
Java_de_zombiepirates_GameRenderer_load(JNIEnv *env, jobject obj, jobject assetManager){
    AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);
    android_fopen_set_asset_manager(mgr);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_de_zombiepirates_GameRenderer_createGameNative(JNIEnv *env, jobject instance,
                                                             jobject surface, jint width,
                                                             jint height) {
    NativeGameLifecycle* tr = new NativeGameLifecycle(
            env, instance, surface, width, height);

    tr->run();
    return reinterpret_cast<jlong>(tr);
}

extern "C"
JNIEXPORT void JNICALL
Java_de_zombiepirates_GameRenderer_disposeGameNative(JNIEnv* /*env*/, jobject /*instance*/,
                                                              jlong handle) {
    delete reinterpret_cast<NativeGameLifecycle*>(handle);
}
