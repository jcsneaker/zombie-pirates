//  -------------------------------------------------------------------------
//  Copyright (C) 2018 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_TRIANGLERENDERER_H
#define RAMSES_TRIANGLERENDERER_H

#include "RendererBundle.h"
#include "PirateGame.h"
#include <jni.h>

namespace ramses
{
    class Node;
    class RamsesClient;
    class Scene;
}

class TriangleRenderer {
public:
    TriangleRenderer(JNIEnv *env, jobject instance,
                                 jobject javaSurface, jint width, jint height);

    virtual ~TriangleRenderer();
    void run();

    void frameCallback(long frameTimeNanos);

private:
    ANativeWindow* m_nativeWindow;
    std::unique_ptr<PirateGame> m_game;
    long m_lastFrameTime;
};

#endif
