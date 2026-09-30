// Game/Unsorted_1098CB50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <new>

class Class_10E676D0
{
public:
    Class_10E676D0();
    void operator delete(void* p);
    static void FUN_1098cb80(void* p);
};

class Class_1098CB90
{
public:
    Class_1098CB90* FUN_1098cb90(int A, int B);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
};

// FUNCTION: 0x1098CB80 ?FUN_1098cb80@Class_10E676D0@@SAXPAX@Z
void Class_10E676D0::FUN_1098cb80(void* p)
{
    new (p) Class_10E676D0;
}

// FUNCTION: 0x1098CB90 ?FUN_1098cb90@Class_1098CB90@@QAEPAV1@HH@Z
Class_1098CB90* Class_1098CB90::FUN_1098cb90(int A, int B)
{
    Unknown00 = B;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = 0;
    Unknown24 = A;
    Unknown28 = -1;
    Unknown2C = 0;
    return this;
}
