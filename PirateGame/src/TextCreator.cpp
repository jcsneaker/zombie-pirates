//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  All rights reserved.
//  -------------------------------------------------------------------------
//  This document contains proprietary information belonging to BMW Car IT.
//  Passing on and copying of this document, use and communication of its
//  contents is not permitted without prior written authorization.
//  -------------------------------------------------------------------------

#include "TextCreator.h"
#include "PlatformAbstraction/PlatformThread.h"
#include "GameEngine.h"
#include "RendererLib/WindowedRenderer.h"
#include "ramses-hmi-utils.h"

namespace ramses_internal
{

    TextCreator::TextCreator(GameEngine& engine)
        : m_engine(engine)
        //, m_effect(engine.TextEffect)
        //, m_textAppearance(*engine.getCurrentScene().createAppearance(m_effect, "text appearance"))
        //, m_styleConfig(const_cast<TextFont&>(engine.Font), 32)
        //, m_style(m_engine.getCurrentScene().createTextStyle(m_styleConfig))
    {
        //UniformInput color;
        //m_effect.findUniformInput("u_color", color);
        //m_textAppearance.setInputValueVector4f(color, 0.0f, 0.35f, 1.0f, 1.0f);
    }

    /*TextNode& TextCreator::addText(Pos2D pos)
    {
        StringView stringView("text");
        ramses::text::String* string = m_engine.getCurrentScene().createTextString(stringView);
        TextNode* textNode = m_engine.getCurrentScene().createTextNode(*string, *m_style);
        textNode->setAppearance(m_textAppearance);

        TranslateNode* textOffset = m_engine.getCurrentScene().createTranslateNode();
        textOffset->setTranslation(pos.x(), Pos2D::s_WindowHeight - pos.y(), 0.0f);
        textNode->setParent(*textOffset);

        m_engine.getCurrentRenderGroup().addTextNode(*textNode);

        return *textNode;
    }

    void TextCreator::setTextContent(TextNode& text, const char* content)
    {
        ramses::text::String& oldString = text.getString();
        ramses::text::String* newString = m_engine.getCurrentScene().createTextString(ramses::text::StringView(content));
        text.setString(*newString);
        m_engine.getCurrentScene().destroy(oldString);
    }

    TextNode& TextCreator::spell(Pos2D pos, const ramses_internal::String& str, uint32_t sleepTime)
    {
        TextNode& text = addText(pos);

        for (uint32_t i = 0; i < str.getLength(); ++i)
        {
            setTextContent(text, str.substr(0, i + 1).c_str());
            m_engine.getCurrentScene().flush();
            m_engine.doOneRendererLoop();
            PlatformThread::Sleep(50);
        }

        PlatformThread::Sleep(sleepTime);

        return text;
    }

    ramses::text::TextNode& TextCreator::spell(Pos2D pos, const ramses_internal::String& str, uint32_t sleepTime, uint32_t& offsetForFurtherStrings)
    {
        ramses::StringLayoutInfo layout = RamsesHMIUtils::GetFittingCharacterInfo(text::StringView(str.c_str()), *m_style, 10000);
        offsetForFurtherStrings = layout.advanceOfFittingSubstring;

        return spell(pos, str, sleepTime);
    }*/

}
