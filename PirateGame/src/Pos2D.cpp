#include "Pos2D.h"
#include "PlatformAbstraction/PlatformTypes.h"

namespace ramses_internal
{

    void Pos2D::SetWindowSize(int32_t width, int32_t height)
    {
        s_WindowWidth = (Float)width;
        s_WindowHeight = (Float)height;
    }

    float Pos2D::s_WindowWidth = 200;
    float Pos2D::s_WindowHeight = 200;

}
