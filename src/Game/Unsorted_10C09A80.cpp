// Game/Unsorted_10C09A80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    int FUN_1098e330(int Id, int* Out);
};

struct Struct_10C099A0
{
    int Unknown00;
    int Unknown04;
    char Unknown08[0x18];
};

class Class_10C099A0
{
public:
    bool FUN_10c09c30(int A, int B);
    bool FUN_10c09f10(int Key, int B);

    // The value of the first entry whose key is Key, else 0.
    int FindValue(int Key)
    {
        for (int i = 0; i < Unknown04; i++)
        {
            Struct_10C099A0* Item = &Unknown0C[i];
            if (Item->Unknown00 == Key)
                return Item->Unknown04;
        }
        return 0;
    }

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Struct_10C099A0* Unknown0C;
};

// FUNCTION: 0x10C09BF0 ?FUN_10c09bf0@@YG_NPAVClass_1098E330@@PAH@Z
bool __stdcall FUN_10c09bf0(Class_1098E330* Obj, int* Other)
{
    int Value = 0;
    if (Obj->FUN_1098e330(0x800182, &Value) && Value)
        return true;
    bool Positive = *Other > 0;
    return Positive;
}

// FUNCTION: 0x10C09F10 ?FUN_10c09f10@Class_10C099A0@@QAE_NHH@Z
bool Class_10C099A0::FUN_10c09f10(int Key, int B)
{
    int Value = FindValue(Key);
    if (Value)
        return FUN_10c09c30(Value, B);
    return false;
}
