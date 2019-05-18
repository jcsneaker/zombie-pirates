//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_INTROTEXT_H
#define RAMSES_INTROTEXT_H

#include <ramses-client.h>
#include "RendererLib/WindowedRenderer.h"
#include "Wave.h"
#include "Ship.h"
#include "Tentacles.h"

using namespace ramses;
using namespace ramses_internal;

namespace ramses_internal
{
    class IntroText
    {
    public:
        IntroText(GameEngine& engine);
        void goGoPowerRangers();
    private:
        GameEngine& m_engine;
        
        void getAnswer(TextCreator& textCreator, Pos2D position, String answer, String answerContext);
    };
}

#endif
