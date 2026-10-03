// Game/Unsorted_10BD97D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e93f68[];

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E93F68 : public Class_10E90D70
{
public:
    Class_10E93F68* FUN_10bd97d0(int A, int B, int C, bool D, bool E);

    int Unknown40;
    bool Unknown44;
    bool Unknown45;
    int Unknown48;
    int Unknown4C;
    bool Unknown50;
    bool Unknown51;
    FArray Unknown54;
    int Unknown60;
};

class Class_10AA82D0
{
public:
    int FUN_10aa82d0();
};

class Class_10BF7F90 : public Class_10AA82D0
{
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    Class_10BF7F90* FUN_10bc4160();
};

class Class_10E94578 : public Class_10BC4160
{
public:
    virtual void Virtual1();

    void FUN_10bc5b50();
};

class Class_10BFF460
{
public:
    bool FUN_10bff460();
};

class Class_10BBB410
{
public:
    Class_10BFF460* FUN_10bbb410();
};

class Object_10BDAEB0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10E94218 : public Class_10E94578
{
public:
    virtual void FUN_10bdaeb0();

    Class_10BBB410* Unknown04;
    char Unknown08[0x38];
    Object_10BDAEB0* Unknown40;
};

// FUNCTION: 0x10BD97D0 ?FUN_10bd97d0@Class_10E93F68@@QAEPAV1@HHH_N0@Z
Class_10E93F68* Class_10E93F68::FUN_10bd97d0(int A, int B, int C, bool D, bool E)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown00 = DAT_10e93f68;
    Unknown40 = C;
    Unknown44 = E;
    Unknown45 = D;
    Unknown48 = 0;
    Unknown4C = 0;
    Unknown50 = false;
    Unknown51 = false;
    Unknown54.FArray::FArray();
    Unknown60 = 0;
    return this;
}

// FUNCTION: 0x10BDAEB0 ?FUN_10bdaeb0@Class_10E94218@@UAEXXZ
void Class_10E94218::FUN_10bdaeb0()
{
    if (Unknown40)
        Unknown40->Virtual2();
    Class_10BFF460* Obj = Unknown04->FUN_10bbb410();
    if (!Obj || !Obj->FUN_10bff460() || FUN_10bc4160()->FUN_10aa82d0() == 0)
        FUN_10bc5b50();
}
