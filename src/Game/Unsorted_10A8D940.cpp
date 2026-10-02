// Game/Unsorted_10A8D940.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

extern void* DAT_10e6c890[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E6C890 : public Class_10EB766C
{
public:
    Class_10E6C890()
    {
        VTable = DAT_10e6c890;
    }
};

class Class_10E5D77C
{
public:
    virtual Class_10E6C890* FUN_10a8d9e0();
};

extern void* DAT_10e6c8ac[];

class Class_10E6C8AC : public Class_10EB766C
{
public:
    Class_10E6C8AC()
    {
        VTable = DAT_10e6c8ac;
    }
};

class Class_10E5D778
{
public:
    virtual Class_10E6C8AC* FUN_10a8e0c0();
};

// FUNCTION: 0x10A8D9E0 ?FUN_10a8d9e0@Class_10E5D77C@@UAEPAVClass_10E6C890@@XZ
Class_10E6C890* Class_10E5D77C::FUN_10a8d9e0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6C890* Result = new(0, 0, 0, 0, 0) Class_10E6C890;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A8E0C0 ?FUN_10a8e0c0@Class_10E5D778@@UAEPAVClass_10E6C8AC@@XZ
Class_10E6C8AC* Class_10E5D778::FUN_10a8e0c0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6C8AC* Result = new(0, 0, 0, 0, 0) Class_10E6C8AC;
    FUN_10905aa0()->Virtual9();
    return Result;
}
