//  -------------------------------------------------------------------------
//  Copyright (C) 2018 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include <jni.h>
#include <android/log.h>

#include "RendererBundle.h"
#include "ramses-client.h"
#include "TriangleRenderer.h"
#include "android/asset_manager.h"
#include <android/asset_manager_jni.h>
#include "ramses-capu/os/File.h"


extern "C"
JNIEXPORT void JNICALL
Java_de_zombiepirates_load(JNIEnv *env, jobject obj, jobject assetManager){
    AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);
    if (mgr == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "name.cpp", "error loading asset manager");
    } else {
        __android_log_print(ANDROID_LOG_VERBOSE, "name.cpp", "loaded asset manager");
        android_fopen_set_asset_manager(mgr);
    }

}

extern "C"
JNIEXPORT jlong JNICALL
Java_de_zombiepirates_GameRenderer_createGameNative(JNIEnv *env, jobject instance,
                                                             jobject surface, jint width,
                                                             jint height) {

    TriangleRenderer* tr = new TriangleRenderer(
            env, instance, surface, width, height);

    //tr->connect();
    tr->run();
    return reinterpret_cast<jlong>(tr);
}

extern "C"
JNIEXPORT void JNICALL
Java_de_zombiepirates_GameRenderer_disposeGameNative(JNIEnv* /*env*/, jobject /*instance*/,
                                                              jlong handle) {
    delete reinterpret_cast<TriangleRenderer*>(handle);
}
