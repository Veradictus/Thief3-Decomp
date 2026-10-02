// Game/Unsorted_10ACD6C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

extern float DAT_10e499a4;

class Class_10E67938
{
public:
    virtual void FUN_10a4c470();
};

class Class_10E70060
{
public:
    virtual float FUN_10ace280(int A, int B, Class_1098E330* Obj) = 0;
};

class Class_10E70150 : public Class_10E67938, public Class_10E70060
{
public:
    virtual float FUN_10ace280(int A, int B, Class_1098E330* Obj);
};

class Class_10E700F0 {
public:
    virtual float FUN_10ace340(int a, int b, int c);
};

class Class_10E700D4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual float FUN_10ace1d0(Class_1098E330* A, int B, Class_1098E330* C);
};

// FUNCTION: 0x10ACE1D0 ?FUN_10ace1d0@Class_10E700D4@@UAEMPAVClass_1098E330@@H0@Z
float Class_10E700D4::FUN_10ace1d0(Class_1098E330* A, int B, Class_1098E330* C)
{
    float First = 0.0f;
    A->FUN_1098e330(0x10058b, (int*)&First);
    float Second = 0.0f;
    if (C)
        C->FUN_1098e330(0x100589, (int*)&Second);
    return Second + First;
}

// FUNCTION: 0x10ACE280 ?FUN_10ace280@Class_10E70150@@UAEMHHPAVClass_1098E330@@@Z
float Class_10E70150::FUN_10ace280(int A, int B, Class_1098E330* Obj)
{
    if (Obj)
    {
        float Value = 0.0f;
        Obj->FUN_1098e330(0x100588, (int*)&Value);
        return Value;
    }
    return DAT_10e499a4;
}

// FUNCTION: 0x10ACE340 ?FUN_10ace340@Class_10E700F0@@UAEMHHH@Z
float Class_10E700F0::FUN_10ace340(int a, int b, int c)
{
    return DAT_10e499a4;
}
