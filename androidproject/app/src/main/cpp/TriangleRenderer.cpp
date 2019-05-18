//  -------------------------------------------------------------------------
//  Copyright (C) 2018 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "TriangleRenderer.h"

#include <android/log.h>
#include <android/choreographer.h>

#include "ramses-client.h"
#include "RamsesObjectTypeUtils.h"
#include "Window_Android/Window_Android.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "PirateGame.h"

void mycallback(long frameTimeNanos, void *data)
{
   //TODO make thread save and stop registering new callback if stop requested

   //__android_log_print(ANDROID_LOG_ERROR, "RamsesNativeInterface", "Callback called! frame time %li data %p", frameTimeNanos, data);
   static_cast<TriangleRenderer*>(data)->frameCallback(frameTimeNanos);
   AChoreographer* choreographer = AChoreographer_getInstance();
   //__android_log_print(ANDROID_LOG_ERROR, "RamsesNativeInterface", "AChoreographer_getInstance returned %p", choreographer);
   AChoreographer_postFrameCallback(choreographer, mycallback, data);
}


TriangleRenderer::TriangleRenderer(JNIEnv *env, jobject instance,
        jobject javaSurface, jint width, jint height)
{
    m_nativeWindow = ANativeWindow_fromSurface(env, javaSurface);
    ramses_internal::Window_Android::SetNativeWindow(m_nativeWindow);
    m_game.reset(new PirateGame(width, height));
//__android_log_print(ANDROID_LOG_ERROR, "RamsesNativeInterface", "Loading scene failed!");

}

TriangleRenderer::~TriangleRenderer()
{

    ANativeWindow_release(m_nativeWindow);
};

void TriangleRenderer::run()
{
    AChoreographer* choreographer = AChoreographer_getInstance();
    __android_log_print(ANDROID_LOG_ERROR, "RamsesNativeInterface", "AChoreographer_getInstance returned %p", choreographer);
    AChoreographer_postFrameCallback(choreographer, mycallback, this);
}


void TriangleRenderer::frameCallback(long frameTimeNanos)
{

    //long timeDiffNanos = frameTimeNanos - m_lastFrameTime;
    //float rotateAngle = timeDiffNanos / 1000000000.f * 360;
    __android_log_print(ANDROID_LOG_ERROR, "RamsesNativeInterface", "doframe ass");
    m_game->doFrame();

    //RendererBundle::doOneLoop();

    m_lastFrameTime = frameTimeNanos;
}

