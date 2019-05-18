//  -------------------------------------------------------------------------
//  Copyright (C) 2018 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "SceneViewerBundle.h"

#include <android/log.h>

#include "ramses-client.h"
#include "RamsesObjectTypeUtils.h"


SceneViewerBundle::SceneViewerBundle(JNIEnv *env, jobject instance,
        jobject javaSurface, jint width, jint height, const char* sceneFile, const char* resFile)
: RendererBundle(env, instance, javaSurface, width, height, "127.0.0.1", "127.0.0.1")
{
    m_client.reset(new ramses::RamsesClient("client-scene-reader", *m_framework));

    ramses::ResourceFileDescriptionSet resourceFileInformation;
    resourceFileInformation.add(ramses::ResourceFileDescription(resFile));
    m_loadedScene = m_client->loadSceneFromFile(sceneFile, resourceFileInformation);
    if (m_loadedScene == nullptr)
    {
        __android_log_print(ANDROID_LOG_ERROR, "RamsesNativeInterface", "Loading scene failed!");
    }
}

SceneViewerBundle::~SceneViewerBundle()
{
};

void SceneViewerBundle::run()
{
    m_loadedScene->publish();
    m_loadedScene->flush();
    RendererBundle::run();
}

ramses::Node* SceneViewerBundle::findNodeByName(const char* name)
{
    ramses::RamsesObject* rootObject = m_loadedScene->findObjectByName(name);
    return &ramses::RamsesObjectTypeUtils::ConvertTo<ramses::Node>(*rootObject);
}

void SceneViewerBundle::flushScene()
{
    m_loadedScene->flush();
}

UniformInputWrapper* SceneViewerBundle::findUniformInput(const char* appearanceName, const char* inputName)
{
    ramses::RamsesObject* appearanceObj = m_loadedScene->findObjectByName(appearanceName);
    ramses::Appearance& appearance = ramses::RamsesObjectTypeUtils::ConvertTo<ramses::Appearance>(*appearanceObj);
    return new UniformInputWrapper(inputName, appearance);
}
