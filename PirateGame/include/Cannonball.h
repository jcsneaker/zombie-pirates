//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_CANNONBALL_H
#define RAMSES_CANNONBALL_H

#include "Sprite2D.h"
#include "Math3d/Vector2.h"
#include "Math3d/Vector3.h"

using namespace ramses;

namespace ramses_internal
{
    class Cannonball : public AnimatedSprite2D
    {
    public:
        Cannonball(GameEngine& engine, ramses::Scene& scene, Vector2 velocity);

        Vector3 size;

    private:
        Vector2 m_velocity;

        virtual void updateTime(float time) override;
    };
}

#endif
