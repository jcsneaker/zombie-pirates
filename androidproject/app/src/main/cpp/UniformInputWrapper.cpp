//  -------------------------------------------------------------------------
//  Copyright (C) 2018 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "UniformInputWrapper.h"

#include "ramses-client-api/Appearance.h"
#include "ramses-client-api/Effect.h"

UniformInputWrapper::UniformInputWrapper(const char* inputName, ramses::Appearance& appearance)
    :m_appearance(appearance)
{
    m_appearance.getEffect().findUniformInput(inputName, m_input);
}

void UniformInputWrapper::setInputValueFloat(float x)
{
    m_appearance.setInputValueFloat(m_input, x);
}



