// Game/Unsorted_10A30E60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A32000
{
public:
    void FUN_10a32000(int Count);
    int FUN_10a32910(char* Value);

    int Unknown00;
    int Unknown04;
    char* Unknown08;
};

class Class_10A311E0
{
public:
    void FUN_10a30f20();

    void Destroy()
    {
        FUN_10a30f20();
        ::operator delete(this);
    }
};

extern Class_10A311E0* DAT_10f39f3c;

class Class_10DB58F0
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
    virtual void Virtual16(int A);
};

Class_10DB58F0* FUN_10db58f0();

class Class_10939570
{
public:
    void FUN_1093b5e0();
};

extern Class_10939570* DAT_10f323fc;

class Class_1093EDB0
{
public:
    void FUN_1093f7a0();
};

extern Class_1093EDB0* DAT_10f340c0;

class Class_10E6BF5C
{
public:
    void FUN_10a7eaf0(void* A);
};

Class_10E6BF5C* FUN_10a7ea80();

extern void* DAT_10f46d9c;

class Class_10B88C40
{
public:
    void FUN_10b88c40();
};

Class_10B88C40* FUN_10b89170();

void FUN_1092be90();

void FUN_109cc650();

void FUN_109cc9e0();

void FUN_10da8b20();

// FUNCTION: 0x10A30E60 ?FUN_10a30e60@@YAXH@Z
void FUN_10a30e60(int Type)
{
    switch (Type)
    {
    case 8:
        FUN_1092be90();
        break;
    case 10:
        DAT_10f323fc->FUN_1093b5e0();
        break;
    case 4:
        FUN_10db58f0()->Virtual16(Type);
        break;
    case 16:
        FUN_109cc650();
        break;
    case 17:
        FUN_109cc9e0();
        break;
    case 5:
        FUN_10da8b20();
        break;
    case 21:
        FUN_10a7ea80()->FUN_10a7eaf0(DAT_10f46d9c);
        break;
    case 29:
        DAT_10f340c0->FUN_1093f7a0();
        break;
    case 6:
        FUN_10b89170()->FUN_10b88c40();
        break;
    }
}

// FUNCTION: 0x10A311E0 ?FUN_10a311e0@@YAXXZ
void FUN_10a311e0()
{
    if (DAT_10f39f3c)
    {
        DAT_10f39f3c->Destroy();
        DAT_10f39f3c = 0;
    }
}

// FUNCTION: 0x10A32910 ?FUN_10a32910@Class_10A32000@@QAEHPAD@Z
int Class_10A32000::FUN_10a32910(char* Value)
{
    int Index = Unknown00;
    FUN_10a32000(Index + 1);
    Unknown08[Index] = *Value;
    return Index;
}
