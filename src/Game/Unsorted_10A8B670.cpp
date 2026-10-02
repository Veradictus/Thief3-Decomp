// Game/Unsorted_10A8B670.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

template <class T> class TArray
{
public:
    T* Data;
    int ArrayNum;
    int ArrayMax;
};

class UObject
{
public:
    static TArray<UObject*> GObjObjects;
};

class Class_10F3A1EC_Field0C
{
public:
    char Unknown00[0x1C];
    int Unknown1C;
};

class Class_10F3A1EC
{
public:
    int Unknown00;
    int Unknown04;
    int Unknown08;
    Class_10F3A1EC_Field0C* Unknown0C;
    int Unknown10;
    char Unknown14[0x10];
    int Unknown24;
};

extern Class_10F3A1EC* DAT_10f3a1ec;

class Class_10E6C68C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10a8b860();
};

// Ion Storm's memory manager (0x10905AA0): the allocation happens inside a
// scope of it (slots 8 and 9).
class Class_10905A90_Member
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
    virtual void Virtual8(int A, int B);
    virtual void Virtual9();
};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

enum EName
{
    NAME_None = 0
};

class FName
{
public:
    FName(EName N) : Index(N) {}

    int Index;
};

extern void* DAT_10e6c6c4[];

class Class_10E6C6C4
{
public:
    Class_10E6C6C4() : VTable(DAT_10e6c6c4), Unknown04(NAME_None) {}

    void** VTable;
    FName Unknown04;
};

class Class_10E5D74C
{
public:
    virtual Class_10E6C6C4* FUN_10a8c030(int A, int B);
};

// FUNCTION: 0x10A8B860 ?FUN_10a8b860@Class_10E6C68C@@UAEHXZ
int Class_10E6C68C::FUN_10a8b860()
{
    int Pending;
    if (DAT_10f3a1ec->Unknown04 == 0)
        Pending = DAT_10f3a1ec->Unknown08 < UObject::GObjObjects.ArrayNum;
    else if (DAT_10f3a1ec->Unknown10 == DAT_10f3a1ec->Unknown0C->Unknown1C && DAT_10f3a1ec->Unknown24 == 0)
        Pending = 0;
    else
        Pending = 1;
    return !Pending;
}

// FUNCTION: 0x10A8C030 ?FUN_10a8c030@Class_10E5D74C@@UAEPAVClass_10E6C6C4@@HH@Z
Class_10E6C6C4* Class_10E5D74C::FUN_10a8c030(int A, int B)
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6C6C4* Result = new(0, 0, 0, 0, 0) Class_10E6C6C4;
    FUN_10905aa0()->Virtual9();
    return Result;
}
