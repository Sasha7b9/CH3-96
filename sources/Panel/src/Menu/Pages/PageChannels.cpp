#include "PageChannels.h"


static Page pChannels;

Page *PageChannels::self = &pChannels;

static Control *controls[] = { nullptr };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void DrawClosed(int x, int y)
{
//    Rectangle(3, 3).Fill(x + 1, y + 1);

    //TEXT()
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageChannels::Init()
{
    pChannels.Init(controls, DrawClosed);
}
