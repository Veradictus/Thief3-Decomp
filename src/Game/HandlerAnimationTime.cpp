// Game/HandlerAnimationTime.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10B3A460.h"
#include "Game/Class_Field0c_D.h"

Class_10B3A460* GetEntries();

class Class_10B39750
{
public:
    float QueryHandlerValue(int A);
    char Pad00[0xC];
    Class_Field0c_D* m_Handlers[8];
};

// FUNCTION: 0x10B39750 ?QueryHandlerValue@Class_10B39750@@QAEMH@Z
float Class_10B39750::QueryHandlerValue(int A)
{
    int Index = GetEntries()->GetEntry(A)->m_Index;
    return m_Handlers[Index]->FUN_10b47100(A);
}
