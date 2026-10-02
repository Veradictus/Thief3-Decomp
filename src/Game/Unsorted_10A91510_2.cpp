// Game/Unsorted_10A91510_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

extern void* DAT_10e6caac[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E6CAAC : public Class_10EB766C
{
public:
    Class_10E6CAAC()
    {
        VTable = DAT_10e6caac;
    }
};

class Class_10E5D7C0
{
public:
    virtual Class_10E6CAAC* FUN_10a91b50();
};

class Class_10C08940
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
    virtual void* Virtual8();
};

bool FUN_10a491b0(void* A);

class Class_10978090
{
public:
    virtual void Virtual0();

    Class_10C08940* FUN_10978090();
};

class Class_10E6CAC8 : public Class_10978090
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10a91e50(int A, int B);
};

extern void* DAT_10e6cae4[];

class Class_10E6CAE4 : public Class_10EB766C
{
public:
    Class_10E6CAE4()
    {
        VTable = DAT_10e6cae4;
    }
};

class Class_10E5D7C4
{
public:
    virtual Class_10E6CAE4* FUN_10a91f10();
};

extern void* DAT_10e6cb00[];

class Class_10E6CB00 : public Class_10EB766C
{
public:
    Class_10E6CB00()
    {
        VTable = DAT_10e6cb00;
    }
};

class Class_10E5D7C8
{
public:
    virtual Class_10E6CB00* FUN_10a922c0();
};

// FUNCTION: 0x10A91B50 ?FUN_10a91b50@Class_10E5D7C0@@UAEPAVClass_10E6CAAC@@XZ
Class_10E6CAAC* Class_10E5D7C0::FUN_10a91b50()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CAAC* Result = new(0, 0, 0, 0, 0) Class_10E6CAAC;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A91E50 ?FUN_10a91e50@Class_10E6CAC8@@UAE_NHH@Z
bool Class_10E6CAC8::FUN_10a91e50(int A, int B)
{
    return FUN_10a491b0(FUN_10978090()->Virtual8()) != 0;
}

// FUNCTION: 0x10A91F10 ?FUN_10a91f10@Class_10E5D7C4@@UAEPAVClass_10E6CAE4@@XZ
Class_10E6CAE4* Class_10E5D7C4::FUN_10a91f10()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CAE4* Result = new(0, 0, 0, 0, 0) Class_10E6CAE4;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A922C0 ?FUN_10a922c0@Class_10E5D7C8@@UAEPAVClass_10E6CB00@@XZ
Class_10E6CB00* Class_10E5D7C8::FUN_10a922c0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CB00* Result = new(0, 0, 0, 0, 0) Class_10E6CB00;
    FUN_10905aa0()->Virtual9();
    return Result;
}
