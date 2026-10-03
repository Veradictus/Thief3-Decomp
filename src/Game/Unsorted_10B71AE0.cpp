// Game/Unsorted_10B71AE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Struct_10B73810
{
public:
    virtual void Virtual0();

    char Unknown04[0x1EC];
    int Unknown1F0;
};

class Class_10B735C0
{
public:
    void FUN_10b735c0(int A);
};

class Class_10B73810
{
public:
    void FUN_10b737b0();

    char Unknown00[0x188];
    Struct_10B73810* Unknown188;
    char Unknown18C[4];
    int Unknown190;
    char Unknown194[4];
    Class_10B735C0** Unknown198;
    char Unknown19C[8];
    int* Unknown1A4;
};

// FUNCTION: 0x10B737B0 ?FUN_10b737b0@Class_10B73810@@QAEXXZ
void Class_10B73810::FUN_10b737b0()
{
    Struct_10B73810* Obj = Unknown188;
    int Base = (int)Obj;
    if (Obj)
        Base = Obj->Unknown1F0;
    for (int i = 0; i < Unknown190; i++)
        Unknown198[i]->FUN_10b735c0(Unknown1A4[Base + i]);
}
