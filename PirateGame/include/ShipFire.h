//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_SHIPFIRE_H
#define RAMSES_SHIPFIRE_H

#include "Sprite2D.h"
#include "Math3d/Vector3.h"

namespace ramses_internal
{
    struct FireConfig
    {
        Float scale;
        Float fireBaseRotation;
        Float rotationOffset;
        Vector2 translate;
        Vector3 permutationParams;
        Float igniteThreshold;
    };

    class ShipFire : public AnimatedSprite2D
    {
    public:
        ShipFire(GameEngine& engine, ramses::Scene& scene, const ramses::Texture2D& texture, ramses::Node& rootNode, FireConfig config);

        virtual void updateTime(float time) override;
        Float getIgniteThreshold() const;
    private:
        FireConfig m_config;
    };
}

#endif
