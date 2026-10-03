// Game/Unsorted_10A715C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

class Class_10A111B0
{
public:
    void FUN_10a111b0();
};

class Class_10A72DB0 : public Class_10A111B0
{
public:
    void FUN_10a72db0();

    char Unknown00[0x18];
    void* Unknown18;
};

struct Struct_10A4C550_Node
{
    Struct_10A4C550_Node* Unknown00;
    Struct_10A4C550_Node* Unknown04;
    unsigned int Unknown08;
    int Unknown0C;
};

class Class_10A4C550_Iterator
{
public:
    Class_10A4C550_Iterator() {}

    Struct_10A4C550_Node* Unknown00;
};

class Class_10A4C550
{
public:
    Class_10A4C550_Iterator FUN_10a4c550(const unsigned int& Key);
};

class Class_10E6BAB0
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
    virtual int* FUN_10a73200(unsigned int Key);

    Class_10A4C550 Unknown04;
};

struct Struct_10AB0400
{
};

class Class_10AB0400
{
public:
    void FUN_10a6e990();
    void FUN_10ab0400()
    {
        FUN_10a6e990();
        delete Unknown04;
        Unknown04 = 0;
    }

    char Unknown00[4];
    Struct_10AB0400* Unknown04;
};

class Class_10A71C40
{
public:
    void FUN_10a71c40();

    char Unknown00[8];
    Class_10AB0400 Unknown08;
    char Unknown10[4];
    std::vector<void*> Unknown14;
};

// FUNCTION: 0x10A71C40 ?FUN_10a71c40@Class_10A71C40@@QAEXXZ
void Class_10A71C40::FUN_10a71c40()
{
    Unknown14.~vector();
    Unknown08.FUN_10ab0400();
}

// FUNCTION: 0x10A72DB0 ?FUN_10a72db0@Class_10A72DB0@@QAEXXZ
void Class_10A72DB0::FUN_10a72db0()
{
    FUN_10a111b0();
    ::operator delete(Unknown18);
    Unknown18 = 0;
}

// FUNCTION: 0x10A73200 ?FUN_10a73200@Class_10E6BAB0@@UAEPAHI@Z
int* Class_10E6BAB0::FUN_10a73200(unsigned int Key)
{
    Class_10A4C550_Iterator It = Unknown04.FUN_10a4c550(Key);
    return &It.Unknown00->Unknown0C;
}
