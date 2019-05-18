//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_SHIPFIGHT_H
#define RAMSES_SHIPFIGHT_H

#include <ramses-client.h>
#include "RendererLib/WindowedRenderer.h"
#include "Wave.h"
#include "Ship.h"
#include "Tentacles.h"
#include "Water.h"

using namespace ramses;
using namespace ramses_internal;

namespace ramses_internal
{
    class Shipfight
    {
    public:
        Shipfight(GameEngine& engine);
        ~Shipfight();
        void goGoPowerRangers();
    private:

        void processCollisions(const CannonballCollisions& collisions, Float time);
        
        GameEngine& m_engine;

        ramses::Scene& m_scene;

        Water m_water;
        TentaclesState m_tentaclesState;
        Ship m_ship1;
        Ship m_ship2;
    };
}

#endif
