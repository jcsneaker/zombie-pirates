//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_OUTRO_H
#define RAMSES_OUTRO_H

#include "Sprite2D.h"

namespace ramses_internal
{
    class GameEngine;

    class Outro
    {
    public:
        Outro(GameEngine& engine);
        void goGoPowerRangers();
    private:

        GameEngine& m_engine;
        Sprite2D m_water;
    };
}

#endif
