// Game/Unsorted_10B06390.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B0F7C0;

struct Info_10B0F7C0
{
    char Unknown00[0x24];
    Struct_10B0F7C0* Unknown24;
    char Unknown28[4];
    int Unknown2C;
};

struct Struct_10B0F7C0
{
    char Unknown00[0xE8];
    Info_10B0F7C0* UnknownE8;
};

extern "C" void* memset(void* Dest, int Value, unsigned int Count);

class Class_10B120F0
{
public:
    Class_10B120F0* FUN_10b120f0();

    int Unknown00;
    int Unknown04[7];
};

void FUN_10b12d20();

void FUN_10b13120();

void FUN_10b13180();

// Parameter setter - stores parameter to field at offset 0x30

class Class_10B138F0 {
public:
    char Unknown00[0x30];
    int Field30;
    void FUN_10b138f0(int param);
};

extern void* GWindowManager[];

// FUNCTION: 0x10B0F7C0 ?FUN_10b0f7c0@@YAHPAUStruct_10B0F7C0@@@Z
int FUN_10b0f7c0(Struct_10B0F7C0* Obj)
{
    Info_10B0F7C0* Info = Obj->UnknownE8;
    if (Info->Unknown2C == 0)
        Info->Unknown2C = Info->Unknown24->UnknownE8->Unknown2C;
    return Info->Unknown2C;
}

// FUNCTION: 0x10B120F0 ?FUN_10b120f0@Class_10B120F0@@QAEPAV1@XZ
Class_10B120F0* Class_10B120F0::FUN_10b120f0()
{
    Unknown00 = 1;
    memset(Unknown04, 0, sizeof(Unknown04));
    return this;
}

// FUNCTION: 0x10B12DD0 ?FUN_10b12dd0@@YAXXZ
void FUN_10b12dd0()
{
    FUN_10b12d20();
}

// FUNCTION: 0x10B131E0 ?FUN_10b131e0@@YAXXZ
void FUN_10b131e0()
{
    FUN_10b13120();
}

// FUNCTION: 0x10B131F0 ?FUN_10b131f0@@YAXXZ
void FUN_10b131f0()
{
    FUN_10b13180();
}

// FUNCTION: 0x10B138F0 ?FUN_10b138f0@Class_10B138F0@@QAEXH@Z
void Class_10B138F0::FUN_10b138f0(int param)
{
    Field30 = param;
}

// FUNCTION: 0x10B154C0 ?FUN_10b154c0@@YAPAXXZ
void* FUN_10b154c0()
{
    return GWindowManager[0];
}

// FUNCTION: 0x10B154D0 ?FUN_10b154d0@@YAPAXXZ
void* FUN_10b154d0()
{
    return (char*)GWindowManager[0] + 0x220;
}
