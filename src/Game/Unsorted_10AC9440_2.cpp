// Game/Unsorted_10AC9440_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

struct Struct_10AA3520
{
    char Unknown00[0x8];
    Class_1098E330* Unknown08;
    char Unknown0C[0x4];
    Class_10AC14F0* Unknown10;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10AC98B0
{
public:
    void FUN_10ac9570();
    void FUN_10ac9840();

    char Unknown00[0x4];
    bool Unknown04;
};

// FUNCTION: 0x10AC9840 ?FUN_10ac9840@Class_10AC98B0@@QAEXXZ
void Class_10AC98B0::FUN_10ac9840()
{
    Class_10AC14F0* Camera = DAT_10f35dec->Unknown10;
    float First = 75.0f;
    float Second = 60.0f;
    DAT_10f35dec->Unknown08->FUN_1098e330(0x100534, (int*)&First);
    DAT_10f35dec->Unknown08->FUN_1098e330(0x100777, (int*)&Second);
    Camera->FUN_10ac14f0(First, 0, Second, true);
    FUN_10ac9570();
}
