// Game/Unsorted_10A933A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

extern void* DAT_10e6cc48[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E6CC48 : public Class_10EB766C
{
public:
    Class_10E6CC48()
    {
        VTable = DAT_10e6cc48;
    }
};

class Class_10E5D7F0
{
public:
    virtual Class_10E6CC48* FUN_10a93460();
};

// FUNCTION: 0x10A93460 ?FUN_10a93460@Class_10E5D7F0@@UAEPAVClass_10E6CC48@@XZ
Class_10E6CC48* Class_10E5D7F0::FUN_10a93460()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CC48* Result = new(0, 0, 0, 0, 0) Class_10E6CC48;
    FUN_10905aa0()->Virtual9();
    return Result;
}
