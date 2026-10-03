// Game/Unsorted_10A8D680.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10EB766C
{
public:
    virtual ~Class_10EB766C();

    int Unknown04;
    int Unknown08;
};

class Class_10E5B578
{
public:
    virtual int Virtual0(int A, int B, int C, int* D) = 0;
};

class Class_10E6DC88 : public Class_10EB766C, public Class_10E5B578
{
public:
    Class_10E6DC88(int Value);
    virtual ~Class_10E6DC88();

    int Unknown10;
};

// Its primary table is folded with the one 0x10A8D5A0's class stores; its
// second base's table (0x10E70820) with Class_10E8C22C's.
class Class_10E6C7FC : public Class_10E6DC88
{
public:
    Class_10E6C7FC()
        : Class_10E6DC88(0x2e)
    {
    }

    virtual int Virtual0(int A, int B, int C, int* D);
};

class Class_10E5D764
{
public:
    virtual Class_10E6C7FC* FUN_10a8d680();
};

// FUNCTION: 0x10A8D680 ?FUN_10a8d680@Class_10E5D764@@UAEPAVClass_10E6C7FC@@XZ
Class_10E6C7FC* Class_10E5D764::FUN_10a8d680()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6C7FC* Result = new(0, 0, 0, 0, 0) Class_10E6C7FC;
    FUN_10905aa0()->Virtual9();
    return Result;
}
