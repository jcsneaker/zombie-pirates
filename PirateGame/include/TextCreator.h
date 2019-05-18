//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#ifndef RAMSES_TEXTCREATOR_H
#define RAMSES_TEXTCREATOR_H

#include <ramses-client.h>
#include "Collections/Vector.h"
#include "Pos2D.h"
#include "GameEngine.h"

namespace ramses_internal
{
    class TextCreator
    {
    public:
        TextCreator(GameEngine& engine);

        /*ramses::TextNode& addText(Pos2D pos);
        void setTextContent(TextNode& text, const char* content);

        TextNode& spell(Pos2D pos, const ramses_internal::String& str, uint32_t sleepTime);
        TextNode& spell(Pos2D pos, const ramses_internal::String& str, uint32_t sleepTime, uint32_t& offsetForFurtherStrings);*/
    private:
        GameEngine& m_engine;
        //const ramses::Effect& m_effect;
        //ramses::Appearance& m_textAppearance;
        //
        //TextStyleConfig m_styleConfig;
        //TextStyle* m_style;
    };
}

#endif
