//  -------------------------------------------------------------------------
//  Copyright (C) 2018 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "RendererBundle.h"

#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "ramses-renderer-api/RamsesRenderer.h"
#include "Window_Android/Window_Android.h"
#include "ramses-renderer-api/DisplayConfig.h"
#include <ramses-framework-api/RamsesFramework.h>


RendererBundle::RendererBundle(JNIEnv *env, jobject /*instance*/,
    jobject javaSurface, jint width, jint height, const char* interfaceSelectionIP, const char* daemonIP)
{
    m_nativeWindow = ANativeWindow_fromSurface(env, javaSurface);
    ramses_internal::Window_Android::SetNativeWindow(m_nativeWindow);

    ramses::RamsesFrameworkConfig frameworkConfig;
    frameworkConfig.setInterfaceSelectionIPForTCPCommunication(interfaceSelectionIP);
    frameworkConfig.setDaemonIPForTCPCommunication(daemonIP);
    m_framework = new ramses::RamsesFramework(frameworkConfig);
    ramses::RendererConfig rendererConfig;
    m_renderer = new ramses::RamsesRenderer(*m_framework, rendererConfig);

    m_displayManager = new ramses_display_manager::DisplayManager(*m_renderer, *m_framework, true);
    m_displayManagerRunnable = new DisplayManagerRunnable(m_displayManager);
    m_displayManagerThread = new ramses_internal::PlatformThread("DMThread");

    ramses::DisplayConfig displayConfig;
    displayConfig.setWindowRectangle(0, 0, width, height);
    displayConfig.setPerspectiveProjection(19.f, static_cast<float>(width)/static_cast<float>(height), 0.1f, 1500.f);
    m_displayManager->createDisplay(displayConfig);
}

RendererBundle::~RendererBundle()
{
    m_displayManagerRunnable->cancel();
    m_displayManagerThread->join();

    delete m_displayManagerThread;
    delete m_displayManagerRunnable;
    delete m_displayManager;
    delete m_renderer;
    delete m_framework;
    ANativeWindow_release(m_nativeWindow);
};

void RendererBundle::connect()
{
    m_framework->connect();
}

void RendererBundle::run()
{
    m_renderer->setMaximumFramerate(60);
    m_renderer->startThread();
    m_displayManagerThread->start(*m_displayManagerRunnable);
}

void RendererBundle::doOneLoop()
{
    m_displayManager->dispatchAndFlush();
    m_renderer->doOneLoop();
}
