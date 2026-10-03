// Game/Unsorted_10B9F280.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive;

class Class_10C04AA0
{
public:
    void FUN_10c04aa0(FArchive& Ar);
};

class Class_10B9F450
{
public:
    void FUN_10b9f450(FArchive& Ar);

    char Unknown00[0xC];
    int Unknown0C;
    char Unknown10[4];
    Class_10C04AA0** Unknown14;
};

class Class_10B9F2F0
{
public:
    void FUN_10b9f2f0(FArchive& Ar);
};

class Class_10B9F480
{
public:
    void FUN_10b9f480(FArchive& Ar);

    char Unknown00[0x18];
    int Unknown18;
    char Unknown1C[4];
    Class_10B9F2F0** Unknown20;
};

class Object_10B9F420
{
public:
    virtual ~Object_10B9F420();
};

struct Struct_10B9F420
{
    int Unknown00;
    int Unknown04;
    Object_10B9F420** Unknown08;
};

// FUNCTION: 0x10B9F420 ?FUN_10b9f420@@YAXPAUStruct_10B9F420@@@Z
void FUN_10b9f420(Struct_10B9F420* List)
{
    for (int i = 0; i < List->Unknown00; i++)
        delete List->Unknown08[i];
    List->Unknown00 = 0;
}

// FUNCTION: 0x10B9F450 ?FUN_10b9f450@Class_10B9F450@@QAEXAAVFArchive@@@Z
void Class_10B9F450::FUN_10b9f450(FArchive& Ar)
{
    for (int i = 0; i < Unknown0C; i++)
        Unknown14[i]->FUN_10c04aa0(Ar);
}

// FUNCTION: 0x10B9F480 ?FUN_10b9f480@Class_10B9F480@@QAEXAAVFArchive@@@Z
void Class_10B9F480::FUN_10b9f480(FArchive& Ar)
{
    for (int i = 0; i < Unknown18; i++)
        Unknown20[i]->FUN_10b9f2f0(Ar);
}
