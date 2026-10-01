// Game/Unsorted_1098E5B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

inline void* operator new(unsigned int, void* Ptr)
{
    return Ptr;
}

class Class_10E70A50
{
public:
    Class_10E70A50();

    virtual void FUN_10adb3a0();

    char Unknown04[0x28];
};

class Class_10993EC0 : public Class_10E70A50
{
public:
    Class_10993EC0()
    {
        UnknownB0 = 0;
        UnknownB4 = 0;
        UnknownB8 = 0;
    }

    virtual void FUN_10adb3a0();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

class AMissingArch : public Class_10993EC0
{
public:
    AMissingArch();
};

class AObjSysTest : public Class_10993EC0
{
public:
    AObjSysTest();
};

class AObjSysTestChild : public Class_10993EC0
{
public:
    AObjSysTestChild();
};

// FUNCTION: 0x1098E5B0 ?FUN_1098e5b0@@YAXPAX@Z
void FUN_1098e5b0(void* Memory)
{
    new (Memory) AMissingArch();
}

// FUNCTION: 0x1098E5C0 ?FUN_1098e5c0@@YAXPAX@Z
void FUN_1098e5c0(void* Memory)
{
    new (Memory) AObjSysTest();
}

// FUNCTION: 0x1098E5D0 ?FUN_1098e5d0@@YAXPAX@Z
void FUN_1098e5d0(void* Memory)
{
    new (Memory) AObjSysTestChild();
}
