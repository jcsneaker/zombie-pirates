//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_CREWMEMBER_H
#define RAMSES_CREWMEMBER_H

#include "Sprite2D.h"
#include "Math3d/Vector2.h"

using namespace ramses;

namespace ramses_internal
{
    enum EPerson
    {
        EPerson_Johnny = 0,
        EPerson_Carol = 1,
        EPerson_Max = 2,
        EPerson_Philipp = 3,
        EPerson_Marco = 4,
        EPerson_Count = 6
    };

    struct CrewMemberConfig
    {
        Vector2 offsetToShip;
        Float jiggleSpeed;
        Float jiggleDistance;
        Float rotation;
    };

    class CrewMember : public AnimatedSprite2D
    {
    public:
        CrewMember(GameEngine& engine, ramses::Scene& scene, ramses::Node& rootNode, const ramses::Texture2D& texture, CrewMemberConfig config);

        virtual void updateTime(float time) override;

        CrewMemberConfig m_config;
    };
}

#endif
