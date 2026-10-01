// Game/Unsorted_10ABD820_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FString
{
public:
    FString& operator=(const FString& Other);

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_Field04
{
public:
    int FUN_1098e290(int Id, FString* Out);

    char Unknown00[0xDC];
    FString UnknownDC;
};

class Class_1098E330
{
public:
    virtual void Virtual0();
    int FUN_1098e330(int Id, int* Out);

    char Unknown04[0xFC];
    int Unknown100;
    int Unknown104;
};

// FUNCTION: 0x10ABDEB0 ?FUN_10abdeb0@@YAXPAVClass_Field04@@PAVFString@@@Z
void FUN_10abdeb0(Class_Field04* A, FString* B)
{
    if (!A->FUN_1098e290(0x40812, B))
        *B = A->UnknownDC;
}

// FUNCTION: 0x10ABDFE0 ?FUN_10abdfe0@@YAHPAVClass_1098E330@@@Z
int FUN_10abdfe0(Class_1098E330* Obj)
{
    int Value = -1;
    if (!Obj->FUN_1098e330(0x200817, &Value))
        return Obj->Unknown100;
    return Value;
}

// FUNCTION: 0x10ABE020 ?FUN_10abe020@@YAHPAVClass_1098E330@@@Z
int FUN_10abe020(Class_1098E330* Obj)
{
    int Value = -1;
    if (!Obj->FUN_1098e330(0x200818, &Value))
        return Obj->Unknown104;
    return Value;
}
