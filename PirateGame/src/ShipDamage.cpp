//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "ShipDamage.h"
#include "GameEngine.h"

#define FOREACH_FIRE(statement)                 \
for(ShipFires::iterator fIter = m_shipFires.begin(); fIter != m_shipFires.end(); ++fIter)     \
{                                               \
    ShipFire& fire = **fIter;                   \
    statement;                                  \
}                                               \

namespace ramses_internal
{
    ShipDamage::ShipDamage(GameEngine& engine, Scene& scene)
        : rootNode(*scene.createNode())
        , m_engine(engine)
        , m_scene(scene)
        , m_damage(0.0f)
        , damageBar     (m_engine, m_scene, m_engine.FadeOutEffect)
    {
        damageBar.setSize(100.0f, 20.0f);
        damageBar.m_translateNode.setTranslation(0.0f, -220.0f, 0.0f);
        // disabled atm
        damageBar.setVisibility(false);
    }

    ShipDamage::~ShipDamage()
    {
        m_scene.destroy(rootNode);
    }

    void ShipDamage::putBehind(const MeshNode& mesh)
    {
        int32_t renderOrer;
        m_engine.getCurrentRenderGroup().getMeshNodeOrder(mesh, renderOrer);
        FOREACH_FIRE(m_engine.setMeshRenderOrder(fire.m_meshNode, --renderOrer));
    }

    void ShipDamage::setFadeRange(Vector2 fadeRange)
    {
        FOREACH_FIRE(m_engine.setFadeRange(fire.m_appearance, fadeRange));
    }

    Bool ShipDamage::isBurning() const
    {
        return m_damage >= 1.0f;
    }

    void ShipDamage::addDamage()
    {
        m_damage += DamagePerHit;

        FOREACH_FIRE(fire.setVisibility(m_damage > fire.getIgniteThreshold() ? true : false));
    }

    void ShipDamage::resetDamage()
    {
        m_damage = 0.0f;
        FOREACH_FIRE(fire.setVisibility(false));
    }

    Float ShipDamage::getDamage() const
    {
        return m_damage;
    }

    Bool ShipDamage::moreDamagedThan(const ShipDamage& damage) const
    {
        return m_damage > damage.m_damage;
    }

    LeftShipDamage::LeftShipDamage(GameEngine& engine, ramses::Scene& scene)
        : ShipDamage(engine, scene)
        , littleFire1   (engine, scene, engine.LittleFire1, ShipDamage::rootNode, FireConfig {0.4f, 0.0f,  0.0f, Vector2(-30, -120), Vector3(1.0f, 3.0f, 3.0f), 0.1f})
        , littleFire2   (engine, scene, engine.LittleFire2, ShipDamage::rootNode, FireConfig {0.4f, 0.0f,  0.0f, Vector2(  5,  110), Vector3(4.0f, 5.0f, 5.0f), 0.2f})
        , mediumFire    (engine, scene, engine.MediumFire , ShipDamage::rootNode, FireConfig {0.3f, 0.0f, -5.0f, Vector2(-88,   40), Vector3(2.0f, 1.0f, 1.0f), 0.5f})
        , omgOmgOmg     (engine, scene, engine.OmgOmgOmg  , ShipDamage::rootNode, FireConfig {0.6f, 0.0f,  0.0f, Vector2( 10,    0), Vector3(5.0f, 2.0f, 2.0f), 0.8f})
    {
        m_shipFires.push_back(&littleFire1);
        m_shipFires.push_back(&littleFire2);
        m_shipFires.push_back(&mediumFire);
        m_shipFires.push_back(&omgOmgOmg);
        resetDamage();
    }

    RightShipDamage::RightShipDamage(GameEngine& engine, ramses::Scene& scene)
        : ShipDamage(engine, scene)
        , littleFire1   (engine, scene, engine.LittleFire1, ShipDamage::rootNode, FireConfig {0.4f, 180.0f,  0.0f, Vector2(115,  -40), Vector3(1.0f, 3.0f, 3.0f), 0.1f})
        , littleFire2   (engine, scene, engine.LittleFire2, ShipDamage::rootNode, FireConfig {0.4f, 180.0f,  0.0f, Vector2(-22,  110), Vector3(4.0f, 5.0f, 5.0f), 0.2f})
        , mediumFire    (engine, scene, engine.MediumFire , ShipDamage::rootNode, FireConfig {0.3f, 180.0f, -5.0f, Vector2( 29, -127), Vector3(2.0f, 1.0f, 1.0f), 0.5f})
        , omgOmgOmg     (engine, scene, engine.OmgOmgOmg  , ShipDamage::rootNode, FireConfig {0.6f, 180.0f,  0.0f, Vector2(-10,    0), Vector3(5.0f, 2.0f, 2.0f), 0.8f})
    {
        m_shipFires.push_back(&littleFire1);
        m_shipFires.push_back(&littleFire2);
        m_shipFires.push_back(&mediumFire);
        m_shipFires.push_back(&omgOmgOmg);
        resetDamage();
    }


}
