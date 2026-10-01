// Game/Unsorted_10B12120_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AT3PlayerController
{
public:
    AT3PlayerController();
};

class Class_10E55E78
{
public:
    Class_10E55E78();

    virtual void Virtual0();
};

class Class_10E78470 : public Class_10E55E78
{
public:
    Class_10E78470();
};

class Class_10E78580 : public Class_10E55E78
{
public:
    Class_10E78580();
};

// FUNCTION: 0x10B129C0 ?FUN_10b129c0@@YAXPAX@Z
void FUN_10b129c0(void* Memory)
{
    new ((EInternal*)Memory) AT3PlayerController();
}

// FUNCTION: 0x10B129D0 ??0Class_10E78470@@QAE@XZ
Class_10E78470::Class_10E78470()
{
}

// FUNCTION: 0x10B12B30 ??0Class_10E78580@@QAE@XZ
Class_10E78580::Class_10E78580()
{
}
