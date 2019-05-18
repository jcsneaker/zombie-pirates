//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifdef WIN32

#include "PirateGame.h"

int main(int argc, char* argv[])
{
    const int32_t width = 600;
    const int32_t height = 800;

    PirateGame game(width, height);

    while (!game.finished())
    {
        game.doFrame();
    }
}

#endif
