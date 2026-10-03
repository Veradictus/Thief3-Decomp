// Game/Unsorted_10A4A190_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10D9FEE0
{
public:
    void FUN_10d9fee0(int A, int B);
};

struct Struct_10D9E5E0_Param : public Class_10D9FEE0
{
};

class Class_10D9B090
{
public:
    void FUN_10d9e490(Struct_10D9E5E0_Param* A);
};

Class_10D9B090* FUN_10d9dcb0();

class Class_1098E3D0
{
public:
    void FUN_10990560(int A);
    void FUN_1098e3d0(int A, void* B);

    char Unknown00[0xB0];
    Struct_10D9E5E0_Param* UnknownB0;
};

// FUNCTION: 0x10A4AA30 ?FUN_10a4aa30@@YAXPAVClass_1098E3D0@@@Z
void FUN_10a4aa30(Class_1098E3D0* P)
{
    P->FUN_10990560(1);
    Struct_10D9E5E0_Param* Body = P->UnknownB0;
    if (Body)
    {
        FUN_10d9dcb0()->FUN_10d9e490(Body);
        Body->FUN_10d9fee0(1, 1);
    }
    int Value = 0;
    P->FUN_1098e3d0(0x80064b, &Value);
}
