// Game/Unsorted_10C549A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C55090
{
public:
    void FUN_10c55090();

    Class_10C55090* Unknown00;
    Class_10C55090* Unknown04;
};

class Class_10C55800
{
public:
    void FUN_10c553a0();

    char Unknown00[0x18];
    Class_10C55090* Unknown18;
    int Unknown1C;
};

class Class_10AFCF40
{
public:
    int FUN_10afcf40();
};

class TimeManager : public Class_10AFCF40
{
public:
    static TimeManager* Instance();
};

class Class_10C549E0_Object
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
    virtual int Virtual15(int Time);
};

struct Struct_10C549E0
{
    char Unknown00[8];
    Class_10C549E0_Object* Unknown08;
};

// FUNCTION: 0x10C549E0 ?FUN_10c549e0@@YAHPAPAUStruct_10C549E0@@0@Z
int FUN_10c549e0(Struct_10C549E0** A, Struct_10C549E0** B)
{
    Struct_10C549E0* ItemA = *A;
    Struct_10C549E0* ItemB = *B;
    int Time = TimeManager::Instance()->FUN_10afcf40();
    return ItemB->Unknown08->Virtual15(Time) - ItemA->Unknown08->Virtual15(Time);
}

// FUNCTION: 0x10C553A0 ?FUN_10c553a0@Class_10C55800@@QAEXXZ
void Class_10C55800::FUN_10c553a0()
{
    Class_10C55090* Node = Unknown18->Unknown00;
    Unknown18->Unknown00 = Unknown18;
    Unknown18->Unknown04 = Unknown18;
    Unknown1C = 0;
    while (Node != Unknown18)
    {
        Class_10C55090* Next = Node->Unknown00;
        Node->FUN_10c55090();
        ::operator delete(Node);
        Node = Next;
    }
}
