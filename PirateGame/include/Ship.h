//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_SHIP_H
#define RAMSES_SHIP_H

#include "Sprite2D.h"
#include "Math3d/Vector2.h"
#include "Cannon.h"
#include "ShipDamage.h"
#include "Crew.h"
#include "Wave.h"

using namespace ramses;

namespace ramses_internal
{
    struct SSessionEventData;
    class Cannonball;
    class Explosion;
    class TentaclesState;

    //enum EHitResult
    //{
    //    EHitResult_NothingSpecialJustBurnMotherfucker,
    //    EHitResult_TookAttentionOfTentacles,
    //    EHitResult_HitATentacle,
    //    EHitResult_TentaclesPullBack,
    //    EHitResult_TentaclesAreGoingForYouNowBitch
    //};

    class Ship;

    struct CannonballCollision
    {
        const Ship* damageDealer;
        const Ship* victim;
        Vector2 collisionPoint;
    };

    using Cannonballs = std::vector<const Cannonball*>;
    using CannonballCollisions = std::vector<CannonballCollision>;

    class Ship : public AnimatedSprite2D
    {
    public:
        Ship(GameEngine& engine, ramses::Scene& scene, EShip whoAmI, TentaclesState& tentacleState);
        ~Ship();

        CannonballCollisions getCannonCollisions(Ship& otherShip, Float time);
        void handleInput(float time);
        void handleExplosions(float time);

        EShip getIdentity() const;
        ShipDamage& getDamage();
        const ShipDamage& getDamage() const;

    private:
        EShip m_whoAmI;
        TentaclesState& m_tentacleState;

        enum EDirection
        {
            EDirection_UP,
            EDirection_DOWN,
            EDirection_NONE
        } m_moveStatus, m_facing;

        float m_velocityY;
        float m_lastTimeUpdated;

        Int32 m_canonPoweringUp;
        Float m_cannonPower;

        Cannon m_cannon1;
        Cannon m_cannon2;
        Cannon m_cannon3;

        Cannonballs m_cannonballs;
        TexturedSprite2D m_cannonBang;
        Float m_cannonBangStart;

        std::vector<Explosion*> m_explosions;

        ShipDamage* m_damage;
        Crew* m_crew;

        void fireCannon(Float power);
        virtual void updateTime(float time) override;
        Cannon& getCurrentCannon();
        void takeHit(const Vector2& cannonPos);
    };
}

#endif
