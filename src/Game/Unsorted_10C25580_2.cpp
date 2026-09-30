// Game/Unsorted_10C25580_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Object_10C255F0
{
    char Unknown00[0xC];
    unsigned char Unknown0C;
};

void FUN_10ad1dc0(void* Ptr);

extern void* DAT_10ff7098;

extern float DAT_10e49984;

class Class_10e992d4
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
    virtual float FUN_10c26200();
};

extern float DAT_10e49684;

class Class_10E5CB88
{
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual float FUN_10c26290();
};

extern float DAT_10e99258;

class Class_10E99298
{
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3() = 0;
    virtual void Virtual4() = 0;
    virtual void Virtual5() = 0;
    virtual void Virtual6() = 0;
    virtual void Virtual7() = 0;
    virtual void Virtual8() = 0;
    virtual void Virtual9() = 0;
    virtual float FUN_10c262a0();
};

class Class_10E992D4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10c262b0(int p1, int p2, int p3, int p4);
    char Unknown04[0x20];
    int Unknown24;
    int Unknown28;
    int Unknown2C;
};

class Class_10C26660
{
public:
    char Unknown00[0x38];
    int Unknown38;

    bool FUN_10c26660();
};

// FUNCTION: 0x10C255F0 ?FUN_10c255f0@@YAHPAPAUObject_10C255F0@@0@Z
int FUN_10c255f0(Object_10C255F0** A, Object_10C255F0** B)
{
    Object_10C255F0* ObjA = *A;
    Object_10C255F0* ObjB = *B;
    if (ObjA->Unknown0C == ObjB->Unknown0C)
        return 0;
    return ObjA->Unknown0C > ObjB->Unknown0C ? -1 : 1;
}

// FUNCTION: 0x10C25610 ?FUN_10c25610@@YAXXZ
void FUN_10c25610()
{
    --*(int*)DAT_10ff7098;
    if (*(int*)DAT_10ff7098 == 0)
    {
        FUN_10ad1dc0(DAT_10ff7098);
        DAT_10ff7098 = 0;
    }
}

// FUNCTION: 0x10C26200 ?FUN_10c26200@Class_10e992d4@@UAEMXZ
float Class_10e992d4::FUN_10c26200()
{
    return DAT_10e49984;
}

// FUNCTION: 0x10C26290 ?FUN_10c26290@Class_10E5CB88@@UAEMXZ
float Class_10E5CB88::FUN_10c26290()
{
    return DAT_10e49684;
}

// FUNCTION: 0x10C262A0 ?FUN_10c262a0@Class_10E99298@@UAEMXZ
float Class_10E99298::FUN_10c262a0()
{
    return DAT_10e99258;
}

// FUNCTION: 0x10C262B0 ?FUN_10c262b0@Class_10E992D4@@UAEXHHHH@Z
void Class_10E992D4::FUN_10c262b0(int p1, int p2, int p3, int p4)
{
    Unknown24 = p1;
    Unknown28 = p2;
    Unknown2C = p3;
}

// FUNCTION: 0x10C26660 ?FUN_10c26660@Class_10C26660@@QAE_NXZ
bool Class_10C26660::FUN_10c26660()
{
    return Unknown38 > 0;
}
