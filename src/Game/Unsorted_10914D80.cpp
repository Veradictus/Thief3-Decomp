// Game/Unsorted_10914D80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780;

class Class_109169E0
{
public:
    int FUN_109169e0(const Class_1090A780& Name);
};

class Class_10915210
{
public:
    Class_109169E0* FUN_10915210(const Class_1090A780& Name);
    int FUN_10915810(const Class_1090A780& A, const Class_1090A780& B);
};

void FUN_10ad1dc0(void* Memory);

class Class_10915830
{
public:
    void FUN_109154f0(int A);
    void FUN_10915830();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_10916CA0
{
public:
    void FUN_10916b80(int A);
    void FUN_10916ca0();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_109242E0 {
public:
    void FUN_109242e0(int p1);
};

extern Class_109242E0* DAT_10f319a0;

class Class_10924E80
{
public:
    void FUN_10924e80(int A);
};

extern int DAT_10f2c740;

extern Class_10924E80* DAT_10f2c734;

extern int DAT_10efef54;

extern char DAT_10f2c75a;

extern int DAT_10f2c708;

extern int DAT_10f2c70c;

extern int DAT_10f2c710;

extern int DAT_10f2c714;

void FUN_10917c90(int A, int B, int C, int D);

// FUNCTION: 0x10915810 ?FUN_10915810@Class_10915210@@QAEHABVClass_1090A780@@0@Z
int Class_10915210::FUN_10915810(const Class_1090A780& A, const Class_1090A780& B)
{
    Class_109169E0* Obj = FUN_10915210(A);
    if (Obj == 0)
        return 0;
    return Obj->FUN_109169e0(B);
}

// FUNCTION: 0x10915830 ?FUN_10915830@Class_10915830@@QAEXXZ
void Class_10915830::FUN_10915830()
{
    FUN_109154f0(0x40);
    FUN_10ad1dc0(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}

// FUNCTION: 0x10916CA0 ?FUN_10916ca0@Class_10916CA0@@QAEXXZ
void Class_10916CA0::FUN_10916ca0()
{
    FUN_10916b80(0x40);
    FUN_10ad1dc0(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}

// FUNCTION: 0x10917C50 ?FUN_10917c50@@YAXH@Z
void FUN_10917c50(int p1)
{
    DAT_10f319a0->FUN_109242e0(p1);
}

// FUNCTION: 0x10917FC0 ?FUN_10917fc0@@YAXH@Z
void FUN_10917fc0(int A)
{
    if (DAT_10f2c740)
    {
        DAT_10efef54 = A;
        DAT_10f2c734->FUN_10924e80(A);
    }
    else
        DAT_10efef54 = -1;
}

// FUNCTION: 0x10918200 ?FUN_10918200@@YAXXZ
void FUN_10918200()
{
    if (DAT_10f2c75a)
        FUN_10917c90(DAT_10f2c708, DAT_10f2c70c, DAT_10f2c710, DAT_10f2c714);
}
