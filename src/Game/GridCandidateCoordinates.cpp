// Game/GridCandidateCoordinates.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10C06540.h"

// FUNCTION: 0x10C06560 ?FUN_10c06560@Class_10C06540@@QAEXABVFVector@@PAH1@Z
void Class_10C06540::FUN_10c06560(const FVector& Position, int* Row, int* Column)
{
    FVector Origin(Unknown48.Unknown00 - 96.0f, Unknown48.Unknown04 - 96.0f, 0.0f);
    float DeltaY = Position.Y - Origin.Y;
    *Row = (int)((Position.X - Origin.X) * (1.0f / 24.0f));
    *Column = (int)(DeltaY * (1.0f / 24.0f));
    if (*Row < 0)
        *Row = 0;
    else if (*Row > 7)
        *Row = 7;
    if (*Column < 0)
        *Column = 0;
    else if (*Column > 7)
        *Column = 7;
}
