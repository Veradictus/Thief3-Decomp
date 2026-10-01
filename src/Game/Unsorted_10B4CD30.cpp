// Game/Unsorted_10B4CD30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10971570
{
public:
    void FUN_10971570(int A, bool* B);
};

class Class_10B4D010_Param
{
public:
    char Unknown00[0x448];
    Class_10971570* Unknown448;
    int Unknown44C;
};

class Class_10E7E9B8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10b4d010(Class_10B4D010_Param* A);

    void FUN_10b4c840(Class_10B4D010_Param* A);

    char Unknown04[0xC];
    int Unknown10;
};

class Object_10B4D050
{
public:
    char Unknown00[0x440];
    void* Unknown440;
    char Unknown444[8];
    int Unknown44C;
};

class Class_10E7EA00
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10b4d050(Object_10B4D050* P);

    void FUN_10b4cad0(Object_10B4D050* P);

    char Unknown04[0xC];
    int Unknown10;
    int Unknown14;
};

// FUNCTION: 0x10B4D010 ?FUN_10b4d010@Class_10E7E9B8@@UAEXPAVClass_10B4D010_Param@@@Z
void Class_10E7E9B8::FUN_10b4d010(Class_10B4D010_Param* A)
{
    bool Value;
    A->Unknown448->FUN_10971570(0x20000bd, &Value);
    A->Unknown44C = Value;
    FUN_10b4c840(A);
    Unknown10 = 0x21;
}

// FUNCTION: 0x10B4D050 ?FUN_10b4d050@Class_10E7EA00@@UAEXPAVObject_10B4D050@@@Z
void Class_10E7EA00::FUN_10b4d050(Object_10B4D050* P)
{
    if (P->Unknown440 != 0 && P->Unknown44C != 0)
    {
        Unknown14 = 0;
        Unknown10 = 0;
        FUN_10b4cad0(P);
    }
}
