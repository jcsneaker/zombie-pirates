//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_TENTACLES_H
#define RAMSES_TENTACLES_H

#include "Tentacle.h"
#include "ShipDamage.h"

using namespace ramses;

namespace ramses_internal
{
    class Ship;

    enum ETentacleState
    {
        ETentacleState_Underwater,
        ETentacleState_Rising,
        ETentacleState_Up,
        ETentacleState_Sinking,
        ETentacleState_ComingAfter,
        ETentacleState_SinkingShip
    };

    using TentacleVector = std::vector<Tentacle*>;

    class PirateTentacles
    {
    public:
        PirateTentacles(GameEngine& engine, ramses::Scene& scene, ramses::Node& rootNode);

        Tentacle tentacleHead;
        Tentacle leftTentacle;
        Tentacle fatRightTentacle;
        Tentacle slimRightTentacle;

        void putBehind(const MeshNode& mesh, int32_t renderOrerOffset);
    };

    class GoodGuysTentacles
    {
    public:
        GoodGuysTentacles(GameEngine& engine, ramses::Scene& scene, ramses::Node& rootNode);

        Tentacle tentacleHead;
        Tentacle leftTentacle;
        Tentacle fatRightTentacle;
        Tentacle slimRightTentacle;

        void putBehind(const MeshNode& mesh, int32_t renderOrerOffset);
    };

    class TentaclesState
    {
    public:
        TentaclesState(GameEngine& engine, ramses::Scene& scene);
        virtual ~TentaclesState();

        Bool takeHit(const Vector2& cannonPos, Float time);
        ramses::Node& rootNode;

        void update(float time);

        void setShip(const Ship* ship);
        void setTargetShip(const Ship* ship);
        const Ship* getShip() const;
        ETentacleState getState() const;
        Float getSinkTimestamp() const;
        void setState(ETentacleState state, float time);

        void setFadeRange(EShip ship, Vector2 fadeRange);

    protected:
        GameEngine& m_engine;
        Scene& m_scene;
        const Ship* m_ship;
        const Ship* m_targetShip;
        PirateTentacles m_pirateTentacles;
        GoodGuysTentacles m_goodGuysTentacles;
        ETentacleState m_state;
        TentacleVector m_tentacles;
        Float m_tentacleTimer;
        Float m_tentacleAnimationCountdown;
        Int m_tentacleAnimationIndex;
        Bool m_wasHit;

        Bool checkStateTransition(ETentacleState newState) const;
    };

}

#endif
