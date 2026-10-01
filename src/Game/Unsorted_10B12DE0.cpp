// Game/Unsorted_10B12DE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class Class_10E78470
{
public:
    Class_10E78470();
};

class Class_10E784F8
{
public:
    Class_10E784F8();
};

class Class_10E78580
{
public:
    Class_10E78580();
};

// FUNCTION: 0x10B12DE0 ?FUN_10b12de0@@YAXPAX@Z
void FUN_10b12de0(void* Memory)
{
    new ((EInternal*)Memory) Class_10E78470();
}

// FUNCTION: 0x10B12DF0 ?FUN_10b12df0@@YAXPAX@Z
void FUN_10b12df0(void* Memory)
{
    new ((EInternal*)Memory) Class_10E784F8();
}

// FUNCTION: 0x10B12E00 ?FUN_10b12e00@@YAXPAX@Z
void FUN_10b12e00(void* Memory)
{
    new ((EInternal*)Memory) Class_10E78580();
}
