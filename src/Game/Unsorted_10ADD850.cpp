// Game/Unsorted_10ADD850.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UBitfieldEnum
{
public:
    UBitfieldEnum();
};

// FUNCTION: 0x10ADD850 ?FUN_10add850@@YAXPAX@Z
void FUN_10add850(void* Memory)
{
    new ((EInternal*)Memory) UBitfieldEnum();
}
