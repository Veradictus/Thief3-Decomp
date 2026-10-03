// Game/Unsorted_10934A80_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class IDirect3DVertexBuffer8;

class IDirect3DDevice8
{
public:
    virtual long __stdcall Virtual0();
    virtual long __stdcall Virtual1();
    virtual long __stdcall Virtual2();
    virtual long __stdcall Virtual3();
    virtual long __stdcall Virtual4();
    virtual long __stdcall Virtual5();
    virtual long __stdcall Virtual6();
    virtual long __stdcall Virtual7();
    virtual long __stdcall Virtual8();
    virtual long __stdcall Virtual9();
    virtual long __stdcall Virtual10();
    virtual long __stdcall Virtual11();
    virtual long __stdcall Virtual12();
    virtual long __stdcall Virtual13();
    virtual long __stdcall Virtual14();
    virtual long __stdcall Virtual15();
    virtual long __stdcall Virtual16();
    virtual long __stdcall Virtual17();
    virtual long __stdcall Virtual18();
    virtual long __stdcall Virtual19();
    virtual long __stdcall Virtual20();
    virtual long __stdcall Virtual21();
    virtual long __stdcall Virtual22();
    virtual long __stdcall CreateVertexBuffer(unsigned int Length, unsigned long Usage, unsigned long FVF, int Pool, IDirect3DVertexBuffer8** ppVertexBuffer);
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

class Class_109343B0
{
public:
    void FUN_109343b0(IDirect3DVertexBuffer8** A);
};

class Class_10934D10
{
public:
    long FUN_10934d10();

    char Unknown00[0xC];
    IDirect3DDevice8* Unknown0C;
    unsigned int Unknown10;
    char Unknown14[8];
    IDirect3DVertexBuffer8* Unknown1C;
    Class_109343B0 Unknown20;
};

// FUNCTION: 0x10934D10 ?FUN_10934d10@Class_10934D10@@QAEJXZ
long Class_10934D10::FUN_10934d10()
{
    FUN_10905aa0()->Virtual8(0, 0);
    long Result = Unknown0C->CreateVertexBuffer(Unknown10, 0x208, 0, 0, &Unknown1C);
    FUN_10905aa0()->Virtual9();
    Unknown20.FUN_109343b0(&Unknown1C);
    return Result;
}
