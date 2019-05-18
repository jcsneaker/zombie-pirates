#include "IntroText.h"
#include "PlatformAbstraction/PlatformThread.h"
#include "PlatformAbstraction/PlatformTime.h"
#include "ramses-renderer-api/IRendererEventHandler.h"


namespace ramses_internal
{
    struct AutoPositionText
    {
        AutoPositionText(float x, float y)
            : current(x, y)
        {
        }

        Pos2D operator++(int)
        {
            Pos2D pos = current;
            current.second += 40;
            return pos;
        }

        Pos2D current;
    };

    struct CaptureAnswer : public IKeyListener
    {
        CaptureAnswer()
            : enterPressed(false)
        {
        }

        virtual void keyEvent(ramses::displayId_t, ramses::EKeyEvent keyEvent, uint32_t, ramses::EKeyCode keyCode) override
        {
            if (keyEvent == EKeyEvent_Released)
            {
                if (keyCode >= EKeyCode_A && keyCode <= EKeyCode_Z)
                {
                    const Char asciiCode = static_cast<Char>('a' + (keyCode - EKeyCode_A));
                    answer.append(String(1, asciiCode));
                }
                else if(keyCode == EKeyCode_Backspace && answer.getLength() > 0)
                {
                    answer = answer.substr(0, answer.getLength() - 1);
                }
                else if (keyCode == EKeyCode_Return)
                {
                    enterPressed = true;
                }
            }
        }

        String answer;
        Bool enterPressed;
    };

    IntroText::IntroText(GameEngine& engine)
        : m_engine(engine)
    {
    }

    void IntroText::goGoPowerRangers()
    {
        /*uint32_t x = 0;
        TextCreator textCreator(m_engine);

        AutoPositionText pos(30, 40);
        textCreator.spell(pos++, "There was a time, long forgotten, when pirates swept the seas, claimed new lands and salvaged ", 30);
        textCreator.spell(pos++, "what they wouldn't keep.", 3000);
        textCreator.spell(pos++, "Legends spread about a ghostly ship, a shadow so inhuman it melt the flesh and shed the skin of man.", 3000);
        textCreator.spell(pos++, "The crew, a crowd of fierce pirates, they called themselves the Human Shadows.", 3000);
        textCreator.spell(pos++, "And as shadows they overwhelmed unsuspecting ships, pillaged villages and feasted on the souls of men.", 3000);
        pos++;
        textCreator.spell(pos++, "Two of the bloodyless pirates, Johnny Bonecrusher and Birgit Bring-it-on, woke up one not-so-sunny", 30);
        Pos2D savePosition = pos.current;
        pos++;
        textCreator.spell(savePosition, "day and realized they turned 30", 2000, x);
        savePosition.first += x;
        textCreator.spell(savePosition, "00 years of age*.", 1500);

        TextNode& theyAreZombies = textCreator.spell(Pos2D(Pos2D::s_WindowWidth - 700, Pos2D::s_WindowHeight - 50), "* You guessed right, they are zombies.", 4000);
        textCreator.setTextContent(theyAreZombies, "");

        textCreator.spell(pos++, "So they decided to celebrate doing the one thing they were born to do*:", 1500);

        TextNode& theyDoCPlusPlus = textCreator.spell(Pos2D(Pos2D::s_WindowWidth - 500, Pos2D::s_WindowHeight - 50), "* Except coding C**, that is.", 4000);
        textCreator.setTextContent(theyDoCPlusPlus, "");

        textCreator.spell(pos++, "Exercise some good old ultra violence!", 5000);

        pos++;
        pos++;
        pos++;
        pos++;
        pos++;

        AutoPositionText tmpPos = pos;
        TextNode& j0 = textCreator.spell(pos++, "Pirate 1", 500);
        TextNode& j1 = textCreator.spell(pos++, "    Johnny Bonecrusher", 500);
        TextNode& j2 = textCreator.spell(pos++, "    Steer: W/D     Fire: [Spacebar]", 500);
        pos++;

        TextNode& j3 = textCreator.spell(pos++, "Identity question:", 500);
        TextNode& j4 = textCreator.spell(pos.current, "    What kind of babies can be observed in art exhibitions in Munich?  ", 500, x);
        Pos2D answerPos = pos.current;
        answerPos.first += x;
        getAnswer(textCreator, answerPos, "naked", "        babies.");

        textCreator.setTextContent(j0, "");
        textCreator.setTextContent(j1, "");
        textCreator.setTextContent(j2, "");
        textCreator.setTextContent(j3, "");
        textCreator.setTextContent(j4, "");

        pos = tmpPos;
        TextNode& b0 = textCreator.spell(pos++, "Pirate 2", 500);
        TextNode& b1 = textCreator.spell(pos++, "    Birgit Bring-it-on", 500);
        TextNode& b2 = textCreator.spell(pos++, "    Steer: ArrowUp/ArrowDown     Fire: [Enter]", 500);
        pos++;

        TextNode& b3 = textCreator.spell(pos++, "Identity question:", 500);
        TextNode& b4 = textCreator.spell(pos.current, "    If you had to choose what kind of mistress to be, what would you choose?  ", 500, x);
        answerPos = pos.current;
        answerPos.first += x;
        getAnswer(textCreator, answerPos, "scrum", "        mistress.");

        textCreator.setTextContent(b0, "");
        textCreator.setTextContent(b1, "");
        textCreator.setTextContent(b2, "");
        textCreator.setTextContent(b3, "");
        textCreator.setTextContent(b4, "");

        PlatformThread::Sleep(1500);

        m_engine.fadeOut(6000);*/
    }

    void IntroText::getAnswer(TextCreator& /*textCreator*/, Pos2D /*position*/, String /*answer*/, String /*answerContext*/)
    {
        /*answer.toLowerCase();

        const UInt64 startTime = PlatformTime::GetMillisecondsAbsolute();

        TextNode& contextText = textCreator.addText(position);
        textCreator.setTextContent(contextText, ("\"" + answerContext + "\"").c_str());
        TextNode& text = textCreator.addText(position);

        CaptureAnswer captureAnswer;
        m_engine.setKeyListener(captureAnswer);
        Bool correct = false;
        while (!correct)
        {
            String underscore;
            if (((PlatformTime::GetMillisecondsAbsolute() - startTime) / 1000) % 2 == 0)
            {
                underscore = "_";
            }
            textCreator.setTextContent(text, (" " + captureAnswer.answer + underscore).c_str());

            m_engine.getCurrentScene().flush();

            m_engine.doOneRendererLoop();

            if (captureAnswer.enterPressed)
            {
                if (answer == captureAnswer.answer)
                {
                    correct = true;
                }
                else
                {
                    captureAnswer.enterPressed = false;
                    captureAnswer.answer = "";
                }
            }
        }
        m_engine.unsetKeyListener();

        textCreator.setTextContent(text, "");
        textCreator.setTextContent(contextText, "");*/
    }

}
