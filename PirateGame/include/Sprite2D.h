//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_SPRITE2D_H
#define RAMSES_SPRITE2D_H

#include <ramses-client.h>
#include "Collections/Pair.h"
#include "Collections/Vector.h"
#include "ramses-client-api/UniformInput.h"
#include "Math3d/Vector2.h"

using namespace ramses;

namespace ramses_internal
{
    class GameEngine;

    class Sprite2D
    {
    public:
        Sprite2D(GameEngine& engine, ramses::Scene& scene, const ramses::Effect& effect, uint32_t renderOrderBuffer = 1);
        virtual ~Sprite2D();

        Node& getScale()
        {
            return m_scaleNode;
        }

        void setVisibility(bool enabled);

        MeshNode& getMesh()
        {
            return m_meshNode;
        }

        //void setTime(float time);
        void setSize(float width, float height);
        void setPosition(float x, float y);
        void getPosition(float& x, float& y) const;
        Vector2 getAbsolute2DPosition() const;
        Vector2 getAbsolute2DSize() const;

        void setBlending(bool enabled);

        GameEngine& m_engine;
        Scene& m_scene;

        const ramses::Effect&   m_effect;
        Node&  m_translateNode;
        Node&     m_rotationNode;
        Node&      m_scaleNode;
        MeshNode&       m_meshNode;
        Node&           m_rootNode;
        Appearance&     m_appearance;
        GeometryBinding& m_geometryBinding;
        Float           m_lastTime, m_timeDiff;
    private:
        Node&  m_translateSpriteToCenter;
        Node& m_visibilityNode;
    };

    class TexturedSprite2D : public Sprite2D
    {
    public:
        TexturedSprite2D(GameEngine& engine, ramses::Scene& scene, const Texture2D& m_texture, const ramses::Effect& effect, uint32_t renderOrderBuffer = 1);
        ~TexturedSprite2D();

    protected:
        const ramses::Texture2D& m_texture;
        ramses::TextureSampler& m_sampler;
    };

    class AnimatedSprite2D : public TexturedSprite2D
    {
    public:
        AnimatedSprite2D(GameEngine& engine, ramses::Scene& scene, const Texture2D& texture, const ramses::Effect& effect, int32_t tilesX = 1, int32_t tilesY = 1, uint32_t renderOrderBuffer = 1);
        ~AnimatedSprite2D();

        void setTile(int32_t x, int32_t y);

        virtual void updateTime(float time);

    private:
        const int32_t m_tilesX;
        const int32_t m_tilesY;
        const float m_sizeX;
        const float m_sizeY;

        UniformInput m_textureTile;
        UniformInput m_time;
    };
}

#endif
