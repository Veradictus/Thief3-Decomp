// Game/Unsorted_10B0E9C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUNCTION: 0x10B0F7C0 ?FUN_10b0f7c0@@YAHPAUStruct_10B0F7C0@@@Z
int FUN_10b0f7c0(Struct_10B0F7C0* Obj)
{
    Info_10B0F7C0* Info = Obj->UnknownE8;
    if (Info->Unknown2C == 0)
        Info->Unknown2C = Info->Unknown24->UnknownE8->Unknown2C;
    return Info->Unknown2C;
}
