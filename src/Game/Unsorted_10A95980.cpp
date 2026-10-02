// Game/Unsorted_10A95980.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A67CA0
{
public:
    void FUN_10a67ca0();
};

struct Struct_10AA3520
{
    char Unknown00[0x70];
    Class_10A67CA0* Unknown70;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10E6CE6C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a95980(int A, int B, int C);
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

extern void* DAT_10e6ce28[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E6CE28 : public Class_10EB766C
{
public:
    Class_10E6CE28()
    {
        VTable = DAT_10e6ce28;
    }
};

class Class_10E5D81C
{
public:
    virtual Class_10E6CE28* FUN_10a959a0();
};

// FUNCTION: 0x10A95980 ?FUN_10a95980@Class_10E6CE6C@@UAEHHHH@Z
int Class_10E6CE6C::FUN_10a95980(int A, int B, int C)
{
    if (DAT_10f35dec)
    {
        Class_10A67CA0* Obj = DAT_10f35dec->Unknown70;
        if (Obj)
            Obj->FUN_10a67ca0();
    }
    return 1;
}

// FUNCTION: 0x10A959A0 ?FUN_10a959a0@Class_10E5D81C@@UAEPAVClass_10E6CE28@@XZ
Class_10E6CE28* Class_10E5D81C::FUN_10a959a0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CE28* Result = new(0, 0, 0, 0, 0) Class_10E6CE28;
    FUN_10905aa0()->Virtual9();
    return Result;
}
