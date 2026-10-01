// Game/Unsorted_10B375E0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B1D500
{
public:
    void FUN_10b1d500(bool A, bool B);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0xC];
    Class_10B1D500* Unknown0C;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

struct Struct_10B375E0
{
    char Unknown00[4];
    bool Unknown04;
};

class Class_10B375E0
{
public:
    void FUN_10b375e0(int A, Struct_10B375E0* B, int C);
};

// FUNCTION: 0x10B375E0 ?FUN_10b375e0@Class_10B375E0@@QAEXHPAUStruct_10B375E0@@H@Z
void Class_10B375E0::FUN_10b375e0(int A, Struct_10B375E0* B, int C)
{
    bool Flag = true;
    if (B != (Struct_10B375E0*)-1)
        Flag = B->Unknown04;
    DAT_10f3a3d8->Unknown0C->FUN_10b1d500(true, Flag);
}
