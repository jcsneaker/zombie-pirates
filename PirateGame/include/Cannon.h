//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_CANNON_H
#define RAMSES_CANNON_H

#include "Sprite2D.h"
#include "Math3d/Vector2.h"

using namespace ramses;

namespace ramses_internal
{
    class Cannon : public TexturedSprite2D
    {
    public:
        Cannon(GameEngine& engine, Scene& scene, bool rotate, Vector2 offset, Node& parent);

        void setShootProgress(float progress);

    private:
        UniformInput m_cannonShootProgress;
        Float m_offsetY;
    };
}

#endif
