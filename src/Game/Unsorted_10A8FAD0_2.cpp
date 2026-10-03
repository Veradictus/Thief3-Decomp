// Game/Unsorted_10A8FAD0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

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

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e6c90c[];

extern void* DAT_10e6c928[];

// Constructed by 0x10AAF5B0: a primary table at +0x0 and a second base's at +0xC.
class Class_10E6DC88
{
public:
    Class_10E6DC88(int Value);

    void** VTable;
    int Unknown04;
    int Unknown08;
    void** VTable0C;
    int Unknown10;
};

// Its primary table is folded with Class_10E6C90C's; the second base's table
// (0x10E6C928) is its own.
class Class_10E6C928 : public Class_10E6DC88
{
public:
    Class_10E6C928() : Class_10E6DC88(0xc)
    {
        VTable = DAT_10e6c90c;
        VTable0C = DAT_10e6c928;
    }
};

class Class_10E5D78C
{
public:
    virtual Class_10E6C928* FUN_10a8fb50();
};

extern void* DAT_10e6c930[];

extern void* DAT_10e6c92c[];

class Class_10E6C930 : public Class_10E6DC88
{
public:
    Class_10E6C930() : Class_10E6DC88(0xd)
    {
        VTable = DAT_10e6c930;
        VTable0C = DAT_10e6c92c;
    }
};

class Class_10E5D790
{
public:
    virtual Class_10E6C930* FUN_10a8fbf0();
};

extern void* DAT_10e6c950[];

extern void* DAT_10e6c94c[];

class Class_10E6C950 : public Class_10E6DC88
{
public:
    Class_10E6C950() : Class_10E6DC88(0xe)
    {
        VTable = DAT_10e6c950;
        VTable0C = DAT_10e6c94c;
    }
};

class Class_10E5D794
{
public:
    virtual Class_10E6C950* FUN_10a90060();
};

// FUNCTION: 0x10A8FB50 ?FUN_10a8fb50@Class_10E5D78C@@UAEPAVClass_10E6C928@@XZ
Class_10E6C928* Class_10E5D78C::FUN_10a8fb50()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6C928* Result = new(0, 0, 0, 0, 0) Class_10E6C928;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A8FBF0 ?FUN_10a8fbf0@Class_10E5D790@@UAEPAVClass_10E6C930@@XZ
Class_10E6C930* Class_10E5D790::FUN_10a8fbf0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6C930* Result = new(0, 0, 0, 0, 0) Class_10E6C930;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A90060 ?FUN_10a90060@Class_10E5D794@@UAEPAVClass_10E6C950@@XZ
Class_10E6C950* Class_10E5D794::FUN_10a90060()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6C950* Result = new(0, 0, 0, 0, 0) Class_10E6C950;
    FUN_10905aa0()->Virtual9();
    return Result;
}
