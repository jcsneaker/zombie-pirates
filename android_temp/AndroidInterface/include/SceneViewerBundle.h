//  -------------------------------------------------------------------------
//  Copyright (C) 2018 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_SCENEVIEWERBUNDLE_H
#define RAMSES_SCENEVIEWERBUNDLE_H

#include "RendererBundle.h"
#include "UniformInputWrapper.h"


namespace ramses
{
    class Node;
    class RamsesClient;
    class Scene;
}

class SceneViewerBundle : public RendererBundle {
public:
    SceneViewerBundle(JNIEnv *env, jobject instance,
                                 jobject javaSurface, jint width, jint height,
                                 const char *sceneFile, const char *resFile);

    virtual ~SceneViewerBundle();

    virtual void run() override;

    ramses::Node* findNodeByName(const char *name);

    void flushScene();

    UniformInputWrapper* findUniformInput(const char* appearanceName, const char* inputName);

private:
    std::unique_ptr<ramses::RamsesClient> m_client;
    ramses::Scene* m_loadedScene;
};

#endif
