//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_POS2D_H
#define RAMSES_POS2D_H

#include "Collections/Pair.h"
#include <utility>

namespace ramses_internal
{
    typedef std::pair < float, float > PosBase;
    struct Pos2D : public PosBase
    {
        Pos2D(float x, float y)
            : PosBase(x, y)
        {
        }

        float x() const
        {
            return PosBase::first;
        }

        float y() const
        {
            return PosBase::second;
        }
        
        static void SetWindowSize(int32_t width, int32_t height);

        static float s_WindowWidth;
        static float s_WindowHeight;

    };
}

#endif
