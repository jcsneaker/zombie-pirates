//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#include "DisplayManager/UnmapScene.h"

namespace ramses_display_manager
{
    UnmapScene::UnmapScene(IDisplayManager& displayManager)
        : m_displayManager(displayManager)
    {
        description = "Unmap a scene from a display";
        registerKeyword("unmapScene");

        getArgument<0>()
            .registerKeyword("sceneId")
            .setDescription("Scene id");
    }

    bool UnmapScene::execute(uint64_t& sceneId) const
    {
        m_displayManager.unmapScene(ramses::sceneId_t(sceneId));

        return true;
    }
}
