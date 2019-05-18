//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "GameEngine.h"
#include "ramses-utils.h"
#include "Sprite2D.h"
#include "RendererLib/WindowedRenderer.h"
#include "PlatformAbstraction/PlatformTime.h"
#include "PlatformAbstraction/PlatformThread.h"
#include "TGALoader.h"
#include "Pos2D.h"

namespace ramses_internal
{
    // prepare triangle geometry: vertex position array and index array
    static const float vertexPositionsArray[] =
    {
        0.0f, 0.0f, -1.f,
        1.0f, 0.0f, -1.f,
        1.0f, -1.0f, -1.f,
        0.0f, -1.0f, -1.f
    };

    static const float textureCoordsArray[] = {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };

    static const uint16_t indicesArray[] = { 0, 2, 1, 0, 3, 2 };

    GameEngine::GameEngine(RamsesClient& client, RamsesRenderer& renderer, displayId_t display)
        : m_client(client)
        , m_renderer(renderer)
        , m_display(display)
        , m_keyListener(nullptr)
        , m_updating(false)
        , m_sceneIdCounter(1u)
        , QuadVertexPositions(*client.createConstVector3fArray(4, vertexPositionsArray))
        , QuadTexCoords(*client.createConstVector2fArray(4, textureCoordsArray))
        , QuadIndices(*client.createConstUInt16Array(6, indicesArray))
        , TexturedQuadEffect(createEffect("res/default.vert", "res/textured_rgba.frag"))
        , TexturedQuadEffectWithFade(createEffect("res/default.vert", "res/textured_rgba_with_fade.frag"))
        , ShipEffect(createEffect("res/default.vert", "res/ship.frag"))
        , TextEffect(createEffect("res/textEffect.vert", "res/textEffect.frag"))
        , CannonEffect(createEffect("res/cannon.vert", "res/cannon.frag"))
        , CannonballEffect(createEffect("res/default.vert", "res/textured_rgba.frag"))
        , ExplosionEffect(createEffect("res/explosion.vert", "res/explosion.frag"))
        , TentacleEffect(createEffect("res/default.vert", "res/tentacle.frag"))
        , FadeOutEffect(createEffect("res/default.vert", "res/fadeout.frag"))
        , GuardShipTexture(*TGALoader::LoadTga("res/guardship.tga", client))
        , PirateShipTexture(*TGALoader::LoadTga("res/pirateship.tga", client))
        , CannonTexture(*TGALoader::LoadTga("res/cannon.tga", client))
        , CannonballTexture(*TGALoader::LoadTga("res/cannonball.tga", client))
        , BangTexture1(*TGALoader::LoadTga("res/bang1.tga", client))
        , BangTexture2(*TGALoader::LoadTga("res/bang2.tga", client))
        , ExplosionTexture(*TGALoader::LoadTga("res/explosion.tga", client))
        , LittleFire1(*TGALoader::LoadTga("res/littleFire1.tga", client))
        , LittleFire2(*TGALoader::LoadTga("res/littleFire2.tga", client))
        , MediumFire(*TGALoader::LoadTga("res/mediumFire.tga", client))
        , OmgOmgOmg(*TGALoader::LoadTga("res/omgOmgOmg.tga", client))
        , WaterTexture(*ramses::RamsesUtils::CreateTextureResourceFromPng("res/waves.png", client))
        , Johnny(*TGALoader::LoadTga("res/johnny.tga", client))
        , Carol(*TGALoader::LoadTga("res/carol.tga", client))
        , Max(*TGALoader::LoadTga("res/max.tga", client))
        , Philipp(*TGALoader::LoadTga("res/philipp.tga", client))
        , Marco(*TGALoader::LoadTga("res/marko.tga", client))
        , GoodguyProbablyLame(*TGALoader::LoadTga("res/goodguy.tga", client))
        , HeadTentacle(*TGALoader::LoadTga("res/head.tga", client))
        , LeftTentacle(*TGALoader::LoadTga("res/lefttentacle.tga", client))
        , RightFatTentacle(*TGALoader::LoadTga("res/rightfattentacle.tga", client))
        , RightSlimTentacle(*TGALoader::LoadTga("res/rightslimtentacle.tga", client))
    {
        m_renderer.startThread();
    }

    GameEngine::~GameEngine()
    {
        m_renderer.stopThread();

        m_client.destroy(QuadVertexPositions);
        m_client.destroy(QuadTexCoords);
        m_client.destroy(QuadIndices);
        m_client.destroy(ShipEffect);
        m_client.destroy(TextEffect);
        m_client.destroy(CannonEffect);
        m_client.destroy(CannonballEffect);
        m_client.destroy(ExplosionEffect);
        m_client.destroy(TentacleEffect);
        m_client.destroy(FadeOutEffect);
        m_client.destroy(GuardShipTexture);
        m_client.destroy(PirateShipTexture);
        m_client.destroy(CannonTexture);
        m_client.destroy(CannonballTexture);
        m_client.destroy(BangTexture1);
        m_client.destroy(BangTexture2);
        m_client.destroy(ExplosionTexture);
        m_client.destroy(LittleFire1);
        m_client.destroy(LittleFire2);
        m_client.destroy(MediumFire);
        m_client.destroy(OmgOmgOmg);
        m_client.destroy(Johnny);
        m_client.destroy(Carol);
        m_client.destroy(Max);
        m_client.destroy(Philipp);
        m_client.destroy(Marco);
        m_client.destroy(GoodguyProbablyLame);
        m_client.destroy(HeadTentacle);
        m_client.destroy(LeftTentacle);
        m_client.destroy(RightFatTentacle);
        m_client.destroy(RightSlimTentacle);
    }

    void GameEngine::doOneRendererLoop()
    {
        for(auto sIter: m_scenes)
        {
            ramses::Scene* scene = sIter.scene;
            scene->flush();
        }

        m_renderer.flush();
        m_renderer.dispatchEvents(*this);

        // To slow down stuff
        PlatformThread::Sleep(15u);
    }

    void GameEngine::setKeyListener(IKeyListener& keyListener)
    {
        m_keyListener = &keyListener;
    }

    void GameEngine::unsetKeyListener()
    {
        m_keyListener = nullptr;
    }

    ramses::Scene& GameEngine::pushScene()
    {
        sceneId_t newSceneId = m_sceneIdCounter++;
        ramses::Scene& newScene = *m_client.createScene(newSceneId);
        const RemoteCamera& camera = *newScene.createRemoteCamera();
        ramses::RenderPass& renderPass = *newScene.createRenderPass("");
        renderPass.setCamera(camera);
        ramses::RenderGroup& renderGroup = *newScene.createRenderGroup("");
        renderPass.addRenderGroup(renderGroup);

        SceneData sceneData = { SceneData::ESceneState_Created, &newScene, &renderGroup };
        m_scenes.push_back(sceneData);

        newScene.publish();
        while (!sceneInState(newSceneId, SceneData::ESceneState_Published))
        {
            doOneRendererLoop();
        }

        m_renderer.subscribeScene(newSceneId);
        while (!sceneInState(newSceneId, SceneData::ESceneState_Subscribed))
        {
            doOneRendererLoop();
        }

        m_renderer.mapScene(m_display, newSceneId);
        while (!sceneInState(newSceneId, SceneData::ESceneState_Mapped))
        {
            doOneRendererLoop();
        }

        m_renderer.showScene(newSceneId);
        while (!sceneInState(newSceneId, SceneData::ESceneState_Mapped))
        {
            doOneRendererLoop();
        }

        return newScene;
    }

    ramses::Scene& GameEngine::getCurrentScene() const
    {
        assert(m_scenes.size() > 0);
        ramses::Scene* currentScene = m_scenes[m_scenes.size() - 1].scene;
        return *currentScene;
    }

    ramses::RenderGroup& GameEngine::getCurrentRenderGroup() const
    {
        assert(m_scenes.size() > 0);
        ramses::RenderGroup* currentRenderGroup = m_scenes[m_scenes.size() - 1].renderGroup;
        return *currentRenderGroup;
    }

    void GameEngine::popScene()
    {
        const sceneId_t currentSceneId = m_scenes[m_scenes.size() - 1].scene->getSceneId();
        m_renderer.hideScene(currentSceneId);
        while (!sceneInState(currentSceneId, SceneData::ESceneState_Mapped))
        {
            doOneRendererLoop();
        }

        m_renderer.unmapScene(currentSceneId);
        while (!sceneInState(currentSceneId, SceneData::ESceneState_Subscribed))
        {
            doOneRendererLoop();
        }

        m_renderer.unsubscribeScene(currentSceneId);
        while (!sceneInState(currentSceneId, SceneData::ESceneState_Published))
        {
            doOneRendererLoop();
        }
    }

    void GameEngine::addSprite(Sprite2D& sprite, int32_t renderOrder)
    {
        assert(!m_updating);
        m_sprites.push_back(&sprite);

        getCurrentRenderGroup().addMeshNode(sprite.getMesh(), renderOrder);
    }

    void GameEngine::removeSprite(Sprite2D& sprite)
    {
        assert(!m_updating);
        std::vector<Sprite2D*>::iterator sprIter = std::find(m_sprites.begin(), m_sprites.end(), &sprite);
        assert(sprIter != m_sprites.end());
        m_sprites.erase(sprIter);
    }

    void GameEngine::addAnimatedSprite(AnimatedSprite2D& sprite)
    {
        assert(!m_updating);
        m_animatedSprites.push_back(&sprite);
    }

    void GameEngine::removeAnimatedSprite(AnimatedSprite2D& sprite)
    {
        assert(!m_updating);
        std::vector<AnimatedSprite2D*>::iterator sprIter = std::find(m_animatedSprites.begin(), m_animatedSprites.end(), &sprite);
        assert(sprIter != m_animatedSprites.end());
        m_animatedSprites.erase(sprIter);
    }

    void GameEngine::fadeIn(uint32_t timeMS)
    {
        Sprite2D fadeQuad(*this, getCurrentScene(), FadeOutEffect);
        UniformInput fadeFactor;
        status_t found = fadeQuad.m_effect.findUniformInput("u_fadeFactor", fadeFactor);
        assert(StatusOK == found);
        UNUSED(found);

        fadeQuad.setPosition(Pos2D::s_WindowWidth / 2.0f, Pos2D::s_WindowHeight / 2.0f);
        fadeQuad.setSize(static_cast<Float>(Pos2D::s_WindowWidth), static_cast<Float>(Pos2D::s_WindowHeight));

        const UInt64 startTime = PlatformTime::GetMillisecondsAbsolute();

        while (PlatformTime::GetMillisecondsAbsolute() - startTime < timeMS)
        {
            float fade = (PlatformTime::GetMillisecondsAbsolute() - startTime) / static_cast<float>(timeMS);
            fadeQuad.m_appearance.setInputValueFloat(fadeFactor, 1 - fade);
            doOneRendererLoop();
        }
    }

    void GameEngine::fadeOut(uint32_t timeMS)
    {
        Sprite2D fadeQuad(*this, getCurrentScene(), FadeOutEffect);
        UniformInput fadeFactor;
        status_t found = fadeQuad.m_effect.findUniformInput("u_fadeFactor", fadeFactor);
        assert(StatusOK == found);
        UNUSED(found);

        fadeQuad.setPosition(Pos2D::s_WindowWidth / 2.0f, Pos2D::s_WindowHeight / 2.0f);
        fadeQuad.setSize(static_cast<Float>(Pos2D::s_WindowWidth), static_cast<Float>(Pos2D::s_WindowHeight));

        const UInt64 startTime = PlatformTime::GetMillisecondsAbsolute();

        while (PlatformTime::GetMillisecondsAbsolute() - startTime < timeMS)
        {
            float fade = (PlatformTime::GetMillisecondsAbsolute() - startTime) / static_cast<float>(timeMS);
            fadeQuad.m_appearance.setInputValueFloat(fadeFactor, fade);
            doOneRendererLoop();
        }
    }

    void GameEngine::updateSprites(float time)
    {
        m_updating = true;
        for(auto sprite: m_animatedSprites)
        {
            sprite->updateTime(time);
        }
        m_updating = false;
    }

    void GameEngine::setFadeRange(Appearance& appearance, Vector2 fadeRange)
    {
        UniformInput fadeRangeInput;
        status_t found = appearance.getEffect().findUniformInput("u_fadeRange", fadeRangeInput);
        assert(found == StatusOK);
        UNUSED(found);
        appearance.setInputValueVector2f(fadeRangeInput, fadeRange.x, fadeRange.y);
    }

    void GameEngine::setMeshRenderOrder(MeshNode& mesh, int32_t renderORder)
    {
        status_t inGroup = getCurrentRenderGroup().removeMeshNode(mesh);
        assert(inGroup == StatusOK);
        inGroup = getCurrentRenderGroup().addMeshNode(mesh, renderORder);
        assert(inGroup == StatusOK);
        UNUSED(inGroup);
    }

    const ramses::Effect& GameEngine::createEffect(const char* vertShader, const char* fragShader)
    {
        // create an appearance for red triangle
        ramses::EffectDescription effectDesc;
        effectDesc.setVertexShaderFromFile(vertShader);
        effectDesc.setFragmentShaderFromFile(fragShader);
        effectDesc.setUniformSemantic("mvpMatrix", ramses::EEffectUniformSemantic_ModelViewProjectionMatrix);

        // Surprise! hack
        if (String(vertShader) == String("res/textEffect.vert"))
        {
            effectDesc.setAttributeSemantic("a_position", EEffectAttributeSemantic_TextPositions);
            effectDesc.setAttributeSemantic("a_texcoord", EEffectAttributeSemantic_TextTextureCoordinates);
            effectDesc.setUniformSemantic("u_texture", EEffectUniformSemantic_TextTexture);
        }

        const ramses::Effect* effect = m_client.createEffect(effectDesc, ramses::ResourceCacheFlag_DoNotCache, fragShader);

        return *effect;
    }


    GameEngine::SceneIterator GameEngine::findScene(ramses::sceneId_t sceneId)
    {
        GameEngine::SceneIterator result = m_scenes.end();
        for (GameEngine::SceneIterator sceneIter = m_scenes.begin(); sceneIter != m_scenes.end(); sceneIter++)
        {
            SceneData& data = *sceneIter;
            if (sceneId == data.scene->getSceneId())
            {
                assert(result == m_scenes.end());
                result = sceneIter;
            }
        }
        assert(result != m_scenes.end());
        return result;
    }

    bool GameEngine::sceneInState(ramses::sceneId_t sceneId, SceneData::ESceneState state)
    {
        GameEngine::SceneIterator scene = findScene(sceneId);
        return scene->state == state;
    }

    void GameEngine::scenePublished(ramses::sceneId_t sceneId)
    {
        GameEngine::SceneIterator scene = findScene(sceneId);
        scene->state = SceneData::ESceneState_Published;
    }

    void GameEngine::sceneSubscribed(ramses::sceneId_t sceneId, ramses::ERendererEventResult result)
    {
        GameEngine::SceneIterator scene = findScene(sceneId);
        scene->state = SceneData::ESceneState_Subscribed;
        assert(ERendererEventResult_OK == result);
        UNUSED(result);
    }

    void GameEngine::sceneMapped(ramses::sceneId_t sceneId, ramses::ERendererEventResult result)
    {
        GameEngine::SceneIterator scene = findScene(sceneId);
        scene->state = SceneData::ESceneState_Mapped;
        assert(ERendererEventResult_OK == result);
        UNUSED(result);
    }

    void GameEngine::sceneShown(ramses::sceneId_t sceneId, ramses::ERendererEventResult result)
    {
        GameEngine::SceneIterator scene = findScene(sceneId);
        scene->state = SceneData::ESceneState_Rendered;
        assert(ERendererEventResult_OK == result);
        UNUSED(result);
    }

    void GameEngine::sceneUnpublished(sceneId_t sceneId)
    {
        GameEngine::SceneIterator scene = findScene(sceneId);
        m_scenes.erase(scene);
    }

    void GameEngine::sceneUnsubscribed(sceneId_t sceneId, ERendererEventResult result)
    {
        GameEngine::SceneIterator scene = findScene(sceneId);
        scene->state = SceneData::ESceneState_Published;
        assert(ERendererEventResult_OK == result);
        UNUSED(result);
    }

    void GameEngine::sceneUnmapped(sceneId_t sceneId, ERendererEventResult result)
    {
        GameEngine::SceneIterator scene = findScene(sceneId);
        scene->state = SceneData::ESceneState_Subscribed;
        assert(ERendererEventResult_OK == result);
        UNUSED(result);
    }

    void GameEngine::sceneHidden(sceneId_t sceneId, ERendererEventResult result)
    {
        GameEngine::SceneIterator scene = findScene(sceneId);
        scene->state = SceneData::ESceneState_Mapped;
        assert(ERendererEventResult_OK == result);
        UNUSED(result);
    }

    void GameEngine::keyEvent(ramses::displayId_t display, ramses::EKeyEvent keyEvent, uint32_t, ramses::EKeyCode keyCode)
    {
        if (nullptr != m_keyListener)
        {
            m_keyListener->keyEvent(display, keyEvent, 0, keyCode);
        }
    }

}
