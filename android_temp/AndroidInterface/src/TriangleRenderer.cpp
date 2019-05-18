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
: RendererBundle(env, instance, javaSurface, width, height, "127.0.0.1", "127.0.0.1")
{
    m_client.reset(new ramses::RamsesClient("triangle-client", *m_framework));
//__android_log_print(ANDROID_LOG_ERROR, "RamsesNativeInterface", "Loading scene failed!");

    m_scene = m_client->createScene(123u, ramses::SceneConfig(), "basic geometry scene");

    ramses::Camera* camera = m_scene->createRemoteCamera("my camera");
    camera->setTranslation(0.0f, 0.0f, 5.0f);
    ramses::RenderPass* renderPass = m_scene->createRenderPass("my render pass");
    renderPass->setClearFlags(ramses::EClearFlags_None);
    renderPass->setCamera(*camera);
    ramses::RenderGroup* renderGroup = m_scene->createRenderGroup();
    renderPass->addRenderGroup(*renderGroup);

    float vertexPositionsArray[] = { -1.f, 0.f, -1.f, 1.f, 0.f, -1.f, 0.f, 1.f, -1.f };
    const ramses::Vector3fArray* vertexPositions = m_client->createConstVector3fArray(3, vertexPositionsArray);

    ramses::EffectDescription effectDesc;

    effectDesc.setVertexShader(R"#(#version 100
uniform highp mat4 mvpMatrix;
attribute vec3 a_position;
void main() {
gl_Position = mvpMatrix * vec4(a_position, 1.0);
})#");
        effectDesc.setFragmentShader(R"#(#version 100
uniform highp vec4 color;
void main(void) {
gl_FragColor = color;
})#");

    effectDesc.setUniformSemantic("mvpMatrix", ramses::EEffectUniformSemantic_ModelViewProjectionMatrix);

    const ramses::Effect* effect = m_client->createEffect(effectDesc, ramses::ResourceCacheFlag_DoNotCache, "glsl shader");
    ramses::Appearance* appearance = m_scene->createAppearance(*effect, "triangle appearance");

    ramses::GeometryBinding* geometry = m_scene->createGeometryBinding(*effect, "triangle geometry");
    ramses::AttributeInput positionsInput;
    effect->findAttributeInput("a_position", positionsInput);
    geometry->setInputBuffer(positionsInput, *vertexPositions);

    ramses::UniformInput colorInput;
    effect->findUniformInput("color", colorInput);
    appearance->setInputValueVector4f(colorInput, 1.0f, 0.0f, 0.0f, 1.0f);

    ramses::MeshNode* meshNode = m_scene->createMeshNode("triangle mesh node");
    meshNode->setAppearance(*appearance);
    meshNode->setIndexCount(3);
    meshNode->setGeometryBinding(*geometry);

    m_rotateNode = m_scene->createNode();
    meshNode->setParent(*m_rotateNode);

    renderGroup->addMeshNode(*meshNode);
}

TriangleRenderer::~TriangleRenderer()
{
   m_scene->unpublish();
   m_client->destroy(*m_scene);
};

void TriangleRenderer::run()
{
    m_scene->publish();
    m_scene->flush();
    AChoreographer* choreographer = AChoreographer_getInstance();
    __android_log_print(ANDROID_LOG_ERROR, "RamsesNativeInterface", "AChoreographer_getInstance returned %p", choreographer);
    AChoreographer_postFrameCallback(choreographer, mycallback, this);
}

void TriangleRenderer::frameCallback(long frameTimeNanos)
{
    long timeDiffNanos = frameTimeNanos - m_lastFrameTime;
    float rotateAngle = timeDiffNanos / 1000000000.f * 30;
    //__android_log_print(ANDROID_LOG_ERROR, "RamsesNativeInterface", "calculated rotateAngle %f", rotateAngle);
    m_rotateNode->rotate(0.f, 0.f, rotateAngle);
    m_scene->flush();

    RendererBundle::doOneLoop();

    m_lastFrameTime = frameTimeNanos;
}

