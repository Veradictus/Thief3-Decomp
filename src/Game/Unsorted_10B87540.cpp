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
