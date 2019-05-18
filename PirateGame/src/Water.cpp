#include "Water.h"

namespace ramses_internal
{

    Water::Water(GameEngine& engine, ramses::Scene& scene)
        : Sprite2D(engine, scene, engine.WaterEffect)
    {
        setPosition(Pos2D::s_WindowWidth / 2.0f, Pos2D::s_WindowHeight / 2.0f);
        setSize(static_cast<Float>(Pos2D::s_WindowWidth), static_cast<Float>(Pos2D::s_WindowHeight));
        setBlending(false);
    }

}
