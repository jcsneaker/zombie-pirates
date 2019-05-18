﻿//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "PirateGame.h"
#include "Shipfight.h"
#include "IntroText.h"
#include "Outro.h"
#include "Wave.h"
#include "Utils/CommandLineParser.h"
#include "ramses-renderer-api/DisplayConfig.h"
#include "RamsesRendererImpl.h"

static const int32_t width = 1480;
static const int32_t height = 980;

PirateGame::PirateGame(int argc, char* argv[])
    : m_parser(argc, argv)
    , m_disableIntroText(m_parser, "ni", "noIntroText", false, "Disable intro text")
    , m_rendererConfig(argc, argv)
    , m_displayConfig(CreateDisplayConfig(argc, argv))
    , m_framework(argc, argv)
    , m_client("ramses-local-client-test", m_framework)
    , m_renderer(m_framework, m_rendererConfig)
    , m_display(m_renderer.createDisplay(m_displayConfig))
{
    Pos2D::SetWindowSize(width, height);
    m_framework.connect();
}

PirateGame::~PirateGame()
{
    m_renderer.destroyDisplay(m_display);
}

void PirateGame::run()
{
    GameEngine engine(m_client, m_renderer, m_display);

    /*if (!m_disableIntroText)
    {
        engine.pushScene();
        {
            IntroText introText(engine);
            introText.goGoPowerRangers();
        }
        engine.popScene();
    }*/

    Wave zombiePiratesSong("res/zombie_pirates.wav");
    zombiePiratesSong.play(true, true);

    engine.pushScene();
    {
        Shipfight shipfight(engine);
        shipfight.goGoPowerRangers();
    }
    /*engine.pushScene();
    {
        Outro outro(engine);
        outro.goGoPowerRangers();
    }
    engine.popScene();*/
}

ramses::DisplayConfig PirateGame::CreateDisplayConfig(int argc, char* argv[])
{
    ramses::DisplayConfig displayConfig(argc, argv);
    displayConfig.setWindowRectangle(0, 25, width, height);
    displayConfig.setOrthographicProjection(0, width * 1.0f, 0, height * 1.0f, -100.0f, 100.0f);

    return displayConfig;
}