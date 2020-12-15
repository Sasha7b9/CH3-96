#include "defines.h"
#include "Display/Display.h"
#include "SCPI/SCPI.h"
#include "Utils/String.h"


static pCHAR FuncIDN(pCHAR);
static pCHAR FuncReset(pCHAR);
static pCHAR FuncPicture(pCHAR);


const StructSCPI SCPI::head[] =
{
    SCPI_LEAF("*IDN?",   FuncIDN),
    SCPI_LEAF("*RST",    FuncReset),
    SCPI_LEAF(":PICTURE", FuncPicture),
    SCPI_NODE(":INPUT",  SCPI::input),
    SCPI_EMPTY()
};


static pCHAR FuncIDN(pCHAR buffer) //-V2506
{
    SCPI_PROLOG(buffer)

    SCPI::SendAnswer(String("OAO MNIPI, CH3-96/2, Cherem V1.2").c_str());

    SCPI_EPILOG(buffer)
}


static pCHAR FuncPicture(pCHAR buffer) //-V2506
{
    SCPI_PROLOG(buffer);

    Display::SendToSCPI();

    SCPI_EPILOG(buffer);
}


static pCHAR FuncReset(pCHAR buffer) //-V2506
{
    SCPI_PROLOG(buffer)
        
    SCPI_EPILOG(buffer)
}


