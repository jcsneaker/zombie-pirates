#include "Tentacle.h"


namespace ramses_internal
{
    Tentacle::Tentacle(GameEngine& engine, Scene& scene, ramses::Node& rootNode, const ramses::Texture2D& texture, TentacleConfig config)
        : AnimatedSprite2D(engine, scene, texture, engine.TentacleEffect)
        , m_config(config)
        , m_verticalDisplacement(0.0f)
        , m_hitTime(-1.0f)
    {
        m_rootNode.setParent(rootNode);

        m_rotationNode.setRotation(0, 0, m_config.rotation);

        const float scale = 0.5f;
        m_scaleNode.scale(scale, scale, scale);

        if (m_config.flipped)
        {
            m_scaleNode.scale(-1, 1, 1);
        }
    }

    void Tentacle::setJiggleDistance(Vector2 dist)
    {
        m_config.jiggleDistance = dist;
    }

    void Tentacle::setVerticalDisplacement(float disp)
    {
        m_verticalDisplacement = disp;
    }

    void Tentacle::updateTime(float time)
    {
        Float modifiedTime = time * m_config.jiggleSpeed;

        Vector2 baseOffset = m_config.offsetToShip;
        Vector2 jiggleTranslation = m_config.jiggleDistance * Vector2(pow(sin(modifiedTime), 4), -pow(0.5f*sin(modifiedTime), 4));
        jiggleTranslation += Vector2(sin(modifiedTime), cos(modifiedTime)) * 2 * m_config.jiggleDistance;

        {
            // staircase vertical offset
            Float modifiedDisp = stairs(m_verticalDisplacement);
            Float riseOffset = modifiedDisp * m_config.riseOffset;
            baseOffset += Vector2(riseOffset, 0.0f);
        }

        Float wiggleProgress = 0.0f;
        if (time - m_hitTime <= TentacleWiggleTime)
        {
            wiggleProgress = ((time - m_hitTime) / TentacleWiggleTime);
        }

        Float power = 1.0f / (5.0f - wiggleProgress * PlatformMath::PI_f);
        Vector2 wiggleOffset = PlatformMath::Pow(PlatformMath::Sin(wiggleProgress * PlatformMath::PI_f), power) * m_config.wiggleDirection;

        Vector2 finalTtranslate = baseOffset + jiggleTranslation + wiggleOffset;
        m_translateNode.setTranslation(finalTtranslate.x, finalTtranslate.y, 0);
    }

    Float Tentacle::stairs(Float x) const
    {
        const Float pi2 = 2 * PlatformMath::PI_f;
        const Float pi2x = x * pi2;
        return (pi2x + 0.2f * (1 + (sin(2 * pi2x)))) / (pi2 + 0.2f);
    }

    void Tentacle::takeHit(Float time)
    {
        if (m_hitTime <= 0.0f || time - m_hitTime > TentacleWiggleTime)
        {
            m_hitTime = time;
        }
    }

}
