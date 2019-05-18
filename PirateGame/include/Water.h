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
    class Water : public Sprite2D
    {
    public:
        Water(GameEngine& engine, ramses::Scene& scene);
    };
}

#endif
