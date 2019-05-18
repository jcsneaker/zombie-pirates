#include "CrewMember.h"
#include "GameEngine.h"


namespace ramses_internal
{
    CrewMember::CrewMember(GameEngine& engine, Scene& scene, ramses::Node& rootNode, const ramses::Texture2D& texture, CrewMemberConfig config)
        : AnimatedSprite2D(engine, scene, texture, engine.TexturedQuadEffectWithFade)
        , m_config(config)
    {
        m_rootNode.setParent(rootNode);

        float scale = 0.2f;
        m_scaleNode.scale(scale, scale, scale);

        m_rotationNode.setRotation(0, 0, config.rotation);
    }

    void CrewMember::updateTime(float time)
    {
        time *= 2;

        Float modifiedTime = time * m_config.jiggleSpeed;

        Vector2 translate = m_config.offsetToShip;
        translate += m_config.jiggleDistance * Vector2(pow(sin(modifiedTime), 4), -pow(0.5f*sin(modifiedTime), 4));
        m_translateNode.setTranslation(translate.x, translate.y, 0);
    }

}
