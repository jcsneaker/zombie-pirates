#include "Tentacles.h"
#include "Ship.h"
#include "GameEngine.h"

#define FOREACH_TENTACLE(statement)             \
for(TentacleVector::iterator tIter = m_tentacles.begin(); tIter != m_tentacles.end(); ++tIter)\
{                                               \
    Tentacle& tentacle = **tIter;               \
    statement;                                  \
}                                               \

namespace ramses_internal
{
    TentaclesState::TentaclesState(GameEngine& engine, Scene& scene)
        : rootNode(*scene.createNode())
        , m_engine(engine)
        , m_scene(scene)
        , m_ship(0)
        , m_targetShip(0)
        , m_pirateTentacles(engine, scene, rootNode)
        , m_goodGuysTentacles(engine, scene, rootNode)
        , m_state(ETentacleState_Underwater)
        , m_tentacleAnimationCountdown(0)
        , m_tentacleAnimationIndex(0)
        , m_wasHit(false)
    {
    }

    TentaclesState::~TentaclesState()
    {
        m_scene.destroy(rootNode);
    }

    void TentaclesState::update(float time)
    {
        switch (m_state)
        {
        case ETentacleState_Rising:
        {
            Float riseTime = time - m_tentacleTimer;
            if (riseTime < TentacleRiseTime)
            {
                FOREACH_TENTACLE(tentacle.setVerticalDisplacement(-1 + riseTime / TentacleRiseTime));
            }
            else
            {
                setState(ETentacleState_Up, time);
            }

            break;
        }
        case ETentacleState_Up:
        {
            Float upTime = time - m_tentacleTimer;
            if (upTime >= TentacleTimeUntilSinkAgain)
            {
                setState(ETentacleState_Sinking, time);
            }
            break;
        }
        case ETentacleState_SinkingShip:
            break;
        case ETentacleState_Sinking:
        {
            Float riseTime = time - m_tentacleTimer;
            if (riseTime < TentacleRiseTime)
            {
                FOREACH_TENTACLE(tentacle.setVerticalDisplacement(-riseTime / TentacleRiseTime));
            }
            else
            {
                setShip(0);
                setState(ETentacleState_Underwater, time);
                if (0 != m_targetShip)
                {
                    setState(ETentacleState_ComingAfter, time);
                }
            }

            break;
        }
        case ETentacleState_ComingAfter:
        {
            Float riseTime = time - m_tentacleTimer;
            if (riseTime >= TentacleTimeToArrive)
            {
                setShip(m_targetShip);
                m_targetShip = 0;
                setState(ETentacleState_Rising, time);
            }

            break;
        }
        default:
            break;
        }
    }

    void TentaclesState::setShip(const Ship* ship)
    {
        FOREACH_TENTACLE(tentacle.setVisibility(false));
        m_tentacles.clear();
        m_ship = ship;


        if (0 != ship)
        {
            rootNode.setParent(ship->m_rotationNode);
            m_pirateTentacles.putBehind(ship->m_meshNode, 5);
            m_goodGuysTentacles.putBehind(ship->m_meshNode, 5);

            if (ship->getIdentity() == EShip_LEFT)
            {
                m_tentacles.push_back(&m_goodGuysTentacles.tentacleHead);
                m_tentacles.push_back(&m_goodGuysTentacles.leftTentacle);
                m_tentacles.push_back(&m_goodGuysTentacles.fatRightTentacle);
                m_tentacles.push_back(&m_goodGuysTentacles.slimRightTentacle);
            }
            else if (ship->getIdentity() == EShip_RIGHT)
            {
                m_tentacles.push_back(&m_pirateTentacles.tentacleHead);
                m_tentacles.push_back(&m_pirateTentacles.leftTentacle);
                m_tentacles.push_back(&m_pirateTentacles.fatRightTentacle);
                m_tentacles.push_back(&m_pirateTentacles.slimRightTentacle);
            }
            FOREACH_TENTACLE(tentacle.setVisibility(true));
        }
        else
        {
            rootNode.removeParent();
        }
    }

    void TentaclesState::setTargetShip(const Ship* ship)
    {
        m_targetShip = ship;
    }

    const Ship* TentaclesState::getShip() const
    {
        return m_ship;
    }

    ETentacleState TentaclesState::getState() const
    {
        return m_state;
    }

    Float TentaclesState::getSinkTimestamp() const
    {
        return m_tentacleTimer;
    }

    void TentaclesState::setState(ETentacleState state, float time)
    {
        checkStateTransition(state);

        switch (state)
        {
        case ETentacleState_Underwater:
            FOREACH_TENTACLE(tentacle.setVerticalDisplacement(-1));
            FOREACH_TENTACLE(tentacle.setVisibility(false));
            m_wasHit = false;
            break;
        case ETentacleState_Up:
            FOREACH_TENTACLE(tentacle.setVerticalDisplacement(0));
            m_tentacleTimer = time;
            break;
        case ETentacleState_Rising:
            FOREACH_TENTACLE(tentacle.setVisibility(true));
            FOREACH_TENTACLE(tentacle.setVerticalDisplacement(-1));
            m_tentacleTimer = time;
            break;
        case ETentacleState_Sinking:
            m_tentacleTimer = time;
            m_wasHit = false;
            break;
        case ETentacleState_SinkingShip:
            FOREACH_TENTACLE(tentacle.setJiggleDistance(Vector2(1.0f)));
            m_tentacleTimer = time;
            break;
        case ETentacleState_ComingAfter:
            m_tentacleTimer = time;
            break;
        default:
            break;
        }

        m_state = state;
    }

    void TentaclesState::setFadeRange(EShip ship, Vector2 fadeRange)
    {
        if (ship == EShip_LEFT)
        {
            m_engine.setFadeRange(m_goodGuysTentacles.tentacleHead     .m_appearance, fadeRange);
            m_engine.setFadeRange(m_goodGuysTentacles.leftTentacle     .m_appearance, fadeRange);
            m_engine.setFadeRange(m_goodGuysTentacles.fatRightTentacle .m_appearance, fadeRange);
            m_engine.setFadeRange(m_goodGuysTentacles.slimRightTentacle.m_appearance, fadeRange);
        }
        else if (ship == EShip_RIGHT)
        {
            m_engine.setFadeRange(m_pirateTentacles.tentacleHead     .m_appearance, fadeRange);
            m_engine.setFadeRange(m_pirateTentacles.leftTentacle     .m_appearance, fadeRange);
            m_engine.setFadeRange(m_pirateTentacles.fatRightTentacle .m_appearance, fadeRange);
            m_engine.setFadeRange(m_pirateTentacles.slimRightTentacle.m_appearance, fadeRange);
        }
    }

    Bool TentaclesState::checkStateTransition(ETentacleState newState) const
    {
        Bool valid = true;
        switch (newState)
        {
        case ETentacleState_Underwater:
            valid &= m_state == ETentacleState_SinkingShip || m_state == ETentacleState_Sinking;
            valid &= 0 == m_ship;
            break;
        case ETentacleState_Up:
            valid &= m_state == ETentacleState_Rising;
            break;
        case ETentacleState_Rising:
            valid &= (m_state == ETentacleState_Underwater || m_state == ETentacleState_ComingAfter);
            break;
        case ETentacleState_Sinking:
            valid &= (m_state == ETentacleState_Up || m_state == ETentacleState_Rising);
            break;
        case ETentacleState_SinkingShip:
            valid &= (m_state == ETentacleState_Up);
            break;
        case ETentacleState_ComingAfter:
            valid &= (m_state == ETentacleState_Underwater);
            valid &= 0 != m_targetShip;
            valid &= 0 == m_ship;
            break;
        default:
            break;
        }

        if (!valid)
        {
            assert(false);
        }
        return valid;
    }

    Bool TentaclesState::takeHit(const Vector2& cannonPos, Float time)
    {
        Float distanceToClosestTentackle = 50000.0f;
        Int32 closestTentacle = -1;

        for (UInt32 i = 0; i < m_tentacles.size(); ++i)
        {
            Vector2 tentaclePos = m_tentacles[i]->getAbsolute2DPosition();
            if ((cannonPos - tentaclePos).length() < distanceToClosestTentackle)
            {
                distanceToClosestTentackle = (cannonPos - tentaclePos).length();
                closestTentacle = i;
            }
        }

        m_tentacles[closestTentacle]->takeHit(time);

        if (m_wasHit)
        {
            return true;
        }
        else
        {
            m_wasHit = true;
            return false;
        }
    }

    void GoodGuysTentacles::putBehind(const MeshNode& mesh, int32_t renderOrerOffset)
    {
        int32_t renderOrer;
        tentacleHead.m_engine.getCurrentRenderGroup().getMeshNodeOrder(mesh, renderOrer);
        renderOrer -= renderOrerOffset;
        tentacleHead.m_engine.setMeshRenderOrder(tentacleHead.m_meshNode, renderOrer - 1);
        leftTentacle.m_engine.setMeshRenderOrder(leftTentacle.m_meshNode, renderOrer - 2);
        fatRightTentacle.m_engine.setMeshRenderOrder(fatRightTentacle.m_meshNode, renderOrer - 3);
        slimRightTentacle.m_engine.setMeshRenderOrder(slimRightTentacle.m_meshNode, renderOrer - 4);
    }

    void PirateTentacles::putBehind(const MeshNode& mesh, int32_t renderOrerOffset)
    {
        int32_t renderOrer;
        tentacleHead.m_engine.getCurrentRenderGroup().getMeshNodeOrder(mesh, renderOrer);
        renderOrer -= renderOrerOffset;
        tentacleHead.m_engine.setMeshRenderOrder(tentacleHead.m_meshNode, renderOrer - 1);
        leftTentacle.m_engine.setMeshRenderOrder(leftTentacle.m_meshNode, renderOrer - 2);
        slimRightTentacle.m_engine.setMeshRenderOrder(slimRightTentacle.m_meshNode, renderOrer - 3);
        fatRightTentacle.m_engine.setMeshRenderOrder(fatRightTentacle.m_meshNode, renderOrer - 4);
    }

    PirateTentacles::PirateTentacles(GameEngine& engine, ramses::Scene& scene, ramses::Node& rootNode)
        : tentacleHead      (engine, scene, rootNode, engine.HeadTentacle       , TentacleConfig{ Vector2( 50,   0) , 2.5f, Vector2(4.0f, 0.0f), 90.0f, true, Vector2(-50.0f, 0.0f)  , 200.0f})
        , leftTentacle      (engine, scene, rootNode, engine.LeftTentacle       , TentacleConfig{ Vector2( 60,-120) , 1.7f, Vector2(3.0f, 3.0f), 90.0f, true, Vector2(-50.0f, 50.0f) , 200.0f})
        , fatRightTentacle  (engine, scene, rootNode, engine.RightFatTentacle   , TentacleConfig{ Vector2( 20, -60) , 2.0f, Vector2(5.0f, 5.0f), 90.0f, true, Vector2(-50.0f, 10.0f) , 200.0f})
        , slimRightTentacle (engine, scene, rootNode, engine.RightSlimTentacle  , TentacleConfig{ Vector2( 20, 140) , 2.3f, Vector2(4.0f, 4.0f), 50.0f, true, Vector2(-50.0f,-50.0f) , 200.0f})
    {
        tentacleHead     .setVisibility(false);
        leftTentacle     .setVisibility(false);
        fatRightTentacle .setVisibility(false);
        slimRightTentacle.setVisibility(false);
    }

    GoodGuysTentacles::GoodGuysTentacles(GameEngine& engine, ramses::Scene& scene, ramses::Node& rootNode)
        : tentacleHead      (engine, scene, rootNode, engine.HeadTentacle       , TentacleConfig{ Vector2(-30,   0), 2.5f, Vector2(4.0f, 0.0f), -90.0f , false, Vector2( 50.0f,   0.0f), -200.0f})
        , leftTentacle      (engine, scene, rootNode, engine.LeftTentacle       , TentacleConfig{ Vector2(-10,-140), 1.7f, Vector2(3.0f, 3.0f), -90.0f , false, Vector2( 50.0f,  50.0f), -200.0f})
        , fatRightTentacle  (engine, scene, rootNode, engine.RightFatTentacle   , TentacleConfig{ Vector2(-40, -60), 2.0f, Vector2(5.0f, 5.0f), -90.0f , false, Vector2( 50.0f,  10.0f), -200.0f})
        , slimRightTentacle (engine, scene, rootNode, engine.RightSlimTentacle  , TentacleConfig{ Vector2(-10, 140), 2.3f, Vector2(4.0f, 4.0f), -50.0f , false, Vector2( 50.0f, -50.0f), -200.0f})
    {
        tentacleHead     .setVisibility(false);
        leftTentacle     .setVisibility(false);
        fatRightTentacle .setVisibility(false);
        slimRightTentacle.setVisibility(false);
    }
}
