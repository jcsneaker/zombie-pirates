//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_PIRATEGAME_H
#define RAMSES_PIRATEGAME_H

#include "Utils/CommandLineParser.h"
#include "ramses-renderer-api/DisplayConfig.h"
#include "ramses-renderer-api/RendererConfig.h"
#include "ramses-framework-api/RamsesFramework.h"
#include "ramses-client-api/RamsesClient.h"
#include "ramses-renderer-api/RamsesRenderer.h"
#include "Utils/Argument.h"
#include "GameEngine.h"
#include "Shipfight.h"

class PirateGame
{
public:
    PirateGame(int argc, char* argv[], uint32_t width, uint32_t height);
    ~PirateGame();

    void doFrame();
    bool finished() const;

private:
    static ramses::DisplayConfig CreateDisplayConfig(int argc, char* argv[], uint32_t width, uint32_t height);

    ramses_internal::CommandLineParser       m_parser;
    ramses_internal::ArgumentBool m_disableIntroText;
    ramses::RendererConfig  m_rendererConfig;
    ramses::DisplayConfig   m_displayConfig;

    ramses::RamsesFramework m_framework;
    ramses::RamsesClient    m_client;
    ramses::RamsesRenderer  m_renderer;

    ramses::displayId_t     m_display;

    ramses_internal::GameEngine m_engine;
    std::unique_ptr<Shipfight> m_shipFight;
};

#endif
