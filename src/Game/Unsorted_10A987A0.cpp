// Game/Unsorted_10A987A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C08940
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3(int A, int B);
};

class Class_10978090
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();

    Class_10C08940* FUN_10978090();

    Class_10C08940* Unknown04;
};

class Class_10AAB5C0 : public Class_10978090
{
public:
    int FUN_10aab5c0();

    int Unknown08;
};

class Class_10E5B578
{
public:
    virtual int Virtual0(int A, int B, int C, int* D) = 0;
};

class Class_10E8C22C : public Class_10AAB5C0, public Class_10E5B578
{
public:
    virtual int Virtual0(int A, int B, int C, int* D);
};

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

extern void* DAT_10e6cfd4[];

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

// Its second base's table (0x10E70820) is folded with Class_10E8C22C's.
class Class_10E6CFD4 : public Class_10E6DC88
{
public:
    Class_10E6CFD4() : Class_10E6DC88(0x5c)
    {
        VTable = DAT_10e6cfd4;
        VTable0C = DAT_10e70820;
    }
};

class Class_10E5D840
{
public:
    virtual Class_10E6CFD4* FUN_10a98840();
};

extern void* DAT_10e6cff0[];

class Class_10E6CFF0 : public Class_10E6DC88
{
public:
    Class_10E6CFF0() : Class_10E6DC88(0x5d)
    {
        VTable = DAT_10e6cff0;
        VTable0C = DAT_10e70820;
    }
};

class Class_10E5D844
{
public:
    virtual Class_10E6CFF0* FUN_10a988e0();
};

// FUNCTION: 0x10A98840 ?FUN_10a98840@Class_10E5D840@@UAEPAVClass_10E6CFD4@@XZ
Class_10E6CFD4* Class_10E5D840::FUN_10a98840()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CFD4* Result = new(0, 0, 0, 0, 0) Class_10E6CFD4;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A988E0 ?FUN_10a988e0@Class_10E5D844@@UAEPAVClass_10E6CFF0@@XZ
Class_10E6CFF0* Class_10E5D844::FUN_10a988e0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CFF0* Result = new(0, 0, 0, 0, 0) Class_10E6CFF0;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A98980 ?Virtual0@Class_10E8C22C@@UAEHHHHPAH@Z
int Class_10E8C22C::Virtual0(int A, int B, int C, int* D)
{
    return FUN_10978090()->Virtual3(Virtual4(), FUN_10aab5c0());
}
