//  -------------------------------------------------------------------------
//  Copyright (C) 2018 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include <jni.h>

#include "RendererBundle.h"
#include "ramses-client.h"
#include "TriangleRenderer.h"


extern "C"
JNIEXPORT jlong JNICALL
Java_de_bmw_ramses_RamsesTriangleRenderer_createTriangleRendererNative(JNIEnv *env, jobject instance,
                                                             jobject surface, jint width,
                                                             jint height) {
    TriangleRenderer* tr = new TriangleRenderer(
            env, instance, surface, width, height);

    tr->connect();
    tr->run();
    return reinterpret_cast<jlong>(tr);
}

extern "C"
JNIEXPORT void JNICALL
Java_de_bmw_ramses_RamsesTriangleRenderer_disposeTriangleRendererNative(JNIEnv* /*env*/, jobject /*instance*/,
                                                              jlong handle) {
    delete reinterpret_cast<TriangleRenderer*>(handle);
}
