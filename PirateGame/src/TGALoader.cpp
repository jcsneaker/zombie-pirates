//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "TGALoader.h"
#include "Utils/File.h"

#include "PlatformAbstraction/PlatformTypes.h"
#include "PlatformAbstraction/PlatformMemory.h"
#include "ramses-client-api/TextureEnums.h"
#include "ramses-client-api/MipLevelData.h"
#include "ramses-client-api/RamsesClient.h"

namespace ramses_internal
{
    ramses::Texture2D* TGALoader::LoadTga(const char* tgaImagePath, ramses::RamsesClient& ramsesClient, const char* name/* = 0*/)
    {
        ramses_internal::TgaImage tgaImage;
        File fileIn(tgaImagePath);
        if (EStatus_RAMSES_OK != fileIn.open(EFileMode_ReadOnlyBinary))
        {
            return nullptr;
        }

        Char charDump[32];

        // Read the two first bytes
        UInt nReadBytes = 0;
        fileIn.read(charDump, 2, nReadBytes);

        // Read image type
        fileIn.read(reinterpret_cast<Char*>(&tgaImage.typeCode), sizeof(tgaImage.typeCode), nReadBytes);

        // We allow only following types:
        switch (tgaImage.typeCode)
        {
        case 2: // (uncompressed RGB image)
        case 3: // (uncompressed black-and-white images)
            break;
        default:
            return nullptr;
        }

        // Read 9 bytes which are not needed
        fileIn.read(charDump, 9, nReadBytes);

        // Read the width and height
        fileIn.read(reinterpret_cast<Char*>(&tgaImage.width), sizeof(tgaImage.width), nReadBytes);
        fileIn.read(reinterpret_cast<Char*>(&tgaImage.height), sizeof(tgaImage.height), nReadBytes);

        // Read the image depth
        fileIn.read(reinterpret_cast<Char*>(&tgaImage.bitCount), sizeof(tgaImage.bitCount), nReadBytes);

        UInt8 descriptor;

        // Read descriptor
        fileIn.read(reinterpret_cast<Char*>(&descriptor), sizeof(descriptor), nReadBytes);

        bool flipVertical = (descriptor & (1 << 5)) == 0;

        // Color modes:
        UInt32 numChannels = tgaImage.bitCount / 8;
        switch (numChannels)
        {
        case 3: // BGR
        case 4: // BGRA
        case 5:
            break;
        default:
            return nullptr;
        }

        // GIMP exporter bug
        if (numChannels == 5)
        {
            numChannels = 4;
            tgaImage.bitCount = 32;
        }

        const UInt32 numberOfPixels = tgaImage.width * tgaImage.height;

        // Allocate memory for the image data.
        tgaImage.data.resize(numberOfPixels * numChannels);

        // Read the image data.
        if (flipVertical)
        {
            UInt8* imageData = new UInt8[numberOfPixels * numChannels];
            fileIn.read(reinterpret_cast<Char*>(imageData), numberOfPixels * numChannels, nReadBytes);

            UInt32 stride = numChannels * tgaImage.width;
            UInt8* dst = &tgaImage.data[0];
            UInt8* src = imageData + (tgaImage.height - 1) * stride;

            for (Int32 y = 0; y < tgaImage.height; y++)
            {
                PlatformMemory::Copy(dst, src, stride);
                dst += stride;
                src -= stride;
            }

            delete[] imageData;
        }
        else
        {
            fileIn.read(reinterpret_cast<Char*>(&tgaImage.data[0]), numberOfPixels * numChannels, nReadBytes);
        }

        // Change from BGR to RGB so OpenGL can read the image data.
        for (UInt32 imageIdx = 0; imageIdx < numberOfPixels; imageIdx++)
        {
            const UInt32 index = imageIdx * numChannels;
            const UChar bChannel = tgaImage.data[index];
            const UChar rChannel = tgaImage.data[index + 2u];
            tgaImage.data[index + 0] = rChannel;
            tgaImage.data[index + 2] = bChannel;
        }

        const ramses::ETextureFormat format = (numChannels == 3 ? ramses::ETextureFormat_RGB8 : ramses::ETextureFormat_RGBA8);
        const uint32_t dataSize = tgaImage.width * tgaImage.height * numChannels;
        const uint8_t* dataPtr = &tgaImage.data[0];

        ramses::MipLevelData mipLevelData(dataSize, dataPtr);
        return ramsesClient.createTexture2D(tgaImage.width, tgaImage.height, format, 1, &mipLevelData, true, ramses::ResourceCacheFlag_DoNotCache, name);
    }
}
