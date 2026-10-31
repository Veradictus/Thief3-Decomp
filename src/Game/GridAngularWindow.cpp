// Game/GridAngularWindow.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10BAE0C0.h"

static inline unsigned char GridMaximum(unsigned char A, unsigned char B)
{
    return A >= B ? A : B;
}

struct cGridAngleWindow
{
    int Lower;
    int Upper;
    unsigned char Weight;
    int Kind;
};

static inline void AppendWindow(Class_10BAE0C0& Array, const cGridAngleWindow& Window)
{
    int Index = Array.m_Count;
    Array.Resize(Index + 1);
    ((cGridAngleWindow*)Array.m_Data)[Index] = Window;
}

class cGridAngularNode
{
public:
    void FUN_10c22be0(const cGridAngleWindow* Window);
    FVector Position;
    Class_10BAE0C0 Windows;
    unsigned char Samples[90];
};

// FUNCTION: 0x10C22BE0 ?FUN_10c22be0@cGridAngularNode@@QAEXPBUcGridAngleWindow@@@Z
void cGridAngularNode::FUN_10c22be0(const cGridAngleWindow* Window)
{
    float LowerFraction = ((Window->Lower + 65535) % 65535) / 65535.0f;
    int Lower = (int)(LowerFraction * 90.0f);
    float UpperFraction = ((Window->Upper + 65535) % 65535) / 65535.0f;
    int Upper = (int)(UpperFraction * 90.0f);
    unsigned char Weight = Window->Weight;
    if (Lower == Upper)
        return;
    if (Lower < Upper)
    {
        for (int i = Lower + 1; i < Upper; ++i)
            Samples[i] = GridMaximum(Samples[i], Weight);
    }
    else
    {
        for (int i = 0; i < Upper; ++i)
            Samples[i] = GridMaximum(Samples[i], Weight);
        for (int i = Lower + 1; i < 90; ++i)
            Samples[i] = GridMaximum(Samples[i], Weight);
    }
    AppendWindow(Windows, *Window);
}
