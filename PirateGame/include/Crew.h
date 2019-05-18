//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_CREW_H
#define RAMSES_CREW_H

#include "Sprite2D.h"
#include "Math3d/Vector2.h"
#include "CrewMember.h"

using namespace ramses;

namespace ramses_internal
{
    class Crew
    {
    public:
        Crew(GameEngine& engine, ramses::Scene& scene);
        virtual ~Crew();

        ramses::Node& rootNode;

        virtual void setFadeRange(Vector2 fadeRange) = 0;

    protected:
        GameEngine& m_engine;
        Scene& m_scene;
    };

    class PirateCrew : public Crew
    {
    public:
        PirateCrew(GameEngine& engine, ramses::Scene& scene);

        CrewMember johnny;
        CrewMember carol;
        CrewMember max;
        CrewMember philipp;
        CrewMember marco;

        virtual void setFadeRange(Vector2 fadeRange);
    };

    // They are truly lame
    class GoodGuys : public Crew
    {
    public:
        GoodGuys(GameEngine& engine, ramses::Scene& scene);

        CrewMember lamer1;
        CrewMember lamer2;
        CrewMember lamer3;
        CrewMember lamer4;
        CrewMember lamer5;

        virtual void setFadeRange(Vector2 fadeRange);
    };
}

#endif
