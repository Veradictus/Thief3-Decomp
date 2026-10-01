// Game/Unsorted_10B405B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e7f770[];

extern void* DAT_10e7edb8[];

class Class_10E67BD8
{
public:
    Class_10E67BD8();

    void* vtable;
};

class Class_10E7F770 : public Class_10E67BD8
{
public:
    char Unknown04[0x114];
    void** Unknown118;

    Class_10E7F770* FUN_10b405b0();
};

extern void* DAT_10e7f930[];

extern void* DAT_10e5b2b8[];

class Class_10E7F930 : public Class_10E67BD8
{
public:
    char Unknown04[0x114];
    void** Unknown118;

    Class_10E7F930* FUN_10b405d0();
};

// FUNCTION: 0x10B405B0 ?FUN_10b405b0@Class_10E7F770@@QAEPAV1@XZ
Class_10E7F770* Class_10E7F770::FUN_10b405b0()
{
    this->Class_10E67BD8::Class_10E67BD8();
    vtable = DAT_10e7f770;
    Unknown118 = DAT_10e7edb8;
    return this;
}

// FUNCTION: 0x10B405D0 ?FUN_10b405d0@Class_10E7F930@@QAEPAV1@XZ
Class_10E7F930* Class_10E7F930::FUN_10b405d0()
{
    this->Class_10E67BD8::Class_10E67BD8();
    vtable = DAT_10e7f930;
    Unknown118 = DAT_10e5b2b8;
    return this;
}
