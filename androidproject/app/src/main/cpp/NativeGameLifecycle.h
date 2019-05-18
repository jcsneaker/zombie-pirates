#ifndef NATIVEGAMELIFECYCLE_H
#define NATIVEGAMELIFECYCLE_H

#include "PirateGame.h"
#include <jni.h>

class ANativeWindow;

class NativeGameLifecycle {
public:
    NativeGameLifecycle(JNIEnv *env, jobject instance,
                                 jobject javaSurface, jint width, jint height);

    virtual ~NativeGameLifecycle();
    void run();

    void frameCallback(long frameTimeNanos);

private:
    ANativeWindow* m_nativeWindow;
    std::unique_ptr<PirateGame> m_game;
};

#endif
