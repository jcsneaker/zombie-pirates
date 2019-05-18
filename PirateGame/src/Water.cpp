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
        std::vector<WaveConfig> waveConfigs =
        {
            { {w, h/6}, {w/2, h/2/*1.0f * (h / 8)*/}, 4, 5, 6},
            { {w, h/6}, {w/2, h/2/*2.0f * (h / 8)*/}, 4, 5, 6},
            { {w, h/6}, {w/2, h/2/*3.0f * (h / 8)*/}, 4, 5, 6},
        };

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
    {
        setPosition(waveConfig.offset.x, waveConfig.offset.y);
        setSize(waveConfig.size.x, waveConfig.size.y);
        setBlending(false);
    }

    void Wave::updateTime(float time)
    {
        AnimatedSprite2D::updateTime(time);
    }

}
