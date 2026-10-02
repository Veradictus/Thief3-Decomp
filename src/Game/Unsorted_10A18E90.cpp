// Game/Unsorted_10A18E90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A88A50
{
public:
    bool FUN_10a88a50(int p1);
};

class Class_10A18F80
{
public:
    bool FUN_10a18f80(int p1);

    int Unknown00;
    Class_10A88A50* Unknown04;
};

struct Info_10A18FA0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10A18FA0
{
public:
    bool FUN_10a18fa0(int Index);

    char Unknown00[0x320];
    Info_10A18FA0 Unknown320[1];
};

class Object_10A18F40
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(float A);
};

class Class_10E5D70C
{
public:
    virtual void Virtual0();
    virtual void FUN_10a18f40(float A);

    void FUN_10a18e90();
    void FUN_10a18f10();

    Object_10A18F40* Unknown04;
    char Unknown08[0x668];
    float Unknown670;
};

// FUNCTION: 0x10A18F40 ?FUN_10a18f40@Class_10E5D70C@@UAEXM@Z
void Class_10E5D70C::FUN_10a18f40(float A)
{
    if (Unknown04)
    {
        FUN_10a18e90();
        FUN_10a18f10();
        Unknown04->Virtual2(A);
        Unknown670 = A;
    }
}

// FUNCTION: 0x10A18F80 ?FUN_10a18f80@Class_10A18F80@@QAE_NH@Z
bool Class_10A18F80::FUN_10a18f80(int p1)
{
    if (!Unknown04)
        return false;
    return Unknown04->FUN_10a88a50(p1);
}

// FUNCTION: 0x10A18FA0 ?FUN_10a18fa0@Class_10A18FA0@@QAE_NH@Z
bool Class_10A18FA0::FUN_10a18fa0(int Index)
{
    return Unknown320[Index].Unknown00 > 0;
}
