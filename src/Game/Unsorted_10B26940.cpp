// Game/Unsorted_10B26940.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10F0328C
{
    float Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

extern Struct_10F0328C DAT_10f0328c[];

extern float DAT_10eafbdc;

class Class_10B27220
{
public:
    void FUN_10b27220(int Index);
    void FUN_10b270d0();

    char Unknown00[0x38];
    bool Unknown38;
};

extern void* DAT_10e7aae8[];

class Class_10E7AAE8
{
public:
    Class_10E7AAE8() : Unknown00(DAT_10e7aae8), Unknown08(0), Unknown0C(0), Unknown10(0) {}
    ~Class_10E7AAE8();

    void* Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

class Class_10B26D00
{
public:
    bool FUN_10b26d00(int A, int B, int C);

    char Unknown00[8];
    char* Unknown08;
    char Unknown0C[0x24];
    int Unknown30;
};

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    char* Unknown00;
};

class Class_10B27090
{
public:
    void FUN_10b26e00();
    void FUN_10b27090(int Index, const Class_109081E0& Name, int Value);

    char Unknown00[8];
    bool* Unknown08;
    char Unknown0C[8];
    Class_109081E0* Unknown14;
    char Unknown18[8];
    int* Unknown20;
};

// FUNCTION: 0x10B26CB0 ?FUN_10b26cb0@@YAPAVClass_10E7AAE8@@XZ
Class_10E7AAE8* FUN_10b26cb0()
{
    static Class_10E7AAE8 Instance;
    return &Instance;
}

// FUNCTION: 0x10B26D00 ?FUN_10b26d00@Class_10B26D00@@QAE_NHHH@Z
bool Class_10B26D00::FUN_10b26d00(int A, int B, int C)
{
    if (Unknown30)
    {
        for (int i = 0; i < 4; i++)
        {
            if (Unknown08[i])
                break;
        }
        return true;
    }
    return false;
}

// FUNCTION: 0x10B27090 ?FUN_10b27090@Class_10B27090@@QAEXHABVClass_109081E0@@H@Z
void Class_10B27090::FUN_10b27090(int Index, const Class_109081E0& Name, int Value)
{
    Unknown08[Index] = true;
    Unknown14[Index] = Name;
    Unknown20[Index] = Value;
    FUN_10b26e00();
}

// FUNCTION: 0x10B27220 ?FUN_10b27220@Class_10B27220@@QAEXH@Z
void Class_10B27220::FUN_10b27220(int Index)
{
    if (DAT_10f0328c[Index].Unknown00 > DAT_10eafbdc)
        Unknown38 = true;
    else
        FUN_10b270d0();
}
