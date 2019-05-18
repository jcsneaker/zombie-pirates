#include "Ship.h"
#include "PlatformAbstraction/PlatformMath.h"
#include "Cannonball.h"
#include "Explosion.h"
#include "Tentacles.h"


namespace ramses_internal
{

    Ship::Ship(GameEngine& engine, Scene& scene, EShip whoAmI, TentaclesState& tentacleState)
        : AnimatedSprite2D(engine, scene, (EShip_LEFT == whoAmI) ? engine.GuardShipTexture : engine.PirateShipTexture, engine.ShipEffect, 1, 1, 9)
        , m_whoAmI(whoAmI)
        , m_tentacleState(tentacleState)
        , m_moveStatus(EDirection_NONE)
        , m_facing(EDirection_UP)
        , m_velocityY(0)
        , m_lastTimeUpdated(-1.0f)
        , m_canonPoweringUp(0)
        , m_cannonPower(0.0f)
        , m_cannon1(engine, scene, EShip_LEFT != whoAmI, CannonBaseOffsetShips[whoAmI] + Vector2(0, 0), m_rotationNode)
        , m_cannon2(engine, scene, EShip_LEFT != whoAmI, CannonBaseOffsetShips[whoAmI] + Vector2(0, 60), m_rotationNode)
        , m_cannon3(engine, scene, EShip_LEFT != whoAmI, CannonBaseOffsetShips[whoAmI] + Vector2(0, 120), m_rotationNode)
        , m_cannonBang(engine, scene, EShip_LEFT == whoAmI ? engine.BangTexture1 : engine.BangTexture2, engine.TexturedQuadEffect)
        , m_damage(EShip_LEFT == whoAmI ? static_cast<ShipDamage*>(new LeftShipDamage(engine, scene)) : static_cast<ShipDamage*>(new RightShipDamage(engine, scene)))
        , m_crew(EShip_LEFT == whoAmI ? static_cast<Crew*>(new GoodGuys(engine, scene)) : static_cast<Crew*>(new PirateCrew(engine, scene)))
    {
        if (EShip_LEFT == whoAmI)
        {
            setPosition(ShipOffset, 130);
        }
        else
        {
            setPosition(Pos2D::s_WindowWidth - ShipOffset, 330);
        }

        m_cannonBang.m_scaleNode.scale(0.5f, 0.5f, 0.5f);
        m_cannonBang.setVisibility(false);

        m_damage->rootNode.setParent(m_rotationNode);
        m_damage->damageBar.m_rootNode.setParent(m_translateNode);
        m_crew->rootNode.setParent(m_rotationNode);

        // put behind flames
        m_damage->putBehind(m_meshNode);

        Vector2 absPos = getAbsolute2DPosition();
        Vector2 absSize = getAbsolute2DSize();
        Vector2 shipFade;
        if (EShip_LEFT == whoAmI)
        {
            shipFade = Vector2(absPos.x + absSize.x / 2 - 50.0f, absPos.x + absSize.x / 2);
            tentacleState.setFadeRange(whoAmI, shipFade - Vector2(75.0f, 25.0f));
        }
        else
        {
            shipFade = Vector2(absPos.x - absSize.x / 2 + 50.0f, absPos.x - absSize.x / 2);
            //tentacleState.setFadeRange(whoAmI, Vector2(1220.0f, 1120.0f));
            tentacleState.setFadeRange(whoAmI, shipFade + Vector2(67.0f, 17.0f));
        }

        m_engine.setFadeRange(m_appearance, shipFade);
        m_engine.setFadeRange(m_cannon1.m_appearance, shipFade);
        m_engine.setFadeRange(m_cannon2.m_appearance, shipFade);
        m_engine.setFadeRange(m_cannon3.m_appearance, shipFade);
        m_damage->setFadeRange(shipFade);
        m_crew->setFadeRange(shipFade);
    }

    Ship::~Ship()
    {
    }

    void Ship::updateTime(float time)
    {
        AnimatedSprite2D::updateTime(time);

        float timeDiff = 0;
        if (m_lastTimeUpdated > 0)
        {
            timeDiff = time - m_lastTimeUpdated;
        }
        m_lastTimeUpdated = time;

        Float maxVelocity = MaxShipVelocity;
        Float maxSpeed = MaxShipSpeed;
        if (m_tentacleState.getShip() == this)
        {
            maxVelocity *= SlowDownWhenTentackled;
            maxSpeed *= SlowDownWhenTentackled;
        }

        switch (m_moveStatus)
        {
        case EDirection_NONE:
            m_velocityY = /*(time - m_lastTimeUpdated) **/ 0.9f *m_velocityY;
            break;
        case EDirection_UP:
            m_velocityY = max(-maxVelocity, m_velocityY - 0.01f);
            break;
        case EDirection_DOWN:
            m_velocityY = min(maxVelocity, m_velocityY + 0.01f);
            break;
        }

        float posX, posY;
        getPosition(posX, posY);

        posY += timeDiff * m_velocityY * maxSpeed;

        if (posY < 0)
        {
            posY = 0;
        }
        else if (posY > Pos2D::s_WindowHeight)
        {
            posY = Pos2D::s_WindowHeight;
        }

        setPosition(posX, posY);

        if (time - m_cannonBangStart > BangDuration)
        {
            m_cannonBang.setVisibility(false);
        }
    }

    Cannon& Ship::getCurrentCannon()
    {
        switch (m_canonPoweringUp)
        {
        case 1:
        case -1:
            return m_cannon1;
        case 2:
        case -2:
            return m_cannon2;
        case 3:
        case -3:
            return m_cannon3;
        default:
            assert(false);
            return m_cannon3;
        }
    }

    void Ship::handleInput(float time)
    {
        // TODO rework for android
        //Bool upPressed   = 0 != ((1 << 16) & GetAsyncKeyState(m_whoAmI == EShip_LEFT ? 'W' : VK_UP));
        //Bool downPressed = 0 != ((1 << 16) & GetAsyncKeyState(m_whoAmI == EShip_LEFT ? 'S' : VK_DOWN));
        //Bool firePressed = 0 != ((1 << 16) & GetAsyncKeyState(m_whoAmI == EShip_LEFT ? VK_SPACE : VK_RETURN));

        Bool upPressed = int32_t(time * 1000) % 500 > 250;
        Bool downPressed = int32_t(time * 1000) % 500 < 250;
        Bool firePressed = int32_t(time * 1000) % 500 > 400;

        if (upPressed && !downPressed)
        {
            m_moveStatus = EDirection_UP;
        }
        else if (!upPressed && downPressed)
        {
            m_moveStatus = EDirection_DOWN;
        }
        else
        {
            m_moveStatus = EDirection_NONE;
        }

        if (m_facing == EDirection_UP && m_moveStatus == EDirection_DOWN || m_facing == EDirection_DOWN && m_moveStatus == EDirection_UP)
        {
            m_rotationNode.rotate(180, 0, 0);
            m_facing = m_moveStatus;
        }

        if (firePressed)
        {
            // firing cannon, power up
            if (m_canonPoweringUp > 0)
            {
                m_cannonPower = min(MaxPowerUp, m_cannonPower + PowerUpSpeed);
                getCurrentCannon().setShootProgress(m_cannonPower / MaxPowerUp);
            }
            // want to start firing -> check if I can
            else if (m_cannonballs.size() < MaxCannonBalls)
            {
                //TODO randomize again
                //m_canonPoweringUp = static_cast<int32_t>(PlatformMath::Random(1, 4));
                m_canonPoweringUp = 3;
            }
        }
        // not firing anymore, but a cannon is powered up -> fire
        else if (m_canonPoweringUp > 0)
        {
            fireCannon(m_cannonPower);
            m_cannonPower = 0.0f;
            getCurrentCannon().setShootProgress(0.0f);
            m_cannonBang.setVisibility(true);
            m_cannonBang.m_rootNode.setParent(getCurrentCannon().m_rootNode);
            m_canonPoweringUp = 0;
            m_cannonBangStart = time;
        }
    }

    void Ship::fireCannon(Float power)
    {
        Vector2 speed = Vector2(0.10f, 0.0f) * (1 + power);
        if (m_whoAmI == EShip_RIGHT)
        {
            speed = -speed;
        }
        Cannonball* cannonball = new Cannonball(m_engine, m_scene, speed);

        Vector2 cannonPosition = getCurrentCannon().getAbsolute2DPosition();
        if (m_whoAmI == EShip_LEFT)
        {
            cannonPosition.x -= 30;
        }
        else
        {
            cannonPosition.x += 30;
        }

        cannonball->setPosition(cannonPosition.x, cannonPosition.y);
        m_cannonballs.push_back(cannonball);
    }

    CannonballCollisions Ship::getCannonCollisions(Ship& otherShip, Float /*time*/)
    {
        CannonballCollisions collisions;

        Vector2 shipPosition = otherShip.getAbsolute2DPosition();
        Vector2 shipSize = otherShip.getAbsolute2DSize();

        Cannonballs leftCannonballs;
        for (UInt i = 0; i < m_cannonballs.size(); ++i)
        {
            const Cannonball* cannonball = m_cannonballs[i];
            const Vector2 cannonPos = cannonball->getAbsolute2DPosition();

            if (PlatformMath::Abs(cannonPos.y - shipPosition.y) < (shipSize.y / 2 + cannonball->size.y) &&
                PlatformMath::Abs(cannonPos.x - shipPosition.x) < (cannonball->size.x))
            {
                delete cannonball;
                otherShip.takeHit(cannonPos);
                collisions.push_back(CannonballCollision{this, &otherShip, cannonPos});
            }
            else if (   cannonPos.x > Pos2D::s_WindowWidth + cannonball->size.x/2 ||
                        cannonPos.x < -cannonball->size.x / 2)
            {
                delete cannonball;
            }
            else
            {
                leftCannonballs.push_back(cannonball);
            }
        }

        m_cannonballs = leftCannonballs;
        return collisions;
    }

    void Ship::takeHit(const Vector2& cannonPos)
    {
        Explosion* explosion = new Explosion(m_engine, m_scene, 1.0f);
        explosion->setPosition(cannonPos.x, cannonPos.y);
        m_explosions.push_back(explosion);
        m_damage->addDamage();
    }

    void Ship::handleExplosions(float /*time*/)
    {
        std::vector<Explosion*> explosionsToKeep;
        for (const auto explosion : m_explosions)
        {
            if (explosion->expired())
            {
                delete explosion;
            }
            else
            {
                explosionsToKeep.push_back(explosion);
            }
        }

        m_explosions.swap(explosionsToKeep);
    }

    EShip Ship::getIdentity() const
    {
        return m_whoAmI;
    }

    ShipDamage& Ship::getDamage()
    {
        return *m_damage;
    }

    const ShipDamage& Ship::getDamage() const
    {
        return *m_damage;
    }

}
