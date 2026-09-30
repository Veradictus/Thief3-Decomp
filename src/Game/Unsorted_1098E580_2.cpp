// Game/Unsorted_1098E580_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E70A50
{
public:
    Class_10E70A50();

    void** Unknown00;
    char Unknown04[0x28];
};

class Class_10E53A48 : public Class_10E70A50
{
public:
    Class_10E53A48* FUN_1098dd00();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

inline void* operator new(unsigned int, void* Ptr)
{
    return Ptr;
}

class Class_10E4B7C0
{
public:
    Class_10E4B7C0();
};

// FUNCTION: 0x1098E580 ?FUN_1098e580@@YAXPAVClass_10E53A48@@@Z
void FUN_1098e580(Class_10E53A48* Object)
{
    if (Object)
        Object->FUN_1098dd00();
}

// FUNCTION: 0x1098E5A0 ?FUN_1098e5a0@@YAXPAX@Z
void FUN_1098e5a0(void* Memory)
{
    new (Memory) Class_10E4B7C0();
}
