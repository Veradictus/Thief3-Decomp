// Game/Unsorted_10B87540.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B88840
{
    int Unknown00;
    int Unknown04;
    bool Unknown08;
};

class Class_10B88840
{
public:
    Class_10B88840* FUN_10b88840();

    Struct_10B88840 Unknown00[4];
    bool Unknown30;
};

struct Class_10b888d0_Entry
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10b888d0
{
public:
    Class_10b888d0_Entry Entries[1];
    int FUN_10b888d0(int index);
};

class Class_Unknown00
{
public:
    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
};

class Class_10B888E0
{
public:
    void FUN_10b888e0(int p1, int* p2);

    Class_Unknown00 Unknown00[1];
};

extern void* DAT_10e89540[];

class Class_10E89AA0
{
public:
    Class_10E89AA0(int A, int B, int C);

    void** Unknown00;
};

class Class_10E89540 : public Class_10E89AA0
{
public:
    Class_10E89540* FUN_10b8b5b0(int A, int B);

    char Unknown04[0x14];
    bool Unknown18;
    char Unknown19[0x13];
    int Unknown2C;
};

class Class_10B8D520;

// The member at +0x4C: two arrays, constructed at 0x10DA91B0 and destroyed at 0x10DA91F0.
class Class_10DA91B0
{
public:
    Class_10DA91B0();
    ~Class_10DA91B0();

    void FUN_10da91d0();

    char Unknown00[0x18];
};

// Three values its inline constructor clears.
struct Struct_10B87560
{
    Struct_10B87560() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

// The base (vtable 0x10E89384); its destructor's out-of-line copy is 0x10B87530.
class Class_10E89384
{
public:
    Class_10E89384(int A) : Unknown04(A), Unknown08(0) {}
    virtual ~Class_10E89384() {}

    int Unknown04;
    int Unknown08;
};

class Class_10E893B0 : public Class_10E89384
{
public:
    Class_10E893B0();
    virtual ~Class_10E893B0();

    int Unknown0C;
    Struct_10B87560 Unknown10;
    Struct_10B87560 Unknown1C;
    Struct_10B87560 Unknown28;
    Struct_10B87560 Unknown34;
    int Unknown40;
    int Unknown44;
    int Unknown48;
    Class_10DA91B0 Unknown4C;
    Struct_10B87560 Unknown64;
    int Unknown70;
    int Unknown74;
    Class_10B8D520* Unknown78;
};

// FUNCTION: 0x10B87560 ??0Class_10E893B0@@QAE@XZ
Class_10E893B0::Class_10E893B0()
    : Class_10E89384(1), Unknown0C(0), Unknown40(0), Unknown44(0), Unknown48(0), Unknown70(0), Unknown74(0),
      Unknown78(0)
{
    Unknown4C.FUN_10da91d0();
}

// FUNCTION: 0x10B87EE0 ??_GClass_10E893B0@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B87560's definition in this unit.

// FUNCTION: 0x10B88840 ?FUN_10b88840@Class_10B88840@@QAEPAV1@XZ
Class_10B88840* Class_10B88840::FUN_10b88840()
{
    Unknown30 = false;
    for (int i = 0; i < 4; i++)
    {
        Unknown00[i].Unknown00 = 0;
        Unknown00[i].Unknown04 = 0;
        Unknown00[i].Unknown08 = false;
    }
    return this;
}

// FUNCTION: 0x10B888D0 ?FUN_10b888d0@Class_10b888d0@@QAEHH@Z
int Class_10b888d0::FUN_10b888d0(int index)
{
    return Entries[index].Unknown00;
}

// FUNCTION: 0x10B888E0 ?FUN_10b888e0@Class_10B888E0@@QAEXHPAH@Z
void Class_10B888E0::FUN_10b888e0(int p1, int* p2)
{
    *p2 = Unknown00[p1].Unknown04;
}

// FUNCTION: 0x10B8B5B0 ?FUN_10b8b5b0@Class_10E89540@@QAEPAV1@HH@Z
Class_10E89540* Class_10E89540::FUN_10b8b5b0(int A, int B)
{
    this->Class_10E89AA0::Class_10E89AA0(1, A, B);
    Unknown00 = DAT_10e89540;
    Unknown2C = 0;
    Unknown18 = true;
    return this;
}
