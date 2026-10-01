// Game/Unsorted_10C48200.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C49020
{
public:
    int FUN_10c49020();

    char Unknown00[0x20];
    int* Unknown20;
    char Unknown24[0xC];
    int* Unknown30;
};

class Class_10C49200
{
public:
    void FUN_10c48b80(int A);
    void FUN_10c49200();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_10C49230
{
public:
    void FUN_10c48c00(int A);
    void FUN_10c49230();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Object_10C4A030
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
};

class Class_10C4A030_Member10
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
};

class Class_10C4A150
{
public:
    void FUN_10c49da0(int A);
    void FUN_10c4a150();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_10E9BC18
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
    virtual void FUN_10c4a030();

    char Unknown04[0xC];
    Class_10C4A030_Member10 Unknown10;
    char Unknown14[0x4C];
    Class_10C4A150 Unknown60;
    char Unknown78[4];
    Object_10C4A030* Unknown7C;
};

class Class_10E9BB60 {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual unsigned int FUN_10c48200(int p1, unsigned int p2, unsigned int p3, unsigned int p4);
};

class Class_10E9BB80
{
public:
    virtual void Virtual0();
    virtual int FUN_10c483e0(unsigned int* A, unsigned int* B);
};

// FUNCTION: 0x10C48200 ?FUN_10c48200@Class_10E9BB60@@UAEIHIII@Z
unsigned int Class_10E9BB60::FUN_10c48200(int p1, unsigned int p2, unsigned int p3, unsigned int p4)
{
    unsigned int Avail = p3 - p2;
    if (p4 < Avail)
        return p4;
    return Avail;
}

// FUNCTION: 0x10C483E0 ?FUN_10c483e0@Class_10E9BB80@@UAEHPAI0@Z
int Class_10E9BB80::FUN_10c483e0(unsigned int* A, unsigned int* B)
{
    unsigned int X = *A;
    unsigned int Y = *B;
    if (X == Y)
        return 0;
    return X > Y ? 1 : -1;
}

// FUNCTION: 0x10C49020 ?FUN_10c49020@Class_10C49020@@QAEHXZ
int Class_10C49020::FUN_10c49020()
{
    ++*Unknown30;
    --*Unknown20;
    return *Unknown20;
}

// FUNCTION: 0x10C49200 ?FUN_10c49200@Class_10C49200@@QAEXXZ
void Class_10C49200::FUN_10c49200()
{
    FUN_10c48b80(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}

// FUNCTION: 0x10C49230 ?FUN_10c49230@Class_10C49230@@QAEXXZ
void Class_10C49230::FUN_10c49230()
{
    FUN_10c48c00(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}

// FUNCTION: 0x10C4A030 ?FUN_10c4a030@Class_10E9BC18@@UAEXXZ
void Class_10E9BC18::FUN_10c4a030()
{
    Unknown7C->Virtual1();
    Unknown10.Virtual6();
    Unknown60.FUN_10c49da0(0x40);
}

// FUNCTION: 0x10C4A150 ?FUN_10c4a150@Class_10C4A150@@QAEXXZ
void Class_10C4A150::FUN_10c4a150()
{
    FUN_10c49da0(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}
