//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "PirateGame.h"
#include "IntroText.h"
#include "Outro.h"
#include "Wave.h"
#include "Utils/CommandLineParser.h"
#include "ramses-renderer-api/DisplayConfig.h"
#include "RamsesRendererImpl.h"

PirateGame::PirateGame(int argc, char* argv[], uint32_t width, uint32_t height)
    : m_parser(argc, argv)
    , m_disableIntroText(m_parser, "ni", "noIntroText", false, "Disable intro text")
    , m_rendererConfig(argc, argv)
    , m_displayConfig(CreateDisplayConfig(argc, argv, width, height))
    , m_framework(argc, argv)
    , m_client("ramses-local-client-test", m_framework)
    , m_renderer(m_framework, m_rendererConfig)
    , m_display(m_renderer.createDisplay(m_displayConfig))
    , m_engine(m_client, m_renderer, m_display)
{
    Pos2D::SetWindowSize(width, height);
    m_framework.connect();

    m_engine.pushScene();

    m_shipFight.reset(new Shipfight(m_engine));
}

PirateGame::~PirateGame()
{
    m_engine.popScene();

    m_renderer.destroyDisplay(m_display);
}

void PirateGame::doFrame()
{
    m_shipFight->step();
}

bool PirateGame::finished() const
{
    return m_shipFight->fightIsOver();
}

/*
void PirateGame::run()
{

    if (!m_disableIntroText)
    {
        engine.pushScene();
        {
            IntroText introText(engine);
            introText.goGoPowerRangers();
        }
        engine.popScene();
    }

    //Wave zombiePiratesSong("res/zombie_pirates.wav");
    //zombiePiratesSong.play(true, true);

    m_engine.pushScene();
    {
        Shipfight shipfight(m_engine);
        shipfight.goGoPowerRangers();
    }
    engine.pushScene();
    {
        Outro outro(engine);
        outro.goGoPowerRangers();
    }
    m_engine.popScene();
}
*/
ramses::DisplayConfig PirateGame::CreateDisplayConfig(int argc, char* argv[], uint32_t width, uint32_t height)
{
    ramses::DisplayConfig displayConfig(argc, argv);
    displayConfig.setWindowRectangle(0, 25, width, height);
    displayConfig.setOrthographicProjection(0, width * 1.0f, 0, height * 1.0f, -100.0f, 100.0f);

    return displayConfig;
}
