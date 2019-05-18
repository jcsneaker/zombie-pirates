#include "Water.h"
#include "Pos2D.h"
#include "GameEngine.h"

namespace ramses_internal
{
    Water::Water(GameEngine& engine, ramses::Scene& scene)
        : m_engine(engine)
        , m_scene(scene)
    {
        const float w = Pos2D::s_WindowWidth;
        const float h = Pos2D::s_WindowHeight;

        int waveCount = 6;
        float waveVerticalSlice = 1.0f / (waveCount-1);

        std::vector<WaveConfig> waveConfigs;
        for (int i = 0; i < waveCount; ++i)
        {
            waveConfigs.push_back(
                { {w * 0.25f, i * h * waveVerticalSlice}, {w / 2, h *waveVerticalSlice }, 4, 8, 5.0f / (1+(i * 25634) % 15) }
            );
            waveConfigs.push_back(
                { {w * 0.75f, i * h * waveVerticalSlice}, {w / 2, h *waveVerticalSlice }, 4, 8, 5.0f / (1+(i * 2534) % 15) }
            );
        }

        for (auto& conf : waveConfigs)
        {
            m_waves.push_back(new Wave(engine, scene, conf));
        }
    }

    Water::~Water()
    {
        for (auto* wave : m_waves)
        {
            delete wave;
        }
    }

    Wave::Wave(GameEngine& engine, ramses::Scene& scene, WaveConfig waveConfig)
        : AnimatedSprite2D(engine, scene, engine.WaterTexture, engine.TexturedQuadEffect)
        , m_config(waveConfig)
        , m_additionalTranslate(*scene.createNode())
    {
        setPosition(waveConfig.offset.x, waveConfig.offset.y);
        setSize(waveConfig.size.x, waveConfig.size.y);
        setBlending(false);

        ramses::Node* currentParent = m_translateNode.getParent();
        m_translateNode.setParent(m_additionalTranslate);
        if(nullptr != currentParent)
            m_additionalTranslate.setParent(*currentParent);
    }

    void Wave::updateTime(float time)
    {
        Vector2 translate = Vector2(0.0f);
        Float modifiedTime = time * m_config.jiggleSpeed;
        translate += m_config.jiggleDistance * Vector2(pow(sin(modifiedTime + m_config.timeOffset), 4), -pow(cos(modifiedTime + m_config.timeOffset), 4));
        m_additionalTranslate.setTranslation(translate.x, translate.y, 0);
    }

}
