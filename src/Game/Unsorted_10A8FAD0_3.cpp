// Game/Unsorted_10A8FAD0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

extern void* DAT_10e6c950[];

extern void* DAT_10e6c96c[];

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

class Class_10E6C950 : public Class_10E6DC88
{
public:
    Class_10E6C950() : Class_10E6DC88(0xf)
    {
        VTable = DAT_10e6c950;
        VTable0C = DAT_10e6c96c;
    }
};

class Class_10E5D798
{
public:
    virtual Class_10E6C950* FUN_10a901a0();
};

// FUNCTION: 0x10A901A0 ?FUN_10a901a0@Class_10E5D798@@UAEPAVClass_10E6C950@@XZ
Class_10E6C950* Class_10E5D798::FUN_10a901a0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6C950* Result = new(0, 0, 0, 0, 0) Class_10E6C950;
    FUN_10905aa0()->Virtual9();
    return Result;
}
