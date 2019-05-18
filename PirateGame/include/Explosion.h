//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_EXPLOSION_H
#define RAMSES_EXPLOSION_H

#include "Sprite2D.h"
#include "Math3d/Vector2.h"
#include "Math3d/Vector3.h"

using namespace ramses;

namespace ramses_internal
{
    class Explosion : public AnimatedSprite2D
    {
    public:
        Explosion(GameEngine& engine, ramses::Scene& scene, Float size);

        Bool expired() const;

    private:

        virtual void updateTime(float time) override;
        Float m_timeRemaining;
    };
}

#endif
