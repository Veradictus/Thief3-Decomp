// Game/Unsorted_10B31680.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

class Class_10AC14F0
{
public:
    void FUN_10ac14f0(float A, int B, float C, bool D);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x10];
    Class_10AC14F0* Unknown10;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

// FUNCTION: 0x10B31A70 ?FUN_10b31a70@@YGXPAVClass_1098E330@@@Z
void __stdcall FUN_10b31a70(Class_1098E330* Props)
{
    float First = 20.0f;
    float Second = 30.0f;
    Props->FUN_1098e330(0x100509, (int*)&First);
    Props->FUN_1098e330(0x10084e, (int*)&Second);
    DAT_10f3a3d8->Unknown10->FUN_10ac14f0(First, 0, Second, false);
}

// FUNCTION: 0x10B31AD0 ?FUN_10b31ad0@@YGXPAVClass_1098E330@@@Z
void __stdcall FUN_10b31ad0(Class_1098E330* Props)
{
    float First = 75.0f;
    float Second = 50.0f;
    Props->FUN_1098e330(0x100534, (int*)&First);
    Props->FUN_1098e330(0x10084f, (int*)&Second);
    DAT_10f3a3d8->Unknown10->FUN_10ac14f0(First, 0, Second, true);
}
