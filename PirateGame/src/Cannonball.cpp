//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "Cannonball.h"
#include "GameEngine.h"
#include "Pos2D.h"

namespace ramses_internal
{
    Cannonball::Cannonball(GameEngine& engine, Scene& scene, Vector2 velocity)
        : AnimatedSprite2D(engine, scene, engine.CannonballTexture, engine.CannonballEffect)
        , m_velocity(velocity)
    {
        Float scale = 0.24f;
        m_scaleNode.scale(scale, scale, scale);

        m_scaleNode.getScaling(size.x, size.y, size.z);
    }

    void Cannonball::updateTime(float time)
    {
        AnimatedSprite2D::updateTime(time);

        float posX, posY;
        getPosition(posX, posY);

        posX += m_velocity.x * MaxCannonSpeed;
        posY += m_velocity.y * MaxCannonSpeed;

        setPosition(posX, posY);
        m_rotationNode.setRotation(0.0f, 0.0f, time * 150);

        Float magicScaling = PlatformMath::Sin(PlatformMath::PI_f * ((posX - ShipOffset) / (Pos2D::s_WindowWidth - 2 * ShipOffset)));
        Vector3 rescaled = size * (1.0f + 0.8f * magicScaling);
        m_scaleNode.setScaling(rescaled.x, rescaled.y, rescaled.z);
    }
}
