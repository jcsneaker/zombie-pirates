//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_WATER_H
#define RAMSES_WATER_H

#include "Sprite2D.h"

using namespace ramses;
using namespace ramses_internal;

namespace ramses_internal
{

    struct WaveConfig
    {
        Vector2 offset;
        Vector2 size;
        Float jiggleSpeed;
        Float jiggleDistance;
        Float timeOffset;
    };


    class Wave : public AnimatedSprite2D
    {
    public:
        Wave(GameEngine& engine, ramses::Scene& scene, WaveConfig config);

        virtual void updateTime(float time) override;

    private:
        WaveConfig m_config;
        ramses::Node& m_additionalTranslate;
    };

    class Water
    {
    public:
        Water(GameEngine& engine, ramses::Scene& scene);
        ~Water();

    private:
        GameEngine& m_engine;
        ramses::Scene& m_scene;

        std::vector<Wave*> m_waves;
    };
}

#endif
