﻿#include "Shipfight.h"
#include <assert.h>
#include "Utils/LogMacros.h"
#include "Math3d/Vector4.h"
#include "ramses-utils.h"
#include "GameEngine.h"
#include "PlatformAbstraction/PlatformTime.h"

namespace ramses_internal
{
    Shipfight::Shipfight(GameEngine& engine)
        : m_engine(engine)
        , m_scene(engine.getCurrentScene())
        , m_water(engine, m_scene)
        , m_tentaclesState(engine, m_scene)
        , m_ship1(engine, m_scene, EShip_LEFT, m_tentaclesState)
        , m_ship2(engine, m_scene, EShip_RIGHT, m_tentaclesState)
        , m_startTime(PlatformTime::GetMillisecondsAbsolute())
    {
    }

    Shipfight::~Shipfight()
    {
    }

    bool Shipfight::fightIsOver() const
    {
        return m_oneShipSank;
    }

    void Shipfight::step()
    {
        const float time = (PlatformTime::GetMillisecondsAbsolute() - m_startTime) / 1000.0f;

        m_ship1.handleExplosions(time);
        m_ship2.handleExplosions(time);

        m_ship1.handleInput(time);
        m_ship2.handleInput(time);

        if (ETentacleState_SinkingShip == m_tentaclesState.getState())
        {
            if (m_savedShipTranslation.x == -1000.0f)
            {
                m_tentaclesState.getShip()->m_translateNode.getTranslation(m_savedShipTranslation.x, m_savedShipTranslation.y, m_savedShipTranslation.z);
            }

            Float timeDiff = time - m_tentaclesState.getSinkTimestamp();
            if (timeDiff > 8.0f)
            {
                m_oneShipSank = true;
            }
            else
            {
                Float sinkOffset = 60.0f;

                if (m_tentaclesState.getShip()->getIdentity() == EShip_RIGHT)
                {
                    sinkOffset = -sinkOffset;
                }

                m_tentaclesState.getShip()->m_translateNode.setTranslation(m_savedShipTranslation.x + sinkOffset * timeDiff, m_savedShipTranslation.y, m_savedShipTranslation.z);
            }
        }
        else
        {
            processCollisions(m_ship1.getCannonCollisions(m_ship2, time), time);
            processCollisions(m_ship2.getCannonCollisions(m_ship1, time), time);
        }

        m_engine.updateSprites(time);
        m_tentaclesState.update(time);

        m_engine.doOneRendererLoop();

        //m_engine.fadeOut(4000);

        //m_tentaclesState.getShip()->m_translateNode.setTranslation(m_savedShipTranslation.x, m_savedShipTranslation.y, m_savedShipTranslation.z);
        //m_tentaclesState.setShip(0);
        //m_tentaclesState.setState(ETentacleState_Underwater, time);
        //m_ship1.getDamage().resetDamage();
        //m_ship2.getDamage().resetDamage();
    }

    void Shipfight::processCollisions(const CannonballCollisions& collisions, Float time)
    {
        for(const auto collision: collisions)
        {
            ETentacleState tentacleState = m_tentaclesState.getState();

            if (m_tentaclesState.getShip() == 0 && m_tentaclesState.getState() != ETentacleState_ComingAfter && collision.victim->getDamage().isBurning())
            {
                m_tentaclesState.setShip(collision.victim);
                m_tentaclesState.setState(ETentacleState_Rising, time);
            }
            else if (m_tentaclesState.getShip() == collision.damageDealer && collision.victim->getDamage().moreDamagedThan(collision.damageDealer->getDamage()))
            {
                if (ETentacleState_Sinking != m_tentaclesState.getState())
                {
                    m_tentaclesState.setTargetShip(collision.victim);
                    m_tentaclesState.setState(ETentacleState_Sinking, time);
                }
            }
            else if (m_tentaclesState.getShip() == collision.victim && ETentacleState_Up == tentacleState)
            {
                Bool secondHit = m_tentaclesState.takeHit(collision.collisionPoint, time);
                if (secondHit)
                {
                    m_tentaclesState.setState(ETentacleState_SinkingShip, time);
                }
            }
        }
    }

}
