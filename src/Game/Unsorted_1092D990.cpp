// Game/Unsorted_1092D990.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class IDirect3DTexture8;

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
    virtual long __stdcall CreateTexture(unsigned int Width, unsigned int Height, unsigned int Levels, unsigned long Usage, int Format, int Pool, IDirect3DTexture8** ppTexture);
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
};

Class_10905A90_Member* FUN_10905aa0();

class Class_1092D990
{
public:
    void FUN_1092d990();

    IDirect3DTexture8* Unknown00;
    IDirect3DTexture8* Unknown04;
};

// FUNCTION: 0x1092D990 ?FUN_1092d990@Class_1092D990@@QAEXXZ
void Class_1092D990::FUN_1092d990()
{
    FUN_10905aa0()->Virtual8(0, 0);
    GDirect3DDevice8->CreateTexture(0x100, 0x80, 1, 1, 0x15, 0, &Unknown00);
    GDirect3DDevice8->CreateTexture(0x100, 0x80, 1, 1, 0x15, 0, &Unknown04);
}
