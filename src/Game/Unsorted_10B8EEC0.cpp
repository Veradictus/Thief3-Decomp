// Game/Unsorted_10B8EEC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

extern void* DAT_10e89778[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E89778 : public Class_10EB766C
{
public:
    Class_10E89778()
    {
        VTable = DAT_10e89778;
    }
};

class Class_10E88D44
{
public:
    virtual Class_10E89778* FUN_10b8efd0();
};

// FUNCTION: 0x10B8EFD0 ?FUN_10b8efd0@Class_10E88D44@@UAEPAVClass_10E89778@@XZ
Class_10E89778* Class_10E88D44::FUN_10b8efd0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E89778* Result = new(0, 0, 0, 0, 0) Class_10E89778;
    FUN_10905aa0()->Virtual9();
    return Result;
}
