// Game/Unsorted_10919CB0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e47660[];

struct Struct_1091A610Header
{
    int Unknown00;
};

struct Struct_1091A610
{
    char* Unknown00;
};

class Class_10941C40;

class Class_10919B90
{
public:
    bool FUN_10919d30(Class_10941C40* A, const char* Text, int Length, float* X, float* Y, unsigned long Color,
                      float ScaleX, float ScaleY, unsigned long Flags);
    bool FUN_1091a640(Class_10941C40* A, const Struct_1091A610* Text, float* X, float* Y, unsigned long Color,
                      float ScaleX, float ScaleY, unsigned long Flags);
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int* Obj);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_1091A8F0
{
public:
    void FUN_1091a8f0();

    char Unknown00[8];
    int* Unknown08;
};

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_1091AA10
{
public:
    Class_109081E0 FUN_1091aa10(int A);
};

// FUNCTION: 0x1091A640 ?FUN_1091a640@Class_10919B90@@QAE_NPAVClass_10941C40@@PBUStruct_1091A610@@PAM2KMMK@Z
bool Class_10919B90::FUN_1091a640(Class_10941C40* A, const Struct_1091A610* Text, float* X, float* Y,
                                  unsigned long Color, float ScaleX, float ScaleY, unsigned long Flags)
{
    int Length = !Text->Unknown00 ? 0 : ((Struct_1091A610Header*)Text->Unknown00 - 1)->Unknown00;
    const char* Chars = Text->Unknown00 ? Text->Unknown00 : DAT_10e47660;
    return FUN_10919d30(A, Chars, Length, X, Y, Color, ScaleX, ScaleY, Flags);
}

// FUNCTION: 0x1091A8F0 ?FUN_1091a8f0@Class_1091A8F0@@QAEXXZ
void Class_1091A8F0::FUN_1091a8f0()
{
    if (Unknown08)
    {
        int* Obj = Unknown08 - 1;
        FUN_10905aa0()->Virtual5(Obj);
        Unknown08 = 0;
    }
}

// FUNCTION: 0x1091AA10 ?FUN_1091aa10@Class_1091AA10@@QAE?AVClass_109081E0@@H@Z
Class_109081E0 Class_1091AA10::FUN_1091aa10(int A)
{
    if (A != 0)
        return Class_109081E0("MediumFont16");
    return Class_109081E0("font6");
}
