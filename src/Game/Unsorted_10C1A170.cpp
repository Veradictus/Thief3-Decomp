// Game/Unsorted_10C1A170.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e98ce0[];

class Class_10E98CE0
{
public:
    Class_10E98CE0(int p1, int p2);

    void* VTable;
    int Unknown04;
    int Unknown08;
};

extern void* DAT_10e98ce4[];

class Class_10E98CE4 {
public:
    Class_10E98CE4* FUN_10c1a420(int p1);

    void* Unknown00;
    int Unknown04;
};

extern void* DAT_10e98ce8[];

class Class_10E98CE8
{
public:
    Class_10E98CE8(int p1, int p2);

    void* VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10C1A560 {
public:
    Class_10C1A560* FUN_10c1a560();

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10C1A3D0 ??0Class_10E98CE0@@QAE@HH@Z
Class_10E98CE0::Class_10E98CE0(int p1, int p2)
{
    VTable = DAT_10e98ce0;
    Unknown04 = p1;
    Unknown08 = p2;
}

// FUNCTION: 0x10C1A420 ?FUN_10c1a420@Class_10E98CE4@@QAEPAV1@H@Z
Class_10E98CE4* Class_10E98CE4::FUN_10c1a420(int p1)
{
    Unknown00 = DAT_10e98ce4;
    Unknown04 = p1;
    return this;
}

// FUNCTION: 0x10C1A540 ??0Class_10E98CE8@@QAE@HH@Z
Class_10E98CE8::Class_10E98CE8(int p1, int p2)
{
    VTable = DAT_10e98ce8;
    Unknown04 = p1;
    Unknown08 = p2;
}

// FUNCTION: 0x10C1A560 ?FUN_10c1a560@Class_10C1A560@@QAEPAV1@XZ
Class_10C1A560* Class_10C1A560::FUN_10c1a560()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
    return this;
}
