// Game/Unsorted_10933670.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

struct Struct_10932ED0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10E49EB8
{
public:
    virtual void Virtual0();
    virtual int FUN_10933910(int A, int B, Struct_10932ED0* C, int D);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    Struct_10932ED0 Unknown10;
    char Unknown1C[0x18];
    int Unknown34;
    float Unknown38;
};

class Object_10933670_Resource
{
public:
    virtual int __stdcall Virtual0();
    virtual int __stdcall Virtual1();
    virtual int __stdcall Virtual2();
};

struct Struct_10933670_Item
{
    char Unknown00[0x14];
    Object_10933670_Resource* Unknown14;
};

class Class_10E49E50
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10933670();

    char Unknown04[0x10];
    int Unknown14;
    char Unknown18[8];
    std::vector<Struct_10933670_Item*> Unknown20;
};

// FUNCTION: 0x10933670 ?FUN_10933670@Class_10E49E50@@UAEXXZ
void Class_10E49E50::FUN_10933670()
{
    if (Unknown14 & 2)
        return;
    for (std::vector<Struct_10933670_Item*>::iterator It = Unknown20.begin(); It != Unknown20.end(); ++It)
    {
        Struct_10933670_Item* Item = *It;
        if (Item->Unknown14)
        {
            Item->Unknown14->Virtual2();
            Item->Unknown14 = 0;
        }
    }
}

// FUNCTION: 0x10933910 ?FUN_10933910@Class_10E49EB8@@UAEHHHPAUStruct_10932ED0@@H@Z
int Class_10E49EB8::FUN_10933910(int A, int B, Struct_10932ED0* C, int D)
{
    Unknown04 = A;
    Unknown08 = B;
    Unknown10 = *C;
    Unknown38 = Unknown10.Unknown00;
    Unknown0C = D;
    Unknown34 = 0;
    return 0;
}
