#include "defines.h"
#include "Display/Display.h"
#include "Display/Colors.h"
#include "Display/Primitives.h"

#pragma warning(push, 0)
#undef CRC
#include <wx/wx.h>
#pragma warning(pop)


using namespace Primitives;


extern wxMemoryDC memDC;

static Color current = Color::BACK;



void Color::SetAsCurrent() const
{
    uint val = Value();
    uint8 b = (uint8)val;
    uint8 g = (uint8)(val >> 8);
    uint8 r = (uint8)(val >> 16);

    wxColour colorDraw = wxColour(r, g, b);

    memDC.SetPen(wxPen(colorDraw));
}


Color Color::GetCurrent()
{
    return current;
}
