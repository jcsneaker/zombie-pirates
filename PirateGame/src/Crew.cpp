#include "Crew.h"
#include "GameEngine.h"

namespace ramses_internal
{
    Crew::Crew(GameEngine& engine, Scene& scene)
        : rootNode(*scene.createNode())
        , m_engine(engine)
        , m_scene(scene)
    {
    }

    Crew::~Crew()
    {
        m_scene.destroy(rootNode);
    }

    PirateCrew::PirateCrew(GameEngine& engine, ramses::Scene& scene)
        : Crew(engine, scene)
        , johnny    (m_engine, m_scene, rootNode, m_engine.Johnny , CrewMemberConfig{ Vector2(-20,  -30), 5.0f, 4, 82.0f})
        , carol     (m_engine, m_scene, rootNode, m_engine.Carol  , CrewMemberConfig{ Vector2(-20,    0), 2.5f, 3, 82.0f})
        , max       (m_engine, m_scene, rootNode, m_engine.Max    , CrewMemberConfig{ Vector2(-20,   30), 4.0f, 5, 82.0f})
        , philipp   (m_engine, m_scene, rootNode, m_engine.Philipp, CrewMemberConfig{ Vector2(-20,   60), 4.5f, 4, 82.0f})
        , marco     (m_engine, m_scene, rootNode, m_engine.Marco  , CrewMemberConfig{ Vector2(-20,   90), 3.7f, 5, 82.0f})
    {
    }

    void PirateCrew::setFadeRange(Vector2 fadeRange)
    {
        m_engine.setFadeRange(johnny.m_appearance, fadeRange);
        m_engine.setFadeRange(carol.m_appearance, fadeRange);
        m_engine.setFadeRange(max.m_appearance, fadeRange);
        m_engine.setFadeRange(philipp.m_appearance, fadeRange);
        m_engine.setFadeRange(marco.m_appearance, fadeRange);
    }

    GoodGuys::GoodGuys(GameEngine& engine, ramses::Scene& scene)
        : Crew(engine, scene)
        , lamer1 (m_engine, m_scene, rootNode, m_engine.GoodguyProbablyLame, CrewMemberConfig{ Vector2( 10,   -20), 5.0f, 4, -82.0f})
        , lamer2 (m_engine, m_scene, rootNode, m_engine.GoodguyProbablyLame, CrewMemberConfig{ Vector2( 10,    10), 2.5f, 3, -82.0f})
        , lamer3 (m_engine, m_scene, rootNode, m_engine.GoodguyProbablyLame, CrewMemberConfig{ Vector2( 10,    40), 4.0f, 5, -82.0f})
        , lamer4 (m_engine, m_scene, rootNode, m_engine.GoodguyProbablyLame, CrewMemberConfig{ Vector2( 10,    70), 4.5f, 4, -82.0f})
        , lamer5 (m_engine, m_scene, rootNode, m_engine.GoodguyProbablyLame, CrewMemberConfig{ Vector2( 10,   100), 3.7f, 5, -82.0f})
    {
    }

    void GoodGuys::setFadeRange(Vector2 fadeRange)
    {
        m_engine.setFadeRange(lamer1.m_appearance, fadeRange);
        m_engine.setFadeRange(lamer2.m_appearance, fadeRange);
        m_engine.setFadeRange(lamer3.m_appearance, fadeRange);
        m_engine.setFadeRange(lamer4.m_appearance, fadeRange);
        m_engine.setFadeRange(lamer5.m_appearance, fadeRange);
    }

}
