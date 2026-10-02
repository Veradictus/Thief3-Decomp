// Game/Unsorted_10C66910.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <string>

unsigned int* __stdcall FUN_10c66910(unsigned int* Dest, unsigned int Count, const unsigned int* Value);

class Class_10C66DE0
{
public:
    ~Class_10C66DE0();

    std::string Unknown00;
    std::string Unknown1C;
};

// FUNCTION: 0x10C66910 ?FUN_10c66910@@YGPAIPAIIPBI@Z
unsigned int* __stdcall FUN_10c66910(unsigned int* Dest, unsigned int Count, const unsigned int* Value)
{
    unsigned int* P = Dest;
    for (unsigned int I = Count; 0 < I; I--)
    {
        *P = *Value;
        P++;
    }
    return Dest + Count;
}

// FUNCTION: 0x10C66DE0 ??1Class_10C66DE0@@QAE@XZ
Class_10C66DE0::~Class_10C66DE0()
{
}
