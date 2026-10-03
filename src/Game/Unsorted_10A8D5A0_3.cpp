// Game/Unsorted_10A8D5A0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

extern void* DAT_10e6c7fc[];

extern void* DAT_10e6c7f8[];

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

class Class_10E6C7FC : public Class_10E6DC88
{
public:
    Class_10E6C7FC() : Class_10E6DC88(0x2d)
    {
        VTable = DAT_10e6c7fc;
        VTable0C = DAT_10e6c7f8;
    }
};

class Class_10E5D760
{
public:
    virtual Class_10E6C7FC* FUN_10a8d5a0();
};

// FUNCTION: 0x10A8D5A0 ?FUN_10a8d5a0@Class_10E5D760@@UAEPAVClass_10E6C7FC@@XZ
Class_10E6C7FC* Class_10E5D760::FUN_10a8d5a0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6C7FC* Result = new(0, 0, 0, 0, 0) Class_10E6C7FC;
    FUN_10905aa0()->Virtual9();
    return Result;
}
