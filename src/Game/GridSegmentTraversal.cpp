// Game/GridSegmentTraversal.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <math.h>
#include "Core/Core.h"
#include "Game/Class_10C25EB0.h"

class Class_10C06540;

class Class_10C06940
{
public:
    Class_10C25EB0* FUN_10c06f30(Class_10C25EB0* Out, const FVector& Position);

    int Unknown00;
    int Count;
    int CapacityBytes;
    Class_10C06540** Data;
};

float FUN_10c064c0();

class Class_10C25580
{
public:
    bool FUN_10c25640(FVector* Out, const FVector& Start, const FVector& End, unsigned char Minimum);

    int References;
    Class_10C06940* Provider;
};

// FUNCTION: 0x10C25640 ?FUN_10c25640@Class_10C25580@@QAE_NPAVFVector@@ABV2@1E@Z
bool Class_10C25580::FUN_10c25640(FVector* Out, const FVector& Start, const FVector& End, unsigned char Minimum)
{
    Class_10C25EB0 Cell;
    FVector Position;
    {
        FVector Step = End - Start;
        float Length = sqrt(Step.X * Step.X + Step.Y * Step.Y + Step.Z * Step.Z);
        int Count = (int)(Length / FUN_10c064c0());
        Step.Normalize();
        double Scale = FUN_10c064c0();
        Step.X *= Scale;
        Step.Y *= Scale;
        Step.Z *= Scale;
        Position = Start;
        for (int i = 0; ; ++i)
        {
            if (i >= Count)
                return true;
            Provider->FUN_10c06f30(&Cell, Position);
            if ((unsigned char)Cell.FUN_10c25fb0() <= Minimum)
                break;
            Position += Step;
        }
    }
    *Out = Cell.GetPosition();
    return false;
}
