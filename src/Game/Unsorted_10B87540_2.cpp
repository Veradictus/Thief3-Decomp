// Game/Unsorted_10B87540_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10B8C7B0
{
public:
    void FUN_10b8c7b0();
};

class Class_10E893B0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void FUN_10b876c0();

    char Unknown04[0x74];
    Class_10B8C7B0* Unknown78;
};

class Class_10B87900_Member
{
public:
    char Unknown00[0x19];
    bool Unknown19;
};

class Class_10B87900
{
public:
    bool FUN_10b87900();

    char Unknown00[0x78];
    Class_10B87900_Member* Unknown78;
};

class Class_10B8D800
{
public:
    bool FUN_10b8d800(int A, int B, int C, int D);
};

class Class_10B87950
{
public:
    bool FUN_10b87950(int A, int B, int C, int D);

    char Unknown00[0x78];
    Class_10B8D800* Unknown78;
};

class Class_10B8C9F0
{
public:
    bool FUN_10b8c9f0(int A, int B, int C);
};

class Class_10B87970
{
public:
    bool FUN_10b87970(int A, int B, int C);

    char Unknown00[0x78];
    Class_10B8C9F0* Unknown78;
};

class Class_10B8CB20
{
public:
    bool FUN_10b8cb20(int p1, int p2, int p3, int p4);
};

class Class_10B87990
{
public:
    bool FUN_10b87990(int p1, int p2, int p3, int p4);

    char Unknown00[0x78];
    Class_10B8CB20* Unknown78;
};

class Class_10B8D030
{
public:
    void FUN_10b8d030(FVector* Min, FVector* Max);
};

class Class_10E89210
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void FUN_10b879b0(FVector* Min, FVector* Max);

    char Unknown04[0x74];
    Class_10B8D030* Unknown78;
};

class Class_10B8CFF0
{
public:
    void FUN_10b8cff0();

    char Unknown00[0x19];
    bool Unknown19;
};

class Class_10B87EA0
{
public:
    void FUN_10b87ea0();

    char Unknown00[0x78];
    Class_10B8CFF0* Unknown78;
};

class Class_10B87EC0_Member
{
public:
    char Unknown00[0xC];
    int Unknown0C;
};

class Class_10B87EC0
{
public:
    bool FUN_10b87ec0();

    char Unknown00[0x78];
    Class_10B87EC0_Member* Unknown78;
};

// FUNCTION: 0x10B876C0 ?FUN_10b876c0@Class_10E893B0@@UAEXXZ
void Class_10E893B0::FUN_10b876c0()
{
    if (Unknown78)
        Unknown78->FUN_10b8c7b0();
}

// FUNCTION: 0x10B87900 ?FUN_10b87900@Class_10B87900@@QAE_NXZ
bool Class_10B87900::FUN_10b87900()
{
    if (Unknown78)
        return Unknown78->Unknown19;
    return false;
}

// FUNCTION: 0x10B87950 ?FUN_10b87950@Class_10B87950@@QAE_NHHHH@Z
bool Class_10B87950::FUN_10b87950(int A, int B, int C, int D)
{
    if (Unknown78)
        return Unknown78->FUN_10b8d800(A, B, C, D);
    return false;
}

// FUNCTION: 0x10B87970 ?FUN_10b87970@Class_10B87970@@QAE_NHHH@Z
bool Class_10B87970::FUN_10b87970(int A, int B, int C)
{
    if (Unknown78)
        return Unknown78->FUN_10b8c9f0(A, B, C);
    return false;
}

// FUNCTION: 0x10B87990 ?FUN_10b87990@Class_10B87990@@QAE_NHHHH@Z
bool Class_10B87990::FUN_10b87990(int p1, int p2, int p3, int p4)
{
    if (Unknown78)
        return Unknown78->FUN_10b8cb20(p1, p2, p3, p4);
    return false;
}

// FUNCTION: 0x10B879B0 ?FUN_10b879b0@Class_10E89210@@UAEXPAVFVector@@0@Z
void Class_10E89210::FUN_10b879b0(FVector* Min, FVector* Max)
{
    if (Unknown78)
        Unknown78->FUN_10b8d030(Min, Max);
}

// FUNCTION: 0x10B87EA0 ?FUN_10b87ea0@Class_10B87EA0@@QAEXXZ
void Class_10B87EA0::FUN_10b87ea0()
{
    Class_10B8CFF0* Item = Unknown78;
    if (Item && Item->Unknown19)
        Item->FUN_10b8cff0();
}

// FUNCTION: 0x10B87EC0 ?FUN_10b87ec0@Class_10B87EC0@@QAE_NXZ
bool Class_10B87EC0::FUN_10b87ec0()
{
    if (Unknown78)
        return Unknown78->Unknown0C != 0;
    return false;
}
