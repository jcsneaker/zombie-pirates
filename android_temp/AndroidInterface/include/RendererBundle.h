//  -------------------------------------------------------------------------
//  Copyright (C) 2018 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_RENDERERBUNDLE_H
#define RAMSES_RENDERERBUNDLE_H

#include <jni.h>
#include "PlatformAbstraction/PlatformThread.h"
#include "DisplayManager/DisplayManager.h"

namespace ramses
{
    class RamsesFramework;
    class RamsesRenderer;
}

class ANativeWindow;

class RendererBundle
{
public:
    RendererBundle(JNIEnv *env, jobject /*instance*/,
                   jobject javaSurface, jint width, jint height,
                   const char* interfaceSelectionIP, const char* daemonIP);

    virtual ~RendererBundle();
    virtual void connect();
    virtual void run();
    virtual void doOneLoop();

    class DisplayManagerRunnable : public ramses_internal::Runnable
    {
    public:
        explicit DisplayManagerRunnable(ramses_display_manager::DisplayManager* displayManager)
                : m_displayManager(displayManager)
        {
        }

        ~DisplayManagerRunnable()
        {
        }

        virtual void run()
        {
            while (!isCancelRequested())
            {
                m_displayManager->dispatchAndFlush();
                ramses_internal::PlatformThread::Sleep(100u);
            }
        }

    private:
        ramses_display_manager::DisplayManager* m_displayManager;
    };

protected:
    ANativeWindow* m_nativeWindow;
    ramses::RamsesFramework* m_framework;
    ramses::RamsesRenderer* m_renderer;
    ramses_display_manager::DisplayManager* m_displayManager;
    DisplayManagerRunnable* m_displayManagerRunnable;
    ramses_internal::PlatformThread* m_displayManagerThread;
};

#endif
