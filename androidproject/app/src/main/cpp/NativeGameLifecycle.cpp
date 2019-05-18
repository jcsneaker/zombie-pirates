#include <android/log.h>
#include <android/choreographer.h>

#include "NativeGameLifecycle.h"
#include "RamsesObjectTypeUtils.h"
#include "Window_Android/Window_Android.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "PirateGame.h"

void mycallback(long frameTimeNanos, void *data)
{
   //TODO make thread save and stop registering new callback if stop requested

   static_cast<NativeGameLifecycle*>(data)->frameCallback(frameTimeNanos);
   AChoreographer* choreographer = AChoreographer_getInstance();
   AChoreographer_postFrameCallback(choreographer, mycallback, data);
}


NativeGameLifecycle::NativeGameLifecycle(JNIEnv *env, jobject instance,
        jobject javaSurface, jint width, jint height)
{
    m_nativeWindow = ANativeWindow_fromSurface(env, javaSurface);
    ramses_internal::Window_Android::SetNativeWindow(m_nativeWindow);
    m_game.reset(new PirateGame(width, height));

}

NativeGameLifecycle::~NativeGameLifecycle()
{
    ANativeWindow_release(m_nativeWindow);
};

void NativeGameLifecycle::run()
{
    AChoreographer* choreographer = AChoreographer_getInstance();
    AChoreographer_postFrameCallback(choreographer, mycallback, this);
}


void NativeGameLifecycle::frameCallback(long frameTimeNanos)
{
    m_game->doFrame();
}

