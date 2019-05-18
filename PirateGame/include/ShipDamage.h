//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_SHIPDAMAGE_H
#define RAMSES_SHIPDAMAGE_H

#include "ShipFire.h"

using namespace ramses;

namespace ramses_internal
{
    enum EShip
    {
        EShip_LEFT,
        EShip_RIGHT,
        EShip_Undefined
    };

    class ShipDamage;

    class ShipDamage
    {
    public:
        ShipDamage(GameEngine& engine, ramses::Scene& scene);
        ~ShipDamage();

        Bool isBurning() const;
        void addDamage();
        void resetDamage();
        Float getDamage() const;

        Bool moreDamagedThan(const ShipDamage& damage) const;
        ramses::Node& rootNode;

        void putBehind(const MeshNode& mesh);
        void setFadeRange(Vector2 fadeRange);

    protected:
        GameEngine& m_engine;
        Scene& m_scene;

        Float m_damage;

        using ShipFires = std::vector<ShipFire*>;
        ShipFires m_shipFires;

    public:
        Sprite2D damageBar;
    };

    class LeftShipDamage : public ShipDamage
    {
    public:
        LeftShipDamage(GameEngine& engine, ramses::Scene& scene);

    private:
        ShipFire littleFire1;
        ShipFire littleFire2;
        ShipFire mediumFire;
        ShipFire omgOmgOmg;
    };

    class RightShipDamage : public ShipDamage
    {
    public:
        RightShipDamage(GameEngine& engine, ramses::Scene& scene);

    private:
        ShipFire littleFire1;
        ShipFire littleFire2;
        ShipFire mediumFire;
        ShipFire omgOmgOmg;
    };
}

#endif
