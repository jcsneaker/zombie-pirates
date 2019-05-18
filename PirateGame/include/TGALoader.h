//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_TGALOADER_H
#define RAMSES_TGALOADER_H

#include "PlatformAbstraction/PlatformTypes.h"
#include "Collections/Vector.h"

namespace ramses
{
    class RamsesClient;
    class Texture2D;
}

namespace ramses_internal
{
    struct TgaImage
    {
        UInt8 typeCode;
        Int16 width;
        Int16 height;
        UInt8 bitCount;
        std::vector<UInt8> data;
    };

    class TGALoader
    {
    public:
        static ramses::Texture2D* LoadTga(const char* tgaFilePath, ramses::RamsesClient& ramsesClient, const char* name = nullptr);
    };
}

#endif
