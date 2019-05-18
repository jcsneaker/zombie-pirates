//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "Cannon.h"

namespace ramses_internal
{
    Cannon::Cannon(GameEngine& engine, Scene& scene, bool rotate, Vector2 offset, Node& parent) : TexturedSprite2D(engine, scene, engine.CannonTexture, engine.CannonEffect)
        , m_offsetY(offset.y)
    {
        float scaleCanon = 0.4f;
        m_scaleNode.scale(scaleCanon, scaleCanon, scaleCanon);

        m_rootNode.setParent(parent);

        m_translateNode.translate(offset.x, offset.y, 0);

        if (rotate)
        {
            m_rotationNode.rotate(0, 0, 180);
        }

        status_t found = getMesh().getAppearance()->getEffect().findUniformInput("u_shootProgress", m_cannonShootProgress);
        assert(found == StatusOK);
    }

    void Cannon::setShootProgress(float progress)
    {
        m_appearance.setInputValueFloat(m_cannonShootProgress, progress);
    }

}
