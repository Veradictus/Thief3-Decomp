// Game/Unsorted_10BAEA60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" int __cdecl sprintf(char* Out, const char* Format, ...);

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

struct Struct_10BAEAB0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

extern const char DAT_10e8d938[];

struct Struct_10BAEA60
{
    unsigned char Unknown00;
    unsigned char Unknown01;
    unsigned char Unknown02;
};

extern const char DAT_10e8d92c[];

// FUNCTION: 0x10BAEA60 ?FUN_10baea60@@YA?AVClass_109081E0@@PBUStruct_10BAEA60@@@Z
Class_109081E0 FUN_10baea60(const Struct_10BAEA60* Color)
{
    char Buffer[0x64];
    sprintf(Buffer, DAT_10e8d92c, Color->Unknown02, Color->Unknown01, Color->Unknown00);
    return Class_109081E0(Buffer);
}

// FUNCTION: 0x10BAEAB0 ?FUN_10baeab0@@YA?AVClass_109081E0@@PBUStruct_10BAEAB0@@@Z
Class_109081E0 FUN_10baeab0(const Struct_10BAEAB0* Vec)
{
    char Buffer[0x64];
    sprintf(Buffer, DAT_10e8d938, Vec->Unknown00, Vec->Unknown04, Vec->Unknown08);
    return Class_109081E0(Buffer);
}
