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

namespace ramses
{
    class Node;
    class RamsesClient;
    class Scene;
}

class TriangleRenderer : public RendererBundle {
public:
    TriangleRenderer(JNIEnv *env, jobject instance,
                                 jobject javaSurface, jint width, jint height);

    virtual ~TriangleRenderer();

    virtual void run() override;

    void frameCallback(long frameTimeNanos);

private:
    std::unique_ptr<ramses::RamsesClient> m_client;
    ramses::Scene* m_scene;
    ramses::Node* m_rotateNode;
    long m_lastFrameTime;
};

#endif
