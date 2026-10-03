// Game/Unsorted_10A989B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

extern void* DAT_10e6d00c[];

// The second base's table, folded with Class_10E8C22C's (0x10E70820).
extern void* DAT_10e70820[];

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

class Class_10E6D00C : public Class_10E6DC88
{
public:
    Class_10E6D00C() : Class_10E6DC88(0x5e)
    {
        VTable = DAT_10e6d00c;
        VTable0C = DAT_10e70820;
    }
};

class Class_10E5D848
{
public:
    virtual Class_10E6D00C* FUN_10a989b0();
};

// FUNCTION: 0x10A989B0 ?FUN_10a989b0@Class_10E5D848@@UAEPAVClass_10E6D00C@@XZ
Class_10E6D00C* Class_10E5D848::FUN_10a989b0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6D00C* Result = new(0, 0, 0, 0, 0) Class_10E6D00C;
    FUN_10905aa0()->Virtual9();
    return Result;
}
