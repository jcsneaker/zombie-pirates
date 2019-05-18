//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_WAVE_H
#define RAMSES_WAVE_H

//#include "windows.h"
//#include <mmsystem.h>
#include <iostream>
#include <fstream>
//#include <conio.h>
#include <assert.h>

using namespace ramses;
using namespace std;

namespace ramses_internal
{
    /*class Wave
    {
    public:
        Wave(char * filename)
        {
            HInstance = GetModuleHandle(0);

            ifstream infile(filename, ios::binary);

            assert(infile);

            infile.seekg(0, ios::end);   // get length of file
            std::streamoff length = infile.tellg();
            buffer.resize(static_cast<UInt>(length));    // allocate memory
            infile.seekg(0, ios::beg);   // position to start of file
            infile.read(&buffer[0], length);  // read entire file

            infile.close();
        }

        ~Wave()
        {
            stop();
        }

        void play(bool async = false, bool loop = false)
        {
            uint32_t flags = SND_MEMORY;
            if (async)
            {
                flags |= SND_ASYNC;
            }
            if (loop)
            {
                flags |= SND_LOOP;
            }

            PlaySound(&buffer[0], HInstance, flags);
        }

        void stop()
        {
            //PlaySound(NULL, 0, 0); // STOP ANY PLAYING SOUND
        }

    private:
        std::vector<char> buffer;
        //HINSTANCE HInstance;
    };*/
}

#endif
