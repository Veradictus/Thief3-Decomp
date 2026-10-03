// Game/Unsorted_10A95CA0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

extern void* DAT_10e6cea8[];

extern void* DAT_10e6cea4[];

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

// Named after its second base's table (0x10E6CEA4), where its Virtual0
// (0x10A95D40) sits.
class Class_10E6CEA4 : public Class_10E6DC88
{
public:
    Class_10E6CEA4() : Class_10E6DC88(0x4b)
    {
        VTable = DAT_10e6cea8;
        VTable0C = DAT_10e6cea4;
    }
};

class Class_10E5D828
{
public:
    virtual Class_10E6CEA4* FUN_10a95ca0();
};

// FUNCTION: 0x10A95CA0 ?FUN_10a95ca0@Class_10E5D828@@UAEPAVClass_10E6CEA4@@XZ
Class_10E6CEA4* Class_10E5D828::FUN_10a95ca0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CEA4* Result = new(0, 0, 0, 0, 0) Class_10E6CEA4;
    FUN_10905aa0()->Virtual9();
    return Result;
}
