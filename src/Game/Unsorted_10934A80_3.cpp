// Game/Unsorted_10934A80_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class IDirect3DSurface8;

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
    virtual long __stdcall Virtual23();
    virtual long __stdcall Virtual24();
    virtual long __stdcall Virtual25();
    virtual long __stdcall Virtual26();
    virtual long __stdcall CreateImageSurface(unsigned int Width, unsigned int Height, int Format, IDirect3DSurface8** ppSurface);
};

extern IDirect3DDevice8* GDirect3DDevice8;

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

class Class_10934D60
{
public:
    Class_10934D60* FUN_10934d60();

    IDirect3DSurface8* Unknown00;
};

// FUNCTION: 0x10934D60 ?FUN_10934d60@Class_10934D60@@QAEPAV1@XZ
Class_10934D60* Class_10934D60::FUN_10934d60()
{
    Unknown00 = 0;
    FUN_10905aa0()->Virtual8(0, 0);
    GDirect3DDevice8->CreateImageSurface(0x80, 0x80, 0x16, &Unknown00);
    FUN_10905aa0()->Virtual9();
    return this;
}
