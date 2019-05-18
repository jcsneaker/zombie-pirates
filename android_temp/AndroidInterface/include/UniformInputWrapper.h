//  -------------------------------------------------------------------------
//  Copyright (C) 2018 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_UNIFORMINPUTWRAPPER_H
#define RAMSES_UNIFORMINPUTWRAPPER_H

#include "ramses-client-api/UniformInput.h"

namespace ramses
{
    class Appearance;
}

class UniformInputWrapper
{
public:
    UniformInputWrapper(const char* inputName, ramses::Appearance& appearance);

    void setInputValueFloat(float x);

private:
    ramses::UniformInput m_input;
    ramses::Appearance& m_appearance;

};

#endif
