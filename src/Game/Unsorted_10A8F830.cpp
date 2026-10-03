// Game/Unsorted_10A8F830.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

extern void* DAT_10e6c904[];

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

class Class_10E6C90C : public Class_10E6DC88
{
public:
    Class_10E6C90C() : Class_10E6DC88(10)
    {
        VTable = DAT_10e6c90c;
        VTable0C = DAT_10e6c904;
    }
};

class Class_10E5D784
{
public:
    virtual Class_10E6C90C* FUN_10a8f900();
};

// FUNCTION: 0x10A8F900 ?FUN_10a8f900@Class_10E5D784@@UAEPAVClass_10E6C90C@@XZ
Class_10E6C90C* Class_10E5D784::FUN_10a8f900()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6C90C* Result = new(0, 0, 0, 0, 0) Class_10E6C90C;
    FUN_10905aa0()->Virtual9();
    return Result;
}
