// Game/Unsorted_10A4A190_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10D9E5E0_Param;

class Class_10D9B090
{
public:
    void FUN_10d9e5e0(Struct_10D9E5E0_Param* A);
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

// FUNCTION: 0x10A4A9F0 ?FUN_10a4a9f0@@YAXPAVClass_1098E3D0@@@Z
void FUN_10a4a9f0(Class_1098E3D0* P)
{
    P->FUN_10990560(0);
    if (P->UnknownB0)
        FUN_10d9dcb0()->FUN_10d9e5e0(P->UnknownB0);
    int Value = 1;
    P->FUN_1098e3d0(0x80064b, &Value);
}
