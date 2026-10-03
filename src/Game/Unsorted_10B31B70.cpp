// Game/Unsorted_10B31B70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Options
{
public:
    int Get(int Index);
};

Options* FUN_10929550();

class Class_1098E330
{
public:
    int FUN_1098e330(int Id, int* Out);
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

class Class_10B32160
{
public:
    void FUN_10b31ad0(Class_1098E330* Props);
    void FUN_10b32160(Class_1098E330* Props);
};

// FUNCTION: 0x10B32160 ?FUN_10b32160@Class_10B32160@@QAEXPAVClass_1098E330@@@Z
void Class_10B32160::FUN_10b32160(Class_1098E330* Props)
{
    if (!FUN_10929550()->Get(10))
    {
        FUN_10b31ad0(Props);
        return;
    }
    float First = 75.0f;
    int Second = 0;
    float Third = 50.0f;
    Props->FUN_1098e330(0x100534, (int*)&First);
    Props->FUN_1098e330(0x10050d, &Second);
    Props->FUN_1098e330(0x10050c, (int*)&Third);
    DAT_10f3a3d8->Unknown10->FUN_10ac14f0(First, Second, Third, true);
}
