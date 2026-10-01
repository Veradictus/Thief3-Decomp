// Game/Unsorted_109A1720.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class Class_10e56bc0
{
public:
    Class_10e56bc0();
};

class Class_109a0310
{
public:
    void FUN_109a0310();
};

// FUNCTION: 0x109A1720 ?FUN_109a1720@@YAXPAX@Z
void FUN_109a1720(void* Memory)
{
    new ((EInternal*)Memory) Class_10e56bc0();
}

// FUNCTION: 0x109A1740 ?FUN_109a1740@@YAXPAVClass_109a0310@@@Z
void FUN_109a1740(Class_109a0310* p1)
{
    if (p1)
        p1->FUN_109a0310();
}
