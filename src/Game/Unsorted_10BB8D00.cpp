// Game/Unsorted_10BB8D00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9925C
{
public:
    ~Class_10E9925C();

    virtual void Virtual0();
};

struct Struct_10BB8FF0
{
    int Count;
    int Unknown04;
    Class_10E9925C** Items;
};

class Class_10BB95C0
{
public:
    bool FUN_10bb95c0(int Value);

    // The index of the first element equal to Value, else -1.
    int FindIndex(int Value)
    {
        for (int i = 0; i < Unknown220; i++)
        {
            if (Unknown228[i] == Value)
                return i;
        }
        return -1;
    }

    char Unknown00[0x220];
    int Unknown220;
    char Unknown224[4];
    int* Unknown228;
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10A2C2F0
{
public:
    void FUN_10a2c200(void* A, int* B);
};

Class_10A2C2F0* FUN_10a2c6b0();

class Class_10BB9FC0
{
public:
    void FUN_10bb9e90();
    void FUN_10bb9fc0();

    char Unknown00[8];
    Class_10c7d570* Unknown08;
    char Unknown0C[0x278];
    int Unknown284;
};

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

class Class_10BBA080
{
public:
    unsigned char FUN_10bb8c60();
    int FUN_10bba080(Class_1098E330* Obj);
};

// FUNCTION: 0x10BB8FF0 ?FUN_10bb8ff0@@YAXPAUStruct_10BB8FF0@@@Z
void FUN_10bb8ff0(Struct_10BB8FF0* Array)
{
    for (int i = 0; i < Array->Count; i++)
        delete Array->Items[i];
    Array->Count = 0;
}

// FUNCTION: 0x10BB95C0 ?FUN_10bb95c0@Class_10BB95C0@@QAE_NH@Z
bool Class_10BB95C0::FUN_10bb95c0(int Value)
{
    return FindIndex(Value) != -1;
}

// FUNCTION: 0x10BB9FC0 ?FUN_10bb9fc0@Class_10BB9FC0@@QAEXXZ
void Class_10BB9FC0::FUN_10bb9fc0()
{
    FUN_10bb9e90();
    if (Unknown284)
        FUN_10a2c6b0()->FUN_10a2c200(Unknown08->FUN_10c7d570(), &Unknown284);
}

// FUNCTION: 0x10BBA080 ?FUN_10bba080@Class_10BBA080@@QAEHPAVClass_1098E330@@@Z
int Class_10BBA080::FUN_10bba080(Class_1098E330* Obj)
{
    Obj->FUN_1098e330(0x48000782, (int*)&Obj);
    if (FUN_10bb8c60() <= 1)
        return ((int)Obj & 1) > 0;
    return ((int)Obj & 2) > 0;
}
