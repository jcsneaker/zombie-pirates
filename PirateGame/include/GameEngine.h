//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_GAMEENGINE_H
#define RAMSES_GAMEENGINE_H

#include "ramses-client.h"
#include "Collections/Vector.h"
#include "Math3d/Vector2.h"
#include "ramses-renderer-api/RamsesRenderer.h"
#include "ramses-renderer-api/IRendererEventHandler.h"

using ramses::UniformInput;
using ramses::AttributeInput;
using ramses::Effect;
using ramses::Texture2D;
using ramses::RamsesClient;
using ramses::displayId_t;
using ramses::RamsesRenderer;
using ramses::Appearance;
using ramses::MeshNode;

namespace ramses_internal
{
    class Sprite2D;
    class AnimatedSprite2D;
    class WindowedRenderer;
    class ISession;

    const Float ShipOffset = 250.0f;
    const Vector2 CannonBaseOffsetShips[] = { Vector2(50.0f, -30), Vector2(-55, -30) };
    // pixel per second :)
    const Float MaxShipSpeed = 1200.0f;
    const Float MaxCannonSpeed = 20.0f;
    const Float MaxShipVelocity = 1.0f;
    const Float PowerUpSpeed = 0.5f;
    const Float BangDuration = 0.5f;
    const Float ShipExplosionTime = 0.8f;
    const Float MaxPowerUp = 5.0f;
    const UInt32 MaxCannonBalls = 4;
    const Float TentacleRiseTime = 2.5f;
    const Float TentacleTimeToArrive = TentacleRiseTime + 1.5f;
    const Float TentacleTimeUntilSinkAgain = 10.0f;
    const Float TentacleWiggleTime = 2.0f;
    const Float DamagePerHit = 0.1f;
    const Float SlowDownWhenTentackled = 0.6f;

    class IKeyListener
    {
    public:
        virtual ~IKeyListener() {}
        virtual void keyEvent(ramses::displayId_t, ramses::EKeyEvent keyEvent, uint32_t, ramses::EKeyCode keyCode) = 0;
    };

    class GameEngine : public ramses::RendererEventHandlerEmpty
    {
    public:
        GameEngine(RamsesClient& client, RamsesRenderer& renderer, displayId_t display);
        virtual ~GameEngine();

        void doOneRendererLoop();

        void setKeyListener(IKeyListener& keyListener);
        void unsetKeyListener();

        ramses::Scene& pushScene();
        ramses::Scene& getCurrentScene() const;
        void popScene();

        ramses::RenderGroup& getCurrentRenderGroup() const;

        void addSprite(Sprite2D& sprite, int32_t renderOrder);
        void removeSprite(Sprite2D& sprite);
        void addAnimatedSprite(AnimatedSprite2D& sprite);
        void removeAnimatedSprite(AnimatedSprite2D& sprite);

        void fadeIn(uint32_t timeMS);
        void updateSprites(float time);

        void fadeOut(uint32_t timeMS);

        void setFadeRange(Appearance& appearance, Vector2 fadeRange);
        void setMeshRenderOrder(MeshNode& mesh, int32_t renderORder);

    private:
        const ramses::Effect& createEffect(const char* vertShader, const char* fragShader);

        // From ramses::RendererEventHandlerEmpty
        virtual void scenePublished(ramses::sceneId_t sceneId) override final;
        virtual void sceneSubscribed(ramses::sceneId_t sceneId, ramses::ERendererEventResult result) override final;
        virtual void sceneMapped(ramses::sceneId_t sceneId, ramses::ERendererEventResult result) override final;
        virtual void sceneShown(ramses::sceneId_t sceneId, ramses::ERendererEventResult result) override final;
        virtual void sceneUnpublished(ramses::sceneId_t sceneId) override final;
        virtual void sceneUnsubscribed(ramses::sceneId_t sceneId, ramses::ERendererEventResult result) override final;
        virtual void sceneUnmapped(ramses::sceneId_t sceneId, ramses::ERendererEventResult result) override final;
        virtual void sceneHidden(ramses::sceneId_t sceneId, ramses::ERendererEventResult result) override final;
        virtual void keyEvent(ramses::displayId_t, ramses::EKeyEvent keyEvent, uint32_t, ramses::EKeyCode keyCode) override final;

        ramses::RamsesClient& m_client;
        RamsesRenderer& m_renderer;
        displayId_t m_display;
        IKeyListener* m_keyListener;

        Bool m_updating;

        struct SceneData
        {
            enum ESceneState
            {
                ESceneState_Created = 0,
                ESceneState_Published,
                ESceneState_Subscribed,
                ESceneState_Mapped,
                ESceneState_Rendered
            };

            ESceneState state;
            ramses::Scene* scene;
            ramses::RenderGroup* renderGroup;
        };

        ramses::sceneId_t m_sceneIdCounter;
        using SceneCollection = std::vector<SceneData>;
        using SceneIterator = SceneCollection::iterator;
        SceneCollection m_scenes;
        std::vector<Sprite2D*> m_sprites;
        std::vector<AnimatedSprite2D*> m_animatedSprites;

        SceneIterator findScene(ramses::sceneId_t sceneId);
        bool sceneInState(ramses::sceneId_t sceneId, SceneData::ESceneState state);

    public:
        const ramses::Vector3fArray& QuadVertexPositions;
        const ramses::Vector2fArray& QuadTexCoords;
        const ramses::UInt16Array& QuadIndices;

        const ramses::Effect& TexturedQuadEffect;
        const ramses::Effect& TexturedQuadEffectWithFade;
        const ramses::Effect& ShipEffect;
        const ramses::Effect& TextEffect;
        const ramses::Effect& CannonEffect;
        const ramses::Effect& CannonballEffect;
        const ramses::Effect& ExplosionEffect;
        const ramses::Effect& TentacleEffect;
        const ramses::Effect& FadeOutEffect;

        const Texture2D& GuardShipTexture;
        const Texture2D& PirateShipTexture;
        const Texture2D& CannonTexture;
        const Texture2D& CannonballTexture;
        const Texture2D& BangTexture1;
        const Texture2D& BangTexture2;
        const Texture2D& ExplosionTexture;
        const Texture2D& LittleFire1;
        const Texture2D& LittleFire2;
        const Texture2D& MediumFire;
        const Texture2D& OmgOmgOmg;
        const Texture2D& WaterTexture;

        const Texture2D& Johnny;
        const Texture2D& Carol;
        const Texture2D& Max;
        const Texture2D& Philipp;
        const Texture2D& Marco;
        const Texture2D& GoodguyProbablyLame;

        const Texture2D& HeadTentacle;
        const Texture2D& LeftTentacle;
        const Texture2D& RightFatTentacle;
        const Texture2D& RightSlimTentacle;
    };
}

#endif
