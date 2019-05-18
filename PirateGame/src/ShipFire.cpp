//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "ShipFire.h"

namespace ramses_internal
{
    ShipFire::ShipFire(GameEngine& engine, ramses::Scene& scene, const ramses::Texture2D& texture, ramses::Node& rootNode, FireConfig config)
        : AnimatedSprite2D(engine, scene, texture, engine.TexturedQuadEffectWithFade)
        , m_config(config)
    {
        m_rootNode.setParent(rootNode);
        m_scaleNode.scale(config.scale, config.scale, config.scale);
    }

    void ShipFire::updateTime(float time)
    {
        m_rotationNode.setRotation(0, 0, m_config.rotationOffset + m_config.fireBaseRotation + 5 * PlatformMath::Sin(2 * time));

        Vector2 translate = (4 + 3 * PlatformMath::Sin(2 * time + m_config.permutationParams.x)) * Vector2(PlatformMath::Sin(2 * time + m_config.permutationParams.y), PlatformMath::Cos(2 * time + m_config.permutationParams.z)) + m_config.translate;

        m_translateNode.setTranslation(translate.x, translate.y, 0);
    }

    Float ShipFire::getIgniteThreshold() const
    {
        return m_config.igniteThreshold;
    }
}
