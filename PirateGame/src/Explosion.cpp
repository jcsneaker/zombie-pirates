#include "Explosion.h"
#include "GameEngine.h"

namespace ramses_internal
{
    const uint32_t tilesX = 8;
    const uint32_t tilesY = 6;

    Explosion::Explosion(GameEngine& engine, Scene& scene, Float size)
        : AnimatedSprite2D(engine, scene, engine.ExplosionTexture, engine.ExplosionEffect, tilesX, tilesY)
        , m_timeRemaining(ShipExplosionTime)
    {
        setTile(4, 4);
        m_scaleNode.scale(size, size, size);
    }

    void Explosion::updateTime(float time)
    {
        AnimatedSprite2D::updateTime(time);

        m_timeRemaining = max(m_timeRemaining - m_timeDiff, 0.0f);
        const int32_t progressInTileNr = int32_t(PlatformMath::Floor((tilesX * tilesY - 1) * (1 - m_timeRemaining / ShipExplosionTime)));
        const int32_t tileX = progressInTileNr % tilesX;
        const int32_t tileY = progressInTileNr / tilesX;
        setTile(tileX, tileY);
    }

    Bool Explosion::expired() const
    {
        return m_timeRemaining == 0.0f;
    }
}
