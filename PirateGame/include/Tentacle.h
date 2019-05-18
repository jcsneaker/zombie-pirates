//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_TENTACLE_H
#define RAMSES_TENTACLE_H

#include "Sprite2D.h"
#include "Math3d/Vector2.h"

using namespace ramses;

namespace ramses_internal
{
    struct TentacleConfig
    {
        Vector2 offsetToShip;
        Float jiggleSpeed;
        Vector2 jiggleDistance;
        Float rotation;
        Bool flipped;
        Vector2 wiggleDirection;
        Float riseOffset;
    };

    class Tentacle : public AnimatedSprite2D
    {
    public:
        Tentacle(GameEngine& engine, ramses::Scene& scene, ramses::Node& rootNode, const ramses::Texture2D& texture, TentacleConfig config);

        void takeHit(Float time);
        void setJiggleDistance(Vector2 dist);
        void setVerticalDisplacement(float disp);
        virtual void updateTime(float time) override;

    private:
        TentacleConfig m_config;
        float m_verticalDisplacement;
        float m_hitTime;

        Float stairs(Float x) const;
    };
}

#endif
