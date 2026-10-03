// Game/Unsorted_10C223E0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C22AD0
{
    char Unknown00[0x24];
};

class Class_10BAEC80
{
public:
    void FUN_10a211e0(int NewCount);
    void FUN_10c22ad0(const Class_10BAEC80& Other);

    int Count;
    int Unknown04;
    Struct_10C22AD0* Data;
};

struct Struct_10C22BA0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C22A70
{
public:
    void FUN_10c22a70(const Class_10C22A70& Other);

    char Unknown00[0xC];
};

class Class_10C22BA0
{
public:
    void FUN_10c22ba0(const Class_10C22BA0& Other);

    Struct_10C22BA0 Unknown00;
    Class_10C22A70 Unknown0C;
    char Unknown18[0x5A];
};

// FUNCTION: 0x10C22AD0 ?FUN_10c22ad0@Class_10BAEC80@@QAEXABV1@@Z
void Class_10BAEC80::FUN_10c22ad0(const Class_10BAEC80& Other)
{
    FUN_10a211e0(Other.Count);
    for (int i = 0; i < Count; i++)
        Data[i] = Other.Data[i];
}

// FUNCTION: 0x10C22BA0 ?FUN_10c22ba0@Class_10C22BA0@@QAEXABV1@@Z
void Class_10C22BA0::FUN_10c22ba0(const Class_10C22BA0& Other)
{
    Unknown00 = Other.Unknown00;
    Unknown0C.FUN_10c22a70(Other.Unknown0C);
    for (int i = 0; i < 0x5A; i++)
        Unknown18[i] = Other.Unknown18[i];
}
