#include "Outro.h"
#include <ramses-client.h>
#include "PlatformAbstraction/PlatformTime.h"
#include "RendererLib/WindowedRenderer.h"
#include "CrewMember.h"
#include "Crew.h"

namespace ramses_internal
{
    Outro::Outro(GameEngine& engine)
        : m_engine(engine)
        , m_water(engine, engine.getCurrentScene(), engine.OutroWaterEffect)
    {
        m_water.setPosition(Pos2D::s_WindowWidth / 2.0f, Pos2D::s_WindowHeight / 2.0f);
        m_water.setSize(static_cast<Float>(Pos2D::s_WindowWidth), static_cast<Float>(Pos2D::s_WindowHeight));
        m_water.setBlending(false);
        m_water.m_appearance.setDepthFunction(ramses::EDepthFunc_Always);
    }

    void Outro::goGoPowerRangers()
    {
        m_engine.fadeIn(1000);

        const UInt64 startTime = PlatformTime::GetMillisecondsAbsolute();
        float time = 0.0f;

        ramses::Scene& scene = m_engine.getCurrentScene();
        Node& rootNode = *scene.createNode();

        rootNode.setTranslation(Pos2D::s_WindowWidth / 2, Pos2D::s_WindowHeight - 50, 0);

        CrewMember johnny   (m_engine, scene, rootNode, m_engine.Johnny , CrewMemberConfig{ Vector2(- 100,  -30), 1.0f, 4, 3.0f});
        CrewMember carol    (m_engine, scene, rootNode, m_engine.Carol  , CrewMemberConfig{ Vector2(- 200,    0), 0.5f, 3, -5.0f});
        CrewMember max      (m_engine, scene, rootNode, m_engine.Max    , CrewMemberConfig{ Vector2(- 000,   30), 1.0f, 5, 2.0f});
        CrewMember philipp  (m_engine, scene, rootNode, m_engine.Philipp, CrewMemberConfig{ Vector2(+ 200,   60), 0.5f, 4, -9.0f});
        CrewMember marco    (m_engine, scene, rootNode, m_engine.Marco  , CrewMemberConfig{ Vector2(+ 100,   90), 0.7f, 5, 0.0f});

        m_engine.setFadeRange(johnny .m_appearance, Vector2(5000, 6000));
        m_engine.setFadeRange(carol  .m_appearance, Vector2(5000, 6000));
        m_engine.setFadeRange(max    .m_appearance, Vector2(5000, 6000));
        m_engine.setFadeRange(philipp.m_appearance, Vector2(5000, 6000));
        m_engine.setFadeRange(marco  .m_appearance, Vector2(5000, 6000));

        while ((PlatformTime::GetMillisecondsAbsolute() - startTime) < 20000)
        {
            time = (PlatformTime::GetMillisecondsAbsolute() - startTime) / 1000.0f;

            johnny .m_config.offsetToShip += Vector2(0.0f, -1.3f);
            carol  .m_config.offsetToShip += Vector2(0.0f, -1.2f);
            max    .m_config.offsetToShip += Vector2(0.0f, -1.6f);
            philipp.m_config.offsetToShip += Vector2(0.0f, -1.44f);
            marco  .m_config.offsetToShip += Vector2(0.0f, -1.5f);

            m_engine.updateSprites(time);
            m_engine.doOneRendererLoop();
        }

        m_engine.fadeOut(4000);
    }
}
