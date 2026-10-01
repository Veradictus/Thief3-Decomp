// Game/Unsorted_10ABDEE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

    char Unknown00[0xE8];
    FString UnknownE8;
};

class Class_1098E330
{
public:
    virtual void Virtual0();
    int FUN_1098e330(int Id, int* Out);

    char Unknown04[0xF4];
    int UnknownF8;
    int UnknownFC;
};

// FUNCTION: 0x10ABDEE0 ?FUN_10abdee0@@YAXPAVClass_Field04@@PAVFString@@@Z
void FUN_10abdee0(Class_Field04* A, FString* B)
{
    if (!A->FUN_1098e290(0x40813, B))
        *B = A->UnknownE8;
}

// FUNCTION: 0x10ABDF60 ?FUN_10abdf60@@YAHPAVClass_1098E330@@@Z
int FUN_10abdf60(Class_1098E330* Obj)
{
    int Value = -1;
    if (!Obj->FUN_1098e330(0x200815, &Value))
        return Obj->UnknownF8;
    return Value;
}

// FUNCTION: 0x10ABDFA0 ?FUN_10abdfa0@@YAHPAVClass_1098E330@@@Z
int FUN_10abdfa0(Class_1098E330* Obj)
{
    int Value = -1;
    if (!Obj->FUN_1098e330(0x200816, &Value))
        return Obj->UnknownFC;
    return Value;
}
